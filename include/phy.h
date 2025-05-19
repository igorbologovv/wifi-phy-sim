#pragma once
#include <vector>
#include <complex>
#include <string>
#include "mcs.h"


struct MPDU { std::string payload_bits; };

MPDU create_mpdu(const std::string& ascii_text);

std::vector<std::complex<double>>
transmit(const MPDU& mpdu, double snr_db, const MCS& mcs);

MPDU receive(const std::vector<std::complex<double>>& sig, const MCS& mcs);

std::string text_to_bits(const std::string& s);
std::string bits_to_text(const std::string& bits);
