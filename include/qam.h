#pragma once
#include <complex>
#include <string>
#include "mcs.h"


std::complex<double> modulate  (const std::string& bits, Mod m);
std::string          demodulate(const std::complex<double>& sym, Mod m);

std::complex<double> add_awgn(const std::complex<double>& s, double snr_db);
