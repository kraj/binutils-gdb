#source: tls-err-55.s
#as: --pic --no-underscore --emulation=criself -I$srcdir/$subdir
#ld: --shared -m crislinux
#error: \A[^\n]*\.o[^\n]*relocation R_CRIS_32_GOT_GD with non-zero addend 42 against symbol `tls128'[^\n]*\n[^\n]*bad value\Z

# Check that non-zero addend on a R_CRIS_32_GOT_GD is flagged as an error.
