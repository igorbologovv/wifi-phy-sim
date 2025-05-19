#pragma once
#include <vector>
#include <complex>

/*  ───────────────────────────────────
    OFDM helper: IFFT/FFT + noise
    ─────────────────────────────────── */

std::vector<std::complex<double>>
ifft(const std::vector<std::complex<double>>& freq);   // freequence  time

std::vector<std::complex<double>>
fft(const std::vector<std::complex<double>>& time);    // time  frequence

void add_awgn(std::vector<std::complex<double>>& sig, double snr_db);
