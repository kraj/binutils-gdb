find . -name "*.c" -o -name "*.y" | while read line; do
  sed -e 's/CATCH [(]\([a-z]\+\), RETURN_MASK_ALL)/CATCH (const gdb_exception \&\1)/g' -i $line;
  sed -e 's/CATCH [(]\([a-z]\+\), RETURN_MASK_ERROR)/CATCH (const gdb_error \&\1)/g' -i $line;
done
