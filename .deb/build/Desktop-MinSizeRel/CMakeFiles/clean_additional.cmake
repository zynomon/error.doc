# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "MinSizeRel")
  file(REMOVE_RECURSE
  "CMakeFiles/error_doc_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/error_doc_autogen.dir/ParseCache.txt"
  "error_doc_autogen"
  )
endif()
