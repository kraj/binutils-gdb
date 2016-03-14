#source: pr19807-3.s
#as: --64
#ld: -pie -melf_x86_64 -z upper-address=0xffffffff
#readelf: -r --wide

Relocation section '.rela.dyn' at offset 0x[0-9a-f]+ contains 1 entries:
    Offset             Info             Type               Symbol's Value  Symbol's Name \+ Addend
[0-9a-f]+ +[0-9a-f]+ +R_X86_64_RELATIVE +[0-9a-f]+
