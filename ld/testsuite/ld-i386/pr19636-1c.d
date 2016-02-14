#source: pr19636-1.s
#as: --32 -mrelax-relocations=no
#ld: -pie -E -m elf_i386 -z nodynamic-undefined-weak
#readelf : --wide --dyn-syms

#failif
#...
 +[0-9]+: +[a-f0-9]+ +0 +NOTYPE +WEAK +DEFAULT +UND +func[0-9]?
#...
