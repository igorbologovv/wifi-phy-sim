#pragma once
#include <vector>

/* Modulation — bit amount per symbol */
enum class Mod { BPSK = 1, QPSK = 2, QAM16 = 4 };


struct MCS {
    int     index;        // number
    Mod     mod;          // modulation type
    double  code_rate;    // 0.5, 0.75 …
    double  ebn0_req_db;  // required SNR dB 
};

const std::vector<MCS>& mcs_table();          // returns singleton
const MCS&              choose_mcs(double snr_db);

int bits_per_symbol(Mod m);
