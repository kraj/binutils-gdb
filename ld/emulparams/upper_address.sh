PARSE_AND_LIST_OPTIONS_UPPER_ADDRESS='
  fprintf (file, _("\
  -z upper-address=ADDRESS    Limit upper load address to ADDRESS\n"));
'
PARSE_AND_LIST_ARGS_CASE_Z_UPPER_ADDRESS='
      else if (strncmp (optarg, "upper-address=", 14) == 0)
	{
	  const char *end;
	  link_info.upper_address = bfd_scan_vma (optarg + 14, &end, 16);
	  if (*end)
	    einfo (_("%P%F: invalid hex number for -z upper-address=: %s\n"),
		   optarg + 14);
	}
'

PARSE_AND_LIST_OPTIONS="$PARSE_AND_LIST_OPTIONS $PARSE_AND_LIST_OPTIONS_UPPER_ADDRESS"
PARSE_AND_LIST_ARGS_CASE_Z="$PARSE_AND_LIST_ARGS_CASE_Z $PARSE_AND_LIST_ARGS_CASE_Z_UPPER_ADDRESS"
