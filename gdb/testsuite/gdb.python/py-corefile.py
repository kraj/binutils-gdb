# Copyright (C) 2025 Free Software Foundation, Inc.

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

import pathlib


class Mapping:
    def __init__(self, mapping, region):
        self._mapping = mapping
        self._region = region

    @property
    def start(self):
        return self._region.start

    @property
    def end(self):
        return self._region.end

    @property
    def offset(self):
        return self._region.file_offset

    @property
    def filename(self):
        return self._mapping.filename


def info_proc_mappings():
    print("Mapped address spaces:")
    print("")
    format_str = "%-18s %-18s %-18s %-18s %s "
    print(format_str % ("Start Addr", "End Addr", "Size", "Offset", "File"))

    core = gdb.selected_inferior().corefile
    mappings = core.mapped_files()

    result = []
    for m in mappings:
        for r in m.regions:
            result.append(Mapping(m, r))

    result.sort(key=lambda x: x.start)
    for r in result:
        sz = r.end - r.start
        print(
            format_str
            % (
                "0x%016x" % r.start,
                "0x%016x" % r.end,
                "0x%-16x" % sz,
                "0x%-16x" % r.offset,
                "%s" % r.filename,
            )
        )


class InfoProcPyMappings(gdb.Command):
    def __init__(self):
        gdb.Command.__init__(self, "info proc py-mappings", gdb.COMMAND_DATA)

    def invoke(self, args, from_tty):
        info_proc_mappings()


InfoProcPyMappings()


class CheckBuildIds(gdb.Command):
    def __init__(self):
        gdb.Command.__init__(self, "check-build-ids", gdb.COMMAND_DATA)

    def invoke(self, args, from_tty):
        inf = gdb.selected_inferior()
        objfiles = inf.progspace.objfiles()

        path_to_build_id = {}

        for o in objfiles:
            if not o.is_file or o.build_id is None:
                continue
            p = pathlib.Path(o.filename).resolve()
            b = o.build_id
            path_to_build_id[p] = b

        count = 0
        core_mapped_files = inf.corefile.mapped_files()
        for m in core_mapped_files:
            p = pathlib.Path(m.filename).resolve()
            b = m.build_id

            if p in path_to_build_id:
                count += 1
                assert path_to_build_id[p] == b, "build-id mismatch for %s" % p

        assert count > 0, "no mapped files checked"

        print("PASS")


CheckBuildIds()


class CheckMainExec(gdb.Command):
    def __init__(self):
        gdb.Command.__init__(self, "check-main-executable", gdb.COMMAND_DATA)

    def invoke(self, args, from_tty):
        inf = gdb.selected_inferior()
        pspace = inf.progspace
        exec_filename = pathlib.Path(pspace.executable_filename).resolve()

        count = 0
        core_mapped_files = inf.corefile.mapped_files()
        for m in core_mapped_files:
            if not m.is_main_executable:
                continue

            p = pathlib.Path(m.filename).resolve()

            count += 1
            assert exec_filename == p, "main exec filename mismatch"

        assert count == 1, "invalid main executable count"

        print("PASS")


CheckMainExec()


# An 'events' prefix command.
class events_cmd(gdb.Command):
    """Information about recent Python events."""

    def __init__(self):
        gdb.Command.__init__(self, "events", gdb.COMMAND_USER, prefix=True)


# An 'events corefile_changed' sub-command.
class events_corefile_changed_cmd(gdb.Command):
    """Check recent corefile_changed events.

    Requires a single argument either 'check' or 'reset'.  With
    'check', print details of every recent corefile_changed event.
    With 'reset' clear the list of recent corefile_changed events."""

    def __init__(self):
        gdb.Command.__init__(self, "events corefile_changed", gdb.COMMAND_USER)
        self._events = []
        gdb.events.corefile_changed.connect(lambda e: self._corefile_changed_handler(e))

    def _corefile_changed_handler(self, event):
        assert isinstance(event, gdb.CorefileChangedEvent)
        inf = event.inferior
        assert isinstance(inf, gdb.Inferior)

        corefile = inf.corefile
        if corefile is not None:
            assert corefile.is_valid()
            corefile = corefile.filename

        obj = {"inferior": inf.num, "corefile": corefile}
        self._events.append(obj)

    def invoke(self, args, from_tty):
        if args == "check":
            if len(self._events) == 0:
                print("No corefile_changed event has been seen.")
            else:
                total = len(self._events)
                for idx, obj in enumerate(self._events, start=1):
                    inf_num = obj["inferior"]
                    corefile = obj["corefile"]

                    if corefile is None:
                        msg = "None"
                    else:
                        msg = corefile

                    print(
                        "Event {}/{}, Inferior {}, Corefile {}".format(
                            idx, total, inf_num, msg
                        )
                    )
        elif args == "reset":
            self._events = []
        else:
            raise gdb.GdbError("Unknown command args: {}".format(args))


# An 'events exited' sub-command.
class events_exited_cmd(gdb.Command):
    """Check recent exited events.

    Requires a single argument either 'check' or 'reset'.  With
    'check', print details of every recent exited event.  With 'reset'
    clear the list of recent exited events."""

    def __init__(self):
        gdb.Command.__init__(self, "events exited", gdb.COMMAND_USER)
        self._events = []
        gdb.events.exited.connect(lambda e: self._exited_handler(e))

    def _exited_handler(self, event):
        assert isinstance(event, gdb.ExitedEvent)
        inf = event.inferior
        assert isinstance(inf, gdb.Inferior)

        if hasattr(event, "exit_code"):
            assert isinstance(event.exit_code, int)
            exit_code = event.exit_code
        else:
            exit_code = None

        obj = {"inferior": inf.num, "exit_code": exit_code}
        self._events.append(obj)

    def invoke(self, args, from_tty):
        if args == "check":
            if len(self._events) == 0:
                print("No exited event has been seen.")
            else:
                total = len(self._events)
                for idx, obj in enumerate(self._events, start=1):
                    inf_num = obj["inferior"]
                    exit_code = obj["exit_code"]

                    if exit_code is None:
                        msg = "None"
                    else:
                        msg = exit_code

                    print(
                        "Event {}/{}, Inferior {}, Exit Code {}".format(
                            idx, total, inf_num, msg
                        )
                    )
        elif args == "reset":
            self._events = []
        else:
            raise gdb.GdbError("Unknown command args: {}".format(args))


events_cmd()
events_corefile_changed_cmd()
events_exited_cmd()

print("Success")
