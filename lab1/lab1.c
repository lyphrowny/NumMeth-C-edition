#include <math.h>

#include "lab1.h"


long int BISECT_ITER = 0;
long int SECANT_ITER = 0;

void init_coeffs(const float* coeffs, int size) {
    Coeffs.size = size;
    Coeffs.coeffs = coeffs;
}

float limit(const float* coeffs, int size) {
    int m = -1;
    float a = coeffs[0];
    if (a < 0) // first coeff should be > 0
        return NAN;

    for (int i = 0; i < size; i++) {
        if (coeffs[i] < 0 && m == -1)
            m = i;
        if (coeffs[i] < a)
            a = coeffs[i];
    }
    if (m == -1)
        return INFINITY; // no negative roots
    return 1 + powf((fabsf(a) / coeffs[0]), (float)1 / (float)m);
}

float top_pos_limit() {
    if (Coeffs.coeffs[0] < 0) {
        float modified_coeffs[Coeffs.size];
        for (int i = 0; i < Coeffs.size; i++)
            modified_coeffs[i] = -Coeffs.coeffs[i];
        return limit(modified_coeffs, Coeffs.size);
    }
    return limit(Coeffs.coeffs, Coeffs.size);
}

float bottom_neg_limit() {
    float modified_coeffs[Coeffs.size];
    char need_to_negate = Coeffs.coeffs[0] < 0 && !(Coeffs.size & 1);

    for (int i = Coeffs.size - 1; i >= 0; i--) {
        modified_coeffs[i] = need_to_negate ? -Coeffs.coeffs[i] : Coeffs.coeffs[i];
        modified_coeffs[i] = i & 1 ? -modified_coeffs[i] : modified_coeffs[i];
    }
    return -limit(modified_coeffs, Coeffs.size);
}

float bottom_pos_limit() {
    float modified_coeffs[Coeffs.size];
    // reversing
    char need_to_negate = Coeffs.coeffs[Coeffs.size - 1] < 0;

    for (int i = 0; i < Coeffs.size; i++) {
        modified_coeffs[i] = need_to_negate ? -Coeffs.coeffs[Coeffs.size - 1 - i] : Coeffs.coeffs[Coeffs.size - 1 - i] ;
    }
    float res = limit(modified_coeffs, Coeffs.size);
    return res == INFINITY ? res : 1 / res;
}

float top_neg_limit() {
    float modified_coeffs[Coeffs.size];
    char need_to_negate = Coeffs.coeffs[Coeffs.size - 1] < 0 && !(Coeffs.size & 1);

    for (int i = 0; i < Coeffs.size; i++) {
        modified_coeffs[i] = need_to_negate ? -Coeffs.coeffs[Coeffs.size - 1 - i] : Coeffs.coeffs[Coeffs.size - 1 - i];
        modified_coeffs[i] = i & 1 ? -modified_coeffs[i] : modified_coeffs[i];
    }
    float res = limit(modified_coeffs, Coeffs.size);
    return res == INFINITY ? -res : -1 / res;
}

float polynomial(float x) {
    float res = 0;

    for (int i = 0; i < Coeffs.size; i++)
        res += Coeffs.coeffs[i] * powf(x, (float)(Coeffs.size - 1 - i));
    return res;
}

float transcendental(float x) {
    return x - cosf(x);
}

float bisect(float a, float b, float precision, float (* func)(float)) {
    float c, f_c, f_a = func(a), f_b = func(b);
    if (!sign(f_a) ^ sign(f_b))
        return NAN;
    while (fabsf(a - b) > 2 * precision) {
        BISECT_ITER++;
        c = (a + b) / 2;
        f_c = func(c);
        if (sign(f_c) ^ sign(f_a))
            b = c, f_b = f_c;
        else
            a = c, f_a = f_c;
    }
    return (a + b) / 2;
}

float secant(float a, float b, float precision, float (* func)(float)) {
    float f_a = func(a), f_b = func(b);
    while (fabsf(b - a) > precision) {
        SECANT_ITER++;
        a = b - f_b * (b - a) / (f_b - f_a);
        f_a = func(a);
        if (f_a == 0)
            return a;
        b = a - f_a * (a - b) / (f_a - f_b);
        f_b = func(b);
        if (f_b == 0)
            return b;
    }
    return b;
}

long int get_bisect_iter() {
    return BISECT_ITER;
}

long int get_secant_iter() {
    return SECANT_ITER;
}

void null_bisect_iter() {
    BISECT_ITER = 0;
}

void null_secant_iter() {
    SECANT_ITER = 0;
}
