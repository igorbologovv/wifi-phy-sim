#include <cstdint>
#include "phy.h"
#include "qam.h"
#include <bitset>


MPDU create_mpdu(const std::string& message) {
    std::string bits = text_to_bits(message);
    uint16_t fake_fcs = 0xBEEF;
    return {bits, fake_fcs};
}

std::vector<std::complex<double>> transmit(const MPDU& mpdu, double snr_db) {
    std::vector<std::complex<double>> signal;
    for (size_t i = 0; i < mpdu.payload_bits.size(); i += 2) {
        auto bits = mpdu.payload_bits.substr(i, 2);
        auto sym = qam_encode(bits);
        signal.push_back(add_awgn(sym, snr_db));
    }
    return signal;
}

MPDU receive(const std::vector<std::complex<double>>& noisy_signal) {
    std::string bits;
    for (const auto& sym : noisy_signal) {
        bits += qam_decode(sym);
    }
    return {bits, 0xBEEF};
}

std::string text_to_bits(const std::string& input) {
    std::string bits;
    for (unsigned char c : input) {
        bits += std::bitset<8>(c).to_string();
    }
    return bits;
}

std::string bits_to_text(const std::string& bits) {
    std::string text;
    for (size_t i = 0; i < bits.size(); i += 8) {
        text += static_cast<char>(std::bitset<8>(bits.substr(i, 8)).to_ulong());
    }
    return text;
}
