/* MI Command Set for GDB, the GNU debugger.

   Copyright (C) 2019 Free Software Foundation, Inc.

   This file is part of GDB.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* gdb MI commands implemented in Python  */

#include "defs.h"
#include "python-internal.h"
#include "python/py-micmd.h"
#include "arch-utils.h"
#include "charset.h"
#include "language.h"

#include <string>

static PyObject *invoke_cst;

extern PyTypeObject
  micmdpy_object_type CPYCHECKER_TYPE_OBJECT_FOR_TYPEDEF ("micmdpy_object");

/* If the command invoked returns a list, this function parses it and create an
   appropriate MI out output.

   The returned values must be Python string, and can be contained within Python
   lists and dictionaries. It is possible to have a multiple levels of lists
   and/or dictionaries.  */

static void
parse_mi_result (PyObject *result, const char *field_name)
{
  struct ui_out *uiout = current_uiout;

  if (PyDict_Check (result))
    {
      PyObject *key, *value;
      Py_ssize_t pos = 0;
      ui_out_emit_tuple tuple_emitter (uiout, field_name);
      while (PyDict_Next (result, &pos, &key, &value))
	{
	  if (!PyString_Check (key))
	    {
	      gdbpy_ref<> key_repr (PyObject_Repr (key));
	      if (PyErr_Occurred () != NULL)
                {
                  gdbpy_err_fetch ex;
                  gdb::unique_xmalloc_ptr<char> ex_msg (ex.to_string ());

                  if (ex_msg == NULL || *ex_msg == '\0')
                    error (_("Non-string object used as key."));
                  else
                    error (_("Non-string object used as key: %s."),
                           ex_msg.get ());
                }
              else
	        {
	          auto key_repr_string
	                 = python_string_to_target_string (key_repr.get ());
	          error (_("Non-string object used as key: %s."),
                         key_repr_string.get ());
	        }
	    }

	  auto key_string = python_string_to_target_string (key);
	  parse_mi_result (value, key_string.get ());
	}
    }
  else if (PySequence_Check (result) && !PyString_Check (result))
    {
      ui_out_emit_list list_emitter (uiout, field_name);
      for (Py_ssize_t i = 0; i < PySequence_Size (result); ++i)
	{
          gdbpy_ref<> item (PySequence_ITEM (result, i));
	  parse_mi_result (item.get (), NULL);
	}
    }
  else if (PyIter_Check (result))
    {
      gdbpy_ref<> item;
      ui_out_emit_list list_emitter (uiout, field_name);
      while (item.reset (PyIter_Next (result)), item != nullptr)
	parse_mi_result (item.get (), NULL);
    }
  else
    {
      gdb::unique_xmalloc_ptr<char> string (gdbpy_obj_to_string (result));
      uiout->field_string (field_name, string.get ());
    }
}

/* Object initializer; sets up gdb-side structures for MI command.

   Use: __init__(NAME).

   NAME is the name of the MI command to register.  It must start with a dash
   as traditional MI commands do.  */

static int
micmdpy_init (PyObject *self, PyObject *args, PyObject *kw)
{
  const char *name;
  gdbpy_ref<> self_ref = gdbpy_ref<>::new_reference (self);

  if (!PyArg_ParseTuple (args, "s", &name))
    return -1;

  /* Validate command name */
  const int name_len = strlen (name);
  if (name_len == 0)
    {
      error (_("MI command name is empty."));
      return -1;
    }
  else if ((name_len < 2) || (name[0] != '-') || !isalnum (name[1]))
    {
      error (_("MI command name does not start with '-'"
               " followed by at least one letter or digit."));
      return -1;
    }
  else
    for (int i = 2; i < name_len; i++)
      {
	if (!isalnum (name[i]) && name[i] != '-')
	  {
	    error (_("MI command name contains invalid character: %c."),
                   name[i]);
	    return -1;
	  }
      }

  if (!PyObject_HasAttr (self_ref.get (), invoke_cst))
      error (_("-%s: Python command object missing 'invoke' method."), name);

  try
    {
      mi_cmd_up micommand = mi_cmd_up(new mi_command_py (name + 1, self_ref));

      bool result = insert_mi_cmd_entry (std::move (micommand));

      if (!result)
	{
	  error (_("Unable to insert command."
                   "The name might already be in use."));
	  return -1;
	}
    }
  catch (const gdb_exception &except)
    {
      GDB_PY_SET_HANDLE_EXCEPTION (except);
    }

  return 0;
}

