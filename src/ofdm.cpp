#include "ofdm.h"
#include <unsupported/Eigen/FFT>
#include <random>
#include <cmath>

static Eigen::FFT<double> g_fft;

/* frequency domain -> time domain (IFFT) */
std::vector<std::complex<double>>
ifft(const std::vector<std::complex<double>>& freq)
{
    std::vector<std::complex<double>> time;
    g_fft.inv(time, freq);
    return time;
}

/* time domain -> frequency domain (FFT) */
std::vector<std::complex<double>>
fft(const std::vector<std::complex<double>>& time)
{
    std::vector<std::complex<double>> freq;
    g_fft.fwd(freq, time);
    return freq;
}

/* AWGN: SNR is given relative to symbol energy Es = 1 */
void add_awgn(std::vector<std::complex<double>>& sig, double snr_db)
{
    static std::mt19937 gen{std::random_device{}()};
    double snr  = std::pow(10.0, snr_db / 10.0);
    double sigma = std::sqrt(1.0 / (2.0 * snr));        // Es=1

    std::normal_distribution<double> n(0.0, sigma);
    for (auto& s : sig)
        s += std::complex<double>(n(gen), n(gen));
}
