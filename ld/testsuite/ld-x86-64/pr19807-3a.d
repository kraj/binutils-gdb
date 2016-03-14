#source: pr19807-3.s
#as: --64
#ld: -pie -melf_x86_64
#error: .*relocation R_X86_64_32 against symbol `.data' can not be used when making a shared object; recompile with -fPIC
