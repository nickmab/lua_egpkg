#ifndef LUA_EGPKG_DOUBLE_VEC_H
#define LUA_EGPKG_DOUBLE_VEC_H

#ifdef __cplusplus
extern "C" {
#else
#include "stdbool.h"
#endif

struct double_vec { void* mVectorOfDouble; };
typedef struct double_vec double_vec_t;

double_vec_t* double_vec_new();
void          double_vec_delete(double_vec_t*);
void          double_vec_push_back(double_vec_t*, double val, bool* outError);
double        double_vec_max_value(double_vec_t*, bool* outError);

#ifdef __cplusplus
}
#endif

#endif /* LUA_EGPKG_DOUBLE_VEC_H */