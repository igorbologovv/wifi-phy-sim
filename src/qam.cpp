#include "qam.h"
#include <map>
#include <cmath>
#include <random>

static const std::map<std::string, std::complex<double>> qam_map = {
    {"00", {-1.0, -1.0}},
    {"01", {-1.0,  1.0}},
    {"11", { 1.0,  1.0}},
    {"10", { 1.0, -1.0}}
};

std::complex<double> qam_encode(const std::string& bits) {
    return qam_map.at(bits);
}

std::string qam_decode(const std::complex<double>& sym) {
    double min_dist = 1e9;
    std::string closest;
    for (const auto& [bits, point] : qam_map) {
        double dist = std::norm(sym - point);
        if (dist < min_dist) {
            min_dist = dist;
            closest = bits;
        }
    }
    return closest;
}

std::complex<double> add_awgn(const std::complex<double>& sym, double snr_db) {
    static std::mt19937 rng{std::random_device{}()};
    double snr = std::pow(10.0, snr_db / 10.0);
    double sigma = std::sqrt(1.0 / (2.0 * snr));
    std::normal_distribution<double> dist(0.0, sigma);
    return sym + std::complex<double>(dist(rng), dist(rng));
}
