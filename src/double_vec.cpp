#include "double_vec.hpp"

#include <algorithm>
#include <vector>

const char* errCodeToString(char errCode) {
    switch (errCode) {
    case DOUBLE_VEC_SUCCESS:
        return "Success (no error)!";
    case DOUBLE_VEC_ERR_NULL_STRUCT_OP:
        return "Attempted operation on null instance / struct.";
    case DOUBLE_VEC_ERR_NULL_VEC_OP:
        return "Instance / struct was non-null, but vector was null.";
    case DOUBLE_VEC_ERR_EMPTY_VEC_INVALID_OP:
        return "Invalid operation attempted on empty (non-null) vector.";
    default:
        return "Unrecognised error code.";
    }
}

double_vec_t* double_vec_new() {
    double_vec_t* p = (double_vec_t*)malloc(sizeof(double_vec_t));
    if (p == NULL) return NULL;
    p->mVectorOfDouble = static_cast<void*>(new std::vector<double>());
    return p;
}

void double_vec_delete(double_vec_t* p) {
    if (p == NULL) return;
    if (p->mVectorOfDouble != NULL) {
        delete static_cast<std::vector<double>*>(p->mVectorOfDouble);
        p->mVectorOfDouble = NULL;
    }
    free(p);
    p = NULL;
}

void double_vec_push_back(double_vec_t* p, double val, char* errCode) {
    if (p == NULL) {
        *errCode = DOUBLE_VEC_ERR_NULL_STRUCT_OP;
        return;
    }
    if (p->mVectorOfDouble == NULL) {
        *errCode = DOUBLE_VEC_ERR_NULL_VEC_OP;
        return;
    }
    *errCode = DOUBLE_VEC_SUCCESS;
    static_cast<std::vector<double>*>(p->mVectorOfDouble)->push_back(val);
}

double double_vec_max_value(double_vec_t* p, char* errCode) {
    if (p == NULL) {
        *errCode = DOUBLE_VEC_ERR_NULL_STRUCT_OP;
        return 0.0;
    }
    if (p->mVectorOfDouble == NULL) {
        *errCode = DOUBLE_VEC_ERR_NULL_VEC_OP;
        return 0.0;
    }
    auto vec = *static_cast<std::vector<double>*>(p->mVectorOfDouble);
    auto it = std::max_element(vec.begin(), vec.end());
    if (it != vec.end()) {
        *errCode = DOUBLE_VEC_SUCCESS;
        return *it;
    }
    else {
        *errCode = DOUBLE_VEC_ERR_EMPTY_VEC_INVALID_OP;
        return 0.0;
    }
}