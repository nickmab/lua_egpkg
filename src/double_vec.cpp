#include "double_vec.hpp"

#include <algorithm>
#include <vector>

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

void double_vec_push_back(double_vec_t* p, double val, bool* outError) {
    if (p == NULL) {
        *outError = true;
        return;
    }
    *outError = false;
    static_cast<std::vector<double>*>(p->mVectorOfDouble)->push_back(val);
}

double double_vec_max_value(double_vec_t* p, bool* outError) {
    *outError = true;
    if (p == NULL) return 0.0;
    auto vec = *static_cast<std::vector<double>*>(p->mVectorOfDouble);
    auto it = std::max_element(vec.begin(), vec.end());
    if (it != vec.end())
    {
        *outError = false;
        return *it;
    }
    return 0.0;
}