#include "vec.h"
#include <stdio.h>

void print_int_vec(vec_t vec) {
  vec_for_each(int, vec, it) {
    printf("%d ", *it);
  }
  printf("\n");
}

int main() {
  int c_arr[] = { 0, 2, 4, 6, 8, 10 };
  vec_t v = vec_from_const(int, c_arr);

  vec_t v2 = vec_new(int, 1);
  vec_push(int, v2, 1);
  vec_push(int, v2, 11);
  vec_push(int, v2, 21);

  print_int_vec(v);
  print_int_vec(v2);
  
  free(v.data);
  free(v2.data);
  return 0;
}
