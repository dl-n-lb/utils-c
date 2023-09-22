#ifndef FILE_H_
#define FILE_H_

#include "vec.h"
#include <stdio.h>
#include <stdbool.h>

// Read entire file into preallocated buffer
// returning false on error
// get error with ferror on the file
size_t get_file_sz(FILE *f);
bool read_entire_file(FILE *f, arr_t buff);

bool open_read_entire_file(const char *name, arr_t buff);

// Read entire file into a newly allocated array
// if it fails, it will set the length to -1
// TODO:
arr_t read_entire_fileA(FILE *f);
arr_t open_read_entire_fileA(const char *name);

#endif // FILE_H_
#ifdef FILE_IMPL

size_t get_file_sz(FILE *f) {
  fseek(f, 0, SEEK_END);
  size_t res = ftell(f);
  fseek(f, 0, SEEK_SET);
  return res;
}

bool read_entire_file(FILE *f, arr_t buff) {
  size_t cnt = fread(buff.data, buff.len, 1, f);
  return cnt > 0;
}

bool open_read_entire_file(const char *name, arr_t buff) {
  FILE *f = fopen(name, "rb");
  if (!f) return false;
  bool res = read_entire_file(f, buff);
  fclose(f);
  return res;
}

#endif // FILE_IMPL
