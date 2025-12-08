#include "ap_fixed.h"
#include "fir.h"
#include <fstream>
#include <iostream>
#include <math.h>

void fir_tb(data_t *dout, coef_t coeffs[FIR_DEPTH], data_t din,
            data_t shift_reg[FIR_DEPTH]) {
    acc_t acc = 0;

    // shift input samples into shift_reg
    for (int i = FIR_DEPTH - 1; i > 0; i--) {
        shift_reg[i] = shift_reg[i - 1];
    }
    shift_reg[0] = din;

    // MAC
    for (int i = 0; i < FIR_DEPTH; i++) {
        acc += coeffs[i] * shift_reg[i];
    }
    *dout = (data_t)acc;
}

int main() {
    const double raw_coeffs[FIR_DEPTH] = {
        0.0017633376854217537, -0.0089975437204453,   -0.025549073043454072,
        -0.027653626828586075, -0.00289347322956272,  0.022747688381143393,
        0.01166404191990919,   -0.024490991441965808, -0.027051120000213442,
        0.02172055602572685,   0.05023537956495071,   -0.008052893002352082,
        -0.08743495563447104,  -0.03483050021216655,  0.1866158621358078,
        0.40240618185244714,   0.40240618185244714,   0.1866158621358078,
        -0.03483050021216655,  -0.08743495563447104,  -0.008052893002352082,
        0.05023537956495071,   0.02172055602572685,   -0.027051120000213442,
        -0.024490991441965808, 0.01166404191990919,   0.022747688381143393,
        -0.00289347322956272,  -0.027653626828586075, -0.025549073043454072,
        -0.0089975437204453,   0.0017633376854217537};
    coef_t coeffs[FIR_DEPTH];
    for (int i = 0; i < FIR_DEPTH; i++) {
        coeffs[i] = (coef_t)raw_coeffs[i];
    }

    // initialize an empty shift register for sw tb
    data_t tb_shift_reg[FIR_DEPTH];
    for (int i = 0; i < FIR_DEPTH; i++) {
        tb_shift_reg[i] = 0;
    }

    std::ofstream tbfile;
    tbfile.open("tbfile.txt");
    int num_errors = 0;

    for (int t = 0; t < NUM_SAMPLES; t++) {
        data_t raw_signal =
            0.5 * sin(2.0 * M_PI * ((double)F_PASS / F_SAMPLING) * t) +
            0.5 * sin(2.0 * M_PI * ((double)F_STOP / F_SAMPLING) * t);

        // SW testbench model
        data_t tb_out;
        fir_tb(&tb_out, coeffs, raw_signal, tb_shift_reg);

        // HLS hardware models
        data_t hw1_out;
        data_t hw2_out;
        data_t hw3_out;

        fir_opt1(&hw1_out, coeffs, raw_signal);
        fir_opt2(&hw2_out, coeffs, raw_signal);
        fir_opt3(&hw3_out, coeffs, raw_signal);

        tbfile << "\n" << t << ": ";
        if (tb_out != hw1_out || tb_out != hw2_out || tb_out != hw3_out) {
            tbfile << "FAIL!" << "\n";
            num_errors++;
        } else {
            tbfile << "PASS!" << "\n";
        }
        tbfile << "\t TB: " << tb_out << "\n";
        tbfile << "\tHW1: " << hw1_out << "\n";
        tbfile << "\tHW2: " << hw2_out << "\n";
        tbfile << "\tHW3: " << hw3_out << "\n";
    }

    tbfile << "\n TOTAL ERRORS: " << num_errors;
    tbfile.close();

    return 0;
}
