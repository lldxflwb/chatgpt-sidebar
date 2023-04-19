# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\chatgpt-sidebar_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\chatgpt-sidebar_autogen.dir\\ParseCache.txt"
  "chatgpt-sidebar_autogen"
  )
endif()
