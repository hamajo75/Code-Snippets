// mathlib_wrapper.h

#ifndef MATHLIB_WRAPPER_H
#define MATHLIB_WRAPPER_H

extern "C" {
#include "mathlib/mathlib.h"
}

class MathLibWrapper {
public:
    int add(int a, int b) {
        return ::add(a, b); // Call the C library function
    }

    int subtract(int a, int b) {
        return ::subtract(a, b); // Call the C library function
    }
};

#endif
