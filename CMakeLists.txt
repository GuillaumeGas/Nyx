CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
project(Bob)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ggdb")

file (
  GLOB_RECURSE
  source_files
  compilo/*
  parser/*
  ast/*
)

add_executable (
  ../bob
  main.cpp
  ${source_files}
)