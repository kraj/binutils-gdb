/* Copyright 2009-2025 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

   This file is part of the gdb testsuite.
   It tests displaced stepping over various insns that require special
   handling.  */

	.text
	.global test_call
test_call:
	call test_call
	call unreachable
	.global test_ret_end
test_ret_end:
	nop

	.section	.note.GNU-stack,"",@progbits
