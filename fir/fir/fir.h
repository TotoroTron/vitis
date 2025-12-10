#ifndef FIR_H_
#define FIR_H_

#include "ap_fixed.h"
#include <cmath>

constexpr int FIR_DEPTH = 32;
constexpr int F_SAMPLING = 2000;
constexpr int F_PASS = 100;
constexpr int F_STOP = 800;
constexpr int NUM_SAMPLES = 200;

typedef ap_fixed<16, 4> data_t;
typedef ap_fixed<16, 4> coef_t;
typedef ap_fixed<16, 4> acc_t; // just truncate after each sum?

void fir_opt1(data_t *dout, coef_t coeffs[FIR_DEPTH], data_t din);
void fir_opt2(data_t *dout, coef_t coeffs[FIR_DEPTH], data_t din);
void fir_opt3(data_t *dout, coef_t coeffs[FIR_DEPTH], data_t din);
void fir_opt4(data_t *dout, coef_t coeffs[FIR_DEPTH], data_t din);

#endif //
