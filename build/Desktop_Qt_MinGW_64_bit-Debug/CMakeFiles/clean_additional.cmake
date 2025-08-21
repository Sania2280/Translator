# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Translator_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Translator_autogen.dir\\ParseCache.txt"
  "Translator_autogen"
  )
endif()
