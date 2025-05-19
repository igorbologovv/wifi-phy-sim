#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <complex>

// MAC Protocol Data Unit
struct MPDU {
    std::string payload_bits;  // Binary string (e.g. "010011")
    uint16_t fcs;              // Frame Check Sequence (fake for now)
};

// Create MPDU from plain text
MPDU create_mpdu(const std::string& message);

// Transmit MPDU through AWGN channel (symbol stream with noise)
std::vector<std::complex<double>> transmit(const MPDU& mpdu, double snr_db);

// Receive MPDU from noisy signal
MPDU receive(const std::vector<std::complex<double>>& noisy_signal);

// Utils
std::string text_to_bits(const std::string& input);
std::string bits_to_text(const std::string& bits);
