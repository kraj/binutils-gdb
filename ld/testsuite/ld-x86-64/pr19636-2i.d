#source: pr19636-2.s
#as: --64 -mrelax-relocations=no
#ld: -E -m elf_x86_64 -z nodynamic-undefined-weak
#readelf : --wide --dyn-syms

#failif
#...
 +[0-9]+: +[a-f0-9]+ +0 +NOTYPE +WEAK +DEFAULT +UND +func[0-9]?
#...
