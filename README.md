# C Utilities
A collection of useful types and functions (and macros) that make using C a little easier.
It is not standard/posix compliant since it uses _t to indicate types. I doubt there will be any issues any time soon.

Includes are like an stb style header-only library (most 'functions' are function macros as the type is required for them to work):

```c
#define VEC_IMPL
#include "vec.h"
```

Examples can be found in `test.c`.

Allocators are macro defined so if you want to define your own:

``` c
#define VEC_MALLOC my_malloc
#define VEC_REALLOC my_realloc
#define VEC_ASSERT my_assert
#define VEC_MEMCPY my_memcpy
#include "vec.h"
```
## vec.h

All of the syntax of these types is consistent, such that `len` refers to the length in elements, `cap` refers to the capacity in elements, and the data is stored as an array of bytes.

### vec
Like the `std::vector` of c++, but a little less convenient (no templates) and more explicit.
``` c
vec_t vec = vec_new(int, 10); // creates a 10 int capacity array with no elements
vec_push(int, vec, 1); // push 1 into vec, vec = {1}
vec_push(int, vec, 2); // push 2 into vec, vec = {1, 2}
printf("%d", vec_at(int, vec, 3)); // bounds checked if SAFE_INDEX is defined
vec_for_each(int, vec, it) { // iterate over the values in vec by pointer
	printf("%d\n", *it); // print out the value
}
vec_free(vec);
```

### arr + view
Like the `std::array` of c++, but a more explicit. It is literally a pointer, length pair.
The view is the same behind the scenes, but is expected to be used in places where the array isn't modified at all. This isn't enforced, but will be true throughout my code.
``` c
int *i = malloc(10 * sizeof(int));
i[0] = 10;
arr_t arr = arr_from(int, i, 10); // arr = {10, ... (some values)} : arr now owns the pointer
// so from here on, use of i is not recommended
*arr_ref(int, arr, 1) = 9;
arr_for_each(int, arr, it) {
	printf("%d", *it); // prints 10, 9, then undefined behaviour :)
}
arr_free(arr);
```

### string types
Coming soon...™

## tvec.h
Similar to vec.h, but using typed arrays, just as an experiment. Usage might look like
``` c
#include "tvec.h"

typedef vec(int) i32vec;
typedef vec(float) f32vec;

int main() {
	i32vec v1 = (i32vec)vec_new(int, 4);
	f32vec v2 = (f32vec)vec_new(float, 20);
	vec_push(v2, 10.f);
	vec_push(v2, 9.f);
	for (size_t i = 8; i >= 0; i--) {
		vec_push(v2, (float)i);
	}
    vec_for_each(v2, it) {
		printf("%f", *it);
	}	
	vec_free(v1);
	vec_free(v2);
	
	return 0;
}
```

## TODO
- vec_t concatenation [ ]
- view docs			  [ ]
- more safety		  [ ]
- examples			  [ ]
