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

#ifndef PY_MICMDS_H
#define PY_MICMDS_H

#include "mi/mi-cmds.h"
#include "mi/mi-parse.h"
#include "python-internal.h"
#include "python/py-ref.h"

struct micmdpy_object
{
  PyObject_HEAD
};

typedef struct micmdpy_object micmdpy_object;

/* MI command implemented in Python.  */

class mi_command_py : public mi_command
{
  public:
    /* Constructs a new mi_command_py object.  NAME is command name without
       leading dash.  OBJECT is a reference to a Python object implementing
       the command.  This object should inherit from gdb.MICommand and should
       implement method invoke (args). */

    mi_command_py (const char *name, gdbpy_ref<> object);


    /* This is called just before shutting down a Python interpreter
       to release python object implementing the command. */

    void finalize ();

  protected:
   virtual void do_invoke(struct mi_parse *parse) override;

  private:
    gdbpy_ref<> pyobj;
};

#endif
