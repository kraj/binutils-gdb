#source: pr17550-1.s
#source: pr17550-2.s
#ld: -r
#readelf: -s --wide

#failif
#...
 +[0-9]+: +[0-9a-f]+ +0 +OBJECT +GLOBAL +DEFAULT +UND x_alias
#...
