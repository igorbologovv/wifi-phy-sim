#include <iostream>
#include <iomanip>
#include "phy.h"
#include "mcs.h"

int main()
{
    std::string input = "PING";
    double snr_db     = 4.0;               

    /* 1 — choose apropriate MCS */
    const MCS& mcs = choose_mcs(snr_db);

    /* 2 — create MPDU and transfer» */
    MPDU tx  = create_mpdu(input);
    auto wf  = transmit(tx, snr_db, mcs);

    /* 3 — recieve */
    MPDU rx  = receive(wf, mcs);

    /* 4 — count errors*/
    int err = 0;
    for (size_t i=0; i<tx.payload_bits.size(); ++i)
        if (tx.payload_bits[i] != rx.payload_bits[i]) ++err;

    double ber = double(err) / tx.payload_bits.size();

    std::cout << "SNR " << snr_db << " dB  →  MCS" << mcs.index
              << "  (" << bits_per_symbol(mcs.mod) << " bit/sim, R="
              << mcs.code_rate << ")\n"
              << "Decoded: " << bits_to_text(rx.payload_bits) << "\n"
              << "Errors: " << err << "/" << tx.payload_bits.size()
              << "   BER = " << std::scientific << ber << "\n";
    return 0;
}
