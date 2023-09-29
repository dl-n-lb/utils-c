#ifndef VEC_H_
#define VEC_H_

#ifndef NDEBUG
#define SAFE_INDEX
#endif //NDEBUG

#ifndef VEC_ASSERT
#include <assert.h>
#define VEC_ASSERT assert
#endif // VEC_ASSERT

#ifndef VEC_MALLOC
#include <stdlib.h>
#define VEC_MALLOC malloc
#endif // VEC_MALLOC

#ifndef VEC_REALLOC
#include <stdlib.h>
#define VEC_REALLOC realloc
#endif // VEC_REALLOC

#ifndef VEC_MEMCPY
#include <string.h>
#define VEC_MEMCPY memcpy
#endif // VEC_MEMCPY

#define arr(T) struct {				\
    T *data;					\
    size_t len;					\
  }

#define slice(T) struct {			\
    T *data;					\
    size_t len;					\
  } 

#define vec(T) struct {				\
    T *data;					\
    size_t len;					\
    size_t cap;					\
  } vec_t;

#define VEC_GROW_RATE 2

#define vec_new(T, sz)				\
  {						\
    .data = VEC_MALLOC(sizeof(T) * sz),		\
    .len = 0,					\
    .cap = sz,				        \
  }

#define arr_new(T, sz)				\
  {						\
    .data = VEC_MALLOC(sizeof(T) * sz),		\
    .len = sz,					\
  }

#define arr_from(c_arr, sz)			\
  { .data = c_arr, .len = sz }

#define vec_from(c_arr, sz)			\
  { .data = c_arr, .len = sz, .cap = sz }

#define vec_push(vec, val) do {						\
    if ((vec).len + 1 >= (vec).cap) {					\
      (vec).cap *= VEC_GROW_RATE;					\
      (vec).data = VEC_REALLOC((vec).data, sizeof(*(vec).data) * (vec).cap); \
      VEC_ASSERT((vec).data && "REALLOC FAILED WHAT LOL TROLLED");	\
    }									\
    (vec).data[(vec).len++] = (val);					\
  } while(0)

#ifdef SAFE_INDEX
#define arr_at(arr, idx) (assert((idx) >= 0 && (idx) < (arr).len),	\
			     ((arr).data)[(idx)])
#define vec_at(vec, idx) arr_at((vec), idx)
#define arr_ref(arr, idx) (assert((idx) >= 0 && (idx) < (arr).len),	\
			      &((arr).data)[(idx)])
#define vec_ref(vec, idx) arr_ref((vec), idx)
#else
#define arr_at(arr, idx) ((arr).data)[(idx)]
#define vec_at(vec, idx) arr_at((vec), idx)
#define arr_ref(arr, idx) &((arr).data)[(idx)]
#define vec_ref(vec, idx) arr_ref((vec), idx)
#endif // SAFE_INDEX

#define arr_for_each(arr, it_name)					\
  for(typeof(*(arr).data) *it_name = (arr).data;			\
      it_name < ((arr).data + (arr).len); ++it_name)

#define vec_for_each(T, vec, it_name) arr_for_each((vec), it_name)

#define vec_free(vec) (free((vec).data), (vec).len = 0, (vec).cap = 0)
#define arr_free(arr) (free((arr).data), (arr).len = 0)
