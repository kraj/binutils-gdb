#as: -mrelax-relocations=no
#readelf: -rsW
#name: x86-64 local PIC 2

Relocation section '.rela.text' at offset 0x[0-9a-f]+ contains 1 entry:
 +Offset +Info +Type +Symbol's Value +Symbol's Name \+ Addend
[0-9a-f]+ +[0-9a-f]+ R_X86_64_THUNK_GOTPCRELX +[0-9a-f]+ +foo - 4
#...
 +[0-9]+: +[0-9a-f]+ +[0-9a-f]+ +NOTYPE +LOCAL +DEFAULT +[0-9]+ +foo
#pass
