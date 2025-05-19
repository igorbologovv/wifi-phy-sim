#include "mcs.h"

/* MCS - table */
static std::vector<MCS> tbl = {
    { 0, Mod::BPSK , 0.50,  4.0 },
    { 1, Mod::QPSK , 0.50,  7.0 },
    { 2, Mod::QPSK , 0.75,  9.0 },
    { 3, Mod::QAM16, 0.75, 12.0 },
};

const std::vector<MCS>& mcs_table() { return tbl; }

const MCS& choose_mcs(double snr_db)
{
    /* From fast to slow */
    for (auto it = tbl.rbegin(); it != tbl.rend(); ++it)
        if (snr_db >= it->ebn0_req_db) return *it;
    return tbl.front();
}

int bits_per_symbol(Mod m) { return static_cast<int>(m); }
