#include <iostream>
#include <bitset>
#include <vector>
#include "qam.h"

std::string text_to_bits(const std::string& input) {
    std::string bits;
    for (unsigned char c : input) {
        bits += std::bitset<8>(c).to_string();
    }
    return bits;
}

std::string bits_to_text(const std::string& bits) {
    std::string result;
    for (size_t i = 0; i < bits.size(); i += 8) {
        result += static_cast<char>(std::bitset<8>(bits.substr(i, 8)).to_ulong());
    }
    return result;
}

int main() {
    std::string input = "PING";
    double snr = 10.0;

    std::string bits = text_to_bits(input);
    std::cout << "Исходные биты: " << bits << "\n";

    // Разбить на 2-битные символы
    std::vector<std::complex<double>> encoded;
    for (size_t i = 0; i < bits.size(); i += 2) {
        std::string b = bits.substr(i, 2);
        encoded.push_back(add_awgn(qam_encode(b), snr));
    }

    // Распознать символы обратно
    std::string decoded_bits;
    for (const auto& s : encoded) {
        decoded_bits += qam_decode(s);
    }

    std::cout << "Принятые биты:  " << decoded_bits << "\n";
    std::cout << "Расшифровка:    " << bits_to_text(decoded_bits) << "\n";

    // BER
    int errors = 0;
    for (size_t i = 0; i < bits.size(); ++i) {
        if (bits[i] != decoded_bits[i]) errors++;
    }
    std::cout << "Ошибок: " << errors << " из " << bits.size() << " бит (BER = "
              << static_cast<double>(errors) / bits.size() << ")\n";

    return 0;
}
