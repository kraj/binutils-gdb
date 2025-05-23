# Copyright 2013-2025 Free Software Foundation, Inc.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

load_lib dwarf.exp

# This test can only be run on targets which support DWARF-2 and use gas.
require dwarf2_support

# No remote host testing either.
require {!is_remote host}


# Lots of source files since we test a few cases and make new files
# for each.
# The tests are:
#     ok - the main file refers to a dwz and the buildids match
#     mismatch - the buildids do not match
#     fallback - the buildids do not match but a match is found via buildid
standard_testfile main.c \
    dwzbuildid-ok-base.S dwzbuildid-ok-sep.S \
    dwzbuildid-mismatch-base.S dwzbuildid-mismatch-sep.S \
    dwzbuildid-fallback-base.S dwzbuildid-fallback-sep.S \
    dwzbuildid-fallback-ok.S

# Write some assembly that just has a .gnu_debugaltlink section.
proc write_just_debugaltlink {filename dwzname buildid} {
    set asm_file [standard_output_file $filename]

    Dwarf::assemble $asm_file {
	upvar dwzname dwzname
	upvar buildid buildid

	if {$::scenario == "gnu"} {
	    gnu_debugaltlink $dwzname $buildid
	} else {
	    debug_sup 0 $dwzname $buildid
	}

	# Only the DWARF reader checks .gnu_debugaltlink, so make sure
	# there is a bit of DWARF in here.
	cu { label cu_start } {
	    compile_unit {{language @DW_LANG_C}} {
	    }
	}
	aranges {} cu_start {
	    arange {} 0 0
	}
    }
}

# Write some DWARF that also sets the buildid.
proc write_dwarf_file {filename buildid {value 99}} {
    set asm_file [standard_output_file $filename]

    Dwarf::assemble $asm_file {
	declare_labels int_label int_label2

	upvar buildid buildid
	upvar value value

	if {$::scenario == "gnu"} {
	    build_id $buildid
	} else {
	    debug_sup 1 "" $buildid
	}

	cu { label cu_start } {
	    compile_unit {{language @DW_LANG_C}} {
		int_label2: base_type {
		    {name int}
		    {byte_size 4 sdata}
		    {encoding @DW_ATE_signed}
		}

		constant {
		    {name the_int}
		    {type :$int_label2}
		    {const_value $value data1}
		}
	    }
	}

	aranges {} cu_start {
	    arange {} 0 0
	}
    }
}

if  { [gdb_compile ${srcdir}/${subdir}/${srcfile} ${binfile}1.o \
	   object {nodebug}] != "" } {
    return -1
}

# The values don't really matter, just whether they are equal.
set ok_prefix 01
set ok_suffix 02030405060708091011121314151617181920
set ok_suffix2 020304050607080910111213141516171819ff
set ok_buildid ${ok_prefix}${ok_suffix}
set ok_buildid2 ${ok_prefix}${ok_suffix2}
set bad_buildid [string repeat ff 20]

set debugdir [standard_output_file {}]
set basedir $debugdir/.build-id
file mkdir $basedir $basedir/$ok_prefix

# Test where the separate debuginfo's buildid matches.
write_just_debugaltlink $srcfile2 ${binfile}3.o $ok_buildid
write_dwarf_file $srcfile3 $ok_buildid

# Test where the separate debuginfo's buildid does not match.
write_just_debugaltlink $srcfile4 ${binfile}5.o $ok_buildid
write_dwarf_file $srcfile5 $bad_buildid

# Test where the separate debuginfo's buildid does not match, but then
# we find a match in the .build-id directory.
write_just_debugaltlink $srcfile6 ${binfile}7.o $ok_buildid2
# Use 77 as the value so that if we load the bad debuginfo, we will
# see the wrong result.
write_dwarf_file $srcfile7 $bad_buildid 77
write_dwarf_file $srcfile8 $ok_buildid2

# Compile everything.
for {set i 2} {$i <= 8} {incr i} {
    if {[gdb_compile [standard_output_file [set srcfile$i]] \
	     ${binfile}$i.o object nodebug] != ""} {
	return -1
    }
}

# Copy a file into the .build-id place for the "fallback" test.
file copy -force -- ${binfile}8.o $basedir/$ok_prefix/$ok_suffix2.debug

proc do_test {} {
    clean_restart

    gdb_test_no_output "set debug-file-directory $::debugdir" \
	"set debug-file-directory"

    gdb_load ${::binfile}-${::testname}

    if {![runto_main]} {
	return
    }

    if {$::testname == "mismatch"} {
	gdb_test "print the_int" \
	    "(No symbol table is loaded|No symbol \"the_int\" in current context).*"
    } else {
	gdb_test "print the_int" " = 99"
    }
}

set tests {ok mismatch}
if {$scenario == "gnu"} {
    lappend tests fallback
}
foreach_with_prefix testname $tests {
    if { $testname == "ok" } {
	set objs [list ${binfile}1.o ${binfile}2.o]
    } elseif { $testname == "mismatch" } {
	set objs [list ${binfile}1.o ${binfile}4.o]
    } elseif { $testname == "fallback" } {
	set objs [list ${binfile}1.o ${binfile}6.o]
    }

    if {[gdb_compile $objs ${binfile}-$testname executable {quiet}] != ""} {
	unsupported "compilation failed"
	continue
    }

    do_test
}
