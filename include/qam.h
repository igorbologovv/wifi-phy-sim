#pragma once
#include <vector>
#include <complex>
#include <string>

// QAM созвездие: маппинг битов <-> точки
std::complex<double> qam_encode(const std::string& bits);
std::string qam_decode(const std::complex<double>& symbol);

// Функция добавления шума
std::complex<double> add_awgn(const std::complex<double>& sym, double snr_db);
