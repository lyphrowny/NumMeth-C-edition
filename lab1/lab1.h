#ifndef LAB1_H
#define LAB1_H

#define sign(a) ((a) >= 0 ? 1 : 0)

static struct Coeffs {
    const float* coeffs;
    int size;
} Coeffs;

enum lims_index {
    TP, // top positive
    BP, // bottom positive
    TN, // top negative
    BN // bottom negative
};

void init_coeffs(const float* coeffs, int size);

float limit(const float* coeffs, int size);

float top_pos_limit();

float top_neg_limit();

float bottom_pos_limit();

float bottom_neg_limit();

static float (* limits[])(void) = {top_pos_limit, bottom_pos_limit, top_neg_limit, bottom_neg_limit};

static char* limits_names[] = {"top positive", "bottom positive", "top negative", "bottom negative"};

float polynomial(float x);

float transcendental(float x);

float bisect(float a, float b, float precision, float (* func)(float));

float secant(float a, float b, float precision, float (* func)(float));

long int get_bisect_iter();

long int get_secant_iter();

void null_bisect_iter();

void null_secant_iter();

#endif // LAB1_H
