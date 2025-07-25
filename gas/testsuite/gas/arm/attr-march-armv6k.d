# name: attributes for -march=armv6k
# source: blank.s
# as: -march=armv6k
# readelf: -A
# This test is only valid on EABI based ports.
# target: *-*-*eabi*

Attribute Section: aeabi
File Attributes
  Tag_CPU_name: "6K"
  Tag_CPU_arch: v6K
  Tag_ARM_ISA_use: Yes
  Tag_THUMB_ISA_use: Thumb-1
