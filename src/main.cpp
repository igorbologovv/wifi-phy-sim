#include <iostream>
#include <iomanip>
#include <vector>
#include <complex>
#include "qam.h"
#include "ofdm.h"

int main(){
    const size_t N = 64;          // number of subcarriers (small value for clarity)
    double snr_db = 10.0;        // SNR in the channel

    /* ── 1. Create QPSK points for each subcarrier ───────────── */
    std::vector<std::complex<double>> freq(N);
    std::vector<std::string> bits = {"00","01","11","10","00","01","11","10"};
    for(size_t i=0;i<N;++i)
        freq[i] = modulate(bits[i], Mod::QPSK);

    std::cout << " Frequency domain (subcarriers):\n";
    for(auto& s:freq) std::cout<<s<<" "; std::cout<<"\n";

    /* ── 2. IFFT -> time-domain signal ────────────────────────── */
    auto time = ifft(freq);
    std::cout << "\n Time-domain signal after IFFT:\n";
    for(auto& s:time) std::cout<<s<<" "; std::cout<<"\n";

    /* ── 3. Add AWGN ─────────────────────────────────────────── */
    add_awgn(time, snr_db);

    /* ── 4. FFT -> recover frequency domain ───────────────────── */
    auto recv_freq = fft(time);
    std::cout << "\n Recovered subcarriers after FFT:\n";
    for(auto& s:recv_freq) std::cout<<s<<" "; std::cout<<"\n";

    /* ── 5. Demodulation and BER ─────────────────────────────── */
    int errs=0;
    for(size_t i=0;i<N;++i){
        std::string dec = demodulate(recv_freq[i], Mod::QPSK);
        if(dec!=bits[i]) ++errs;
    }
    std::cout << "\nErroneous subcarriers: "<<errs<<" / "<<N<<"\n";
}
