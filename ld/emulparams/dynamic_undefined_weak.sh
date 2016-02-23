PARSE_AND_LIST_OPTIONS_DYNAMIC_UNDEFINED_WEAK='
  fprintf (file, _("\
  -z dynamic-undefined-weak   Treat undefined weak symbol as dynamic\n"));
'

PARSE_AND_LIST_ARGS_CASE_Z_DYNAMIC_UNDEFINED_WEAK='
      else if (strcmp (optarg, "dynamic-undefined-weak") == 0)
	link_info.dynamic_undefined_weak = TRUE;
'

PARSE_AND_LIST_OPTIONS="$PARSE_AND_LIST_OPTIONS $PARSE_AND_LIST_OPTIONS_DYNAMIC_UNDEFINED_WEAK"
PARSE_AND_LIST_ARGS_CASE_Z="$PARSE_AND_LIST_ARGS_CASE_Z $PARSE_AND_LIST_ARGS_CASE_Z_DYNAMIC_UNDEFINED_WEAK"
