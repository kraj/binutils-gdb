#source: pr17550-2.s
#source: pr17550-4.s
#ld: -r
#readelf: -s --wide

#...
 +[0-9]+: +[0-9a-f]+ +0 +OBJECT +GLOBAL +DEFAULT +UND y
#pass
