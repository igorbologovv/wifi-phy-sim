#include "qam.h"
#include <map>
#include <cmath>
#include <random>

/// Coordinates for certain bit combination
static const std::map<std::string,std::complex<double>> map_bpsk = {
    {"0",{ -1.0, 0.0 }}, {"1",{ 1.0, 0.0 }}
};
static const std::map<std::string,std::complex<double>> map_qpsk = {
    {"00",{ -1.0,-1.0 }}, {"01",{ -1.0, 1.0 }},
    {"11",{  1.0, 1.0 }}, {"10",{  1.0,-1.0 }}
};
static const std::map<std::string,std::complex<double>> map_qam16 = {
    {"0000",{-3,-3}},{"0001",{-3,-1}},{"0011",{-3, 1}},{"0010",{-3, 3}},
    {"0100",{-1,-3}},{"0101",{-1,-1}},{"0111",{-1, 1}},{"0110",{-1, 3}},
    {"1100",{ 1,-3}},{"1101",{ 1,-1}},{"1111",{ 1, 1}},{"1110",{ 1, 3}},
    {"1000",{ 3,-3}},{"1001",{ 3,-1}},{"1011",{ 3, 1}},{"1010",{ 3, 3}}
};
static const std::map<Mod,
        const std::map<std::string,std::complex<double>>&> maps = {
    {Mod::BPSK , map_bpsk},
    {Mod::QPSK , map_qpsk},
    {Mod::QAM16, map_qam16},
};

std::complex<double> modulate(const std::string& bits, Mod m)
{
    return maps.at(m).at(bits);
}

std::string demodulate(const std::complex<double>& sym, Mod m)
{
    double best = 1e9; std::string closest;
    for (const auto& [b,pt] : maps.at(m)) {
        double d = std::norm(sym - pt);
        if (d < best) { best = d; closest = b; }
    }
    return closest;
}

std::complex<double> add_awgn(const std::complex<double>& s, double snr_db)
{
    static std::mt19937 gen{std::random_device{}()};
    double snr = std::pow(10.0, snr_db / 10.0);
    double sigma = std::sqrt(1.0 / (2.0 * snr));          // Es = 1
    std::normal_distribution<double> n(0.0, sigma);
    return s + std::complex<double>(n(gen), n(gen));
}
