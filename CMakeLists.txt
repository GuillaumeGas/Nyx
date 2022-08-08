CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
project(Nyx)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ggdb")

file (
  GLOB_RECURSE
  source_files
  global/*
  compilo/*
  parser/*
  ast/*
  symbol/*
  debugger/*
)

add_executable (
  ../nyx
  main.cpp
  ${source_files}
)