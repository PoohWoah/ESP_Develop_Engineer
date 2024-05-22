# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/esp-idf/esp-idf-5.1.1/v5.1.1/esp-idf/components/bootloader/subproject"
  "C:/Users/82030/Desktop/XXX/build/bootloader"
  "C:/Users/82030/Desktop/XXX/build/bootloader-prefix"
  "C:/Users/82030/Desktop/XXX/build/bootloader-prefix/tmp"
  "C:/Users/82030/Desktop/XXX/build/bootloader-prefix/src/bootloader-stamp"
  "C:/Users/82030/Desktop/XXX/build/bootloader-prefix/src"
  "C:/Users/82030/Desktop/XXX/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/82030/Desktop/XXX/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/82030/Desktop/XXX/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