mi_command_py::mi_command_py (const char *name, gdbpy_ref<> object)
  : mi_command (name, NULL), pyobj (object)
{
}

void
mi_command_py::do_invoke (struct mi_parse *parse)
{
  mi_parse_argv (parse->args, parse);

  if (parse->argv == NULL)
    error (_("Problem parsing arguments: %s %s"), parse->command, parse->args);

  PyObject *obj = this->pyobj.get ();

  gdbpy_enter enter_py (get_current_arch (), current_language);

  gdb_assert (obj != nullptr);

  if (!PyObject_HasAttr (obj, invoke_cst))
      error (_("-%s: Python command object missing 'invoke' method."),
	     name ().c_str ());


  gdbpy_ref<> argobj (PyList_New (parse->argc));
  if (argobj == nullptr)
    {
      gdbpy_print_stack ();
      error (_("-%s: failed to create the Python arguments list."),
	     name ().c_str ());
    }

  for (int i = 0; i < parse->argc; ++i)
    {
      gdbpy_ref<> str (PyUnicode_Decode (parse->argv[i], strlen (parse->argv[i]),
					 host_charset (), NULL));
      if (PyList_SetItem (argobj.get (), i, str.release ()) != 0)
	{
	  error (_("-%s: failed to create the Python arguments list."),
		 name ().c_str ());
	}
    }

  gdb_assert (PyErr_Occurred () == NULL);
  gdbpy_ref<> result (
    PyObject_CallMethodObjArgs (obj, invoke_cst, argobj.get (), NULL));
  if (PyErr_Occurred () != NULL)
    {
      gdbpy_err_fetch ex;
      gdb::unique_xmalloc_ptr<char> ex_msg (ex.to_string ());

      if (ex_msg == NULL || *ex_msg == '\0')
	error (_("-%s: failed to execute command"), name ().c_str ());
      else
	error (_("-%s: %s"), name ().c_str (), ex_msg.get ());
    }
  else
    {
      if (Py_None != result)
	parse_mi_result (result.get (), "result");
    }
}

void mi_command_py::finalize ()
{
  this->pyobj.reset (nullptr);
}

/* Initialize the MI command object.  */

int
gdbpy_initialize_micommands ()
{
  micmdpy_object_type.tp_new = PyType_GenericNew;
  if (PyType_Ready (&micmdpy_object_type) < 0)
    return -1;

  if (gdb_pymodule_addobject (gdb_module, "MICommand",
			      (PyObject *) &micmdpy_object_type)
      < 0)
    return -1;

  invoke_cst = PyString_FromString ("invoke");
  if (invoke_cst == NULL)
    return -1;

  return 0;
}

static PyMethodDef micmdpy_object_methods[] = {{0}};

PyTypeObject micmdpy_object_type = {
  PyVarObject_HEAD_INIT (NULL, 0) "gdb.MICommand", /*tp_name */
  sizeof (micmdpy_object),			   /*tp_basicsize */
  0,						   /*tp_itemsize */
  0,						   /*tp_dealloc */
  0,						   /*tp_print */
  0,						   /*tp_getattr */
  0,						   /*tp_setattr */
  0,						   /*tp_compare */
  0,						   /*tp_repr */
  0,						   /*tp_as_number */
  0,						   /*tp_as_sequence */
  0,						   /*tp_as_mapping */
  0,						   /*tp_hash */
  0,						   /*tp_call */
  0,						   /*tp_str */
  0,						   /*tp_getattro */
  0,						   /*tp_setattro */
  0,						   /*tp_as_buffer */
  Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,	/*tp_flags */
  "GDB mi-command object",			   /* tp_doc */
  0,						   /* tp_traverse */
  0,						   /* tp_clear */
  0,						   /* tp_richcompare */
  0,						   /* tp_weaklistoffset */
  0,						   /* tp_iter */
  0,						   /* tp_iternext */
  micmdpy_object_methods,			   /* tp_methods */
  0,						   /* tp_members */
  0,						   /* tp_getset */
  0,						   /* tp_base */
  0,						   /* tp_dict */
  0,						   /* tp_descr_get */
  0,						   /* tp_descr_set */
  0,						   /* tp_dictoffset */
  micmdpy_init,					   /* tp_init */
  0,						   /* tp_alloc */
};
