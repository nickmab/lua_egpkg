#ifndef LUA_EGPKG_DOUBLE_VEC_H
#define LUA_EGPKG_DOUBLE_VEC_H

#define DOUBLE_VEC_SUCCESS 0
#define DOUBLE_VEC_ERR_NULL_STRUCT_OP 1
#define DOUBLE_VEC_ERR_NULL_VEC_OP 2
#define DOUBLE_VEC_ERR_EMPTY_VEC_INVALID_OP 3

#ifdef __cplusplus
extern "C" {
#endif

const char* errCodeToString(char errCode);

struct double_vec { void* mVectorOfDouble; };
typedef struct double_vec double_vec_t;

double_vec_t* double_vec_new();
void          double_vec_delete(double_vec_t*);
void          double_vec_push_back(double_vec_t*, double val, char* errCode);
double        double_vec_max_value(double_vec_t*, char* errCode);

#ifdef __cplusplus
}
#endif

#endif /* LUA_EGPKG_DOUBLE_VEC_H */