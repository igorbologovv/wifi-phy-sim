#include "phy.h"
#include "qam.h"
#include <bitset>

/* Simple «code-repeat x2» for R=1/2 */
static std::string repeat2(const std::string& b)
{
    std::string out;
    out.reserve(b.size()*2);
    for (char c : b) { 
        out.push_back(c);
        out.push_back(c);
     }
    return out;
}
static std::string derpt2(const std::string& b)   /* majority vote skip */
{
    std::string out; out.reserve(b.size()/2);
    for (size_t i=0;i<b.size(); i+=2) out.push_back(b[i]);
    return out;
}



/// ===START section ===  This part is for coding and decoding text// util functions
/* Text  -> bit  */
std::string text_to_bits(const std::string& s)
{
    std::string b;
    for (unsigned char c : s)
        b += std::bitset<8>(c).to_string();
    return b;
}
/* bits -> ASCII */
std::string bits_to_text(const std::string& b)
{
    std::string t;
    for (size_t i=0;i<b.size(); i+=8)
        t += static_cast<char>(std::bitset<8>(b.substr(i,8)).to_ulong());
    return t;
}
//// END section  =====



MPDU create_mpdu(const std::string& ascii_text)
{
    return { text_to_bits(ascii_text) };
}

std::vector<std::complex<double>>
transmit(const MPDU& mpdu, double snr_db, const MCS& mcs)
{
    std::string bits = mpdu.payload_bits;
    if (mcs.code_rate == 0.5) bits = repeat2(bits);          // «FEC»

    const int k = bits_per_symbol(mcs.mod);
    std::vector<std::complex<double>> sig; sig.reserve((bits.size()+k-1)/k);

    for (size_t i=0; i<bits.size(); i+=k) {
        std::string chunk = bits.substr(i, k);
        if (chunk.size() < size_t(k)) chunk.append(k - chunk.size(), '0'); // padding
        auto s = modulate(chunk, mcs.mod);
        sig.push_back(add_awgn(s, snr_db));
    }
    return sig;
}

MPDU receive(const std::vector<std::complex<double>>& sig, const MCS& mcs)
{
    std::string bits;
    for (auto s : sig) bits += demodulate(s, mcs.mod);
    if (mcs.code_rate == 0.5) bits = derpt2(bits);
    return { bits };
}
