#source: pr19636-1.s
#as: --32 -mrelax-relocations=no
#ld: -m elf_i386 -z nodynamic-undefined-weak
#readelf : -r --wide -x .got -x .got.plt --dyn-syms

There are no relocations in this file.

Hex dump of section '.got':
  0x[0-9a-f]+ [0 ]+\.+

Hex dump of section '.got.plt':
  0x[0-9a-f]+ [0 ]+\.+
