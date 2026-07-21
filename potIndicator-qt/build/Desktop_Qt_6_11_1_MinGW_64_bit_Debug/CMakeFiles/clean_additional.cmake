# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\potIndicator-qt_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\potIndicator-qt_autogen.dir\\ParseCache.txt"
  "potIndicator-qt_autogen"
  )
endif()
