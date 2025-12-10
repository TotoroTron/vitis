#include "fir.h"

void fir_opt1(data_t *dout, coef_t coeffs[FIR_DEPTH], data_t din) {
    static data_t shift_reg[FIR_DEPTH];
    acc_t acc;
    int i;
    acc = 0;
    for (i = FIR_DEPTH - 1; i >= 0; i--) {
        if (i == 0) {
            acc += din * coeffs[0];
            shift_reg[0] = din;
        } else {
            shift_reg[i] = shift_reg[i - 1];
            acc += shift_reg[i] * coeffs[i];
        }
    }
    *dout = (data_t)acc;
}

void fir_opt2(data_t *dout, coef_t coeffs[FIR_DEPTH], data_t din) {
    static data_t shift_reg[FIR_DEPTH];
    acc_t acc;
    int i;
TDL:
    for (i = FIR_DEPTH - 1; i > 0; i--) {
        shift_reg[i] = shift_reg[i - 1];
    }
    shift_reg[0] = din;
    acc = 0;
MAC:
    for (i = FIR_DEPTH - 1; i >= 0; i--) {
        acc += shift_reg[i] * coeffs[i];
    }
    *dout = (data_t)acc;
}

void fir_opt3(data_t *dout, coef_t coeffs[FIR_DEPTH], data_t din) {
    static data_t shift_reg[FIR_DEPTH];
    acc_t acc;
    int i;
TDL:
    for (i = FIR_DEPTH - 1; i > 1; i = i - 2) {
        shift_reg[i] = shift_reg[i - 1];
        shift_reg[i - 1] = shift_reg[i - 2];
    }
    if (i == 1) {
        shift_reg[1] = shift_reg[0];
    }
    shift_reg[0] = din;
    acc = 0;
MAC:
    // process in time slices, each 4 cycles long
    for (i = FIR_DEPTH - 1; i >= 3; i -= 4) {
        // acc += shift_reg[i] * coeffs[i] + shift_reg[i - 1] * coeffs[i - 1] +
        // shift_reg[i - 2] * coeffs[i - 2] + shift_reg[i - 3] * coeffs[i - 3];
        acc += shift_reg[i] * coeffs[i];
        acc += shift_reg[i - 1] * coeffs[i - 1];
        acc += shift_reg[i - 2] * coeffs[i - 2];
        acc += shift_reg[i - 3] * coeffs[i - 3];
    }
    // process final time slice for non-multiple of 4 depth
    for (; i >= 0; i--) {
        acc += shift_reg[i] * coeffs[i];
    }
    *dout = (data_t)acc;
}

void fir_opt4(data_t *dout, coef_t coeffs[FIR_DEPTH], data_t din) {
    static data_t shift_reg[FIR_DEPTH];
    acc_t acc;
    int i;
TDL:
    for (i = FIR_DEPTH - 1; i > 1; i = i - 2) {
        shift_reg[i] = shift_reg[i - 1];
        shift_reg[i - 1] = shift_reg[i - 2];
    }
    if (i == 1) {
        shift_reg[1] = shift_reg[0];
    }
    shift_reg[0] = din;
    acc = 0;
MAC:
    for (i = FIR_DEPTH - 1; i >= 0; i--) {
#pragma HLS unroll factor = 4
        acc += shift_reg[i] * coeffs[i];
    }
    *dout = (data_t)acc;
}
