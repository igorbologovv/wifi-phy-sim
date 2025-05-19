#pragma once
#include <complex>
#include <string>

// Map 2-bit string to QAM symbol (QPSK)
std::complex<double> qam_encode(const std::string& bits);

// Decode noisy symbol to nearest constellation point
std::string qam_decode(const std::complex<double>& symbol);

// Add AWGN noise to a symbol (SNR in dB)
std::complex<double> add_awgn(const std::complex<double>& sym, double snr_db);

