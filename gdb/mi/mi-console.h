/* MI Command Set - MI Console.
   Copyright (C) 2000-2017 Free Software Foundation, Inc.
   Contributed by Cygnus Solutions (a Red Hat company).

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

#ifndef MI_CONSOLE_H
#define MI_CONSOLE_H

/* An output stream for MI.  Wraps a given output stream with a prefix
   and handles quoting.  This stream is locally buffered.  */

class mi_console_file : public ui_file
{
public:
  /* Create a console that wraps the given output stream RAW with the
     string PREFIX and quoting it with QUOTE.  */
  mi_console_file (struct ui_file *raw, const char *prefix, char quote);

  /* MI-specific API.  */
  void set_raw (struct ui_file *raw);

  /* ui_file-specific methods.  */

  void flush () override;

  void write (const char *buf, long length_buf) override;

  void puts (const char *) override;

  void write_buffer_on (ui_file &where) override
  { m_buffer.write_buffer_on (where); }

  void rewind () override
  { gdb_assert_not_reached ("mi_console_file::rewind called\n"); }

private:
  /* The wrapped raw output stream.  */
  struct ui_file *m_raw;

  /* The local buffer.  */
  string_file m_buffer;

  /* The prefix.  */
  const char *m_prefix;

  /* The quote char.  */
  char m_quote;
};

#endif
