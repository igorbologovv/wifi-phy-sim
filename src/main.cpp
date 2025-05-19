#include <iostream>
#include "phy.h"

int main() {
    std::string input = "PING";
    double snr = 10.0;

    // Step 1: Sender creates MPDU
    MPDU tx = create_mpdu(input);

    // Step 2: Transmit MPDU through noisy channel
    auto waveform = transmit(tx, snr);

    // Step 3: Receiver tries to recover MPDU
    MPDU rx = receive(waveform);

    // Step 4: Evaluate bit error rate
    int errors = 0;
    for (size_t i = 0; i < tx.payload_bits.size(); ++i) {
        if (tx.payload_bits[i] != rx.payload_bits[i]) errors++;
    }

    std::cout << "Decoded text: " << bits_to_text(rx.payload_bits) << "\n";
    std::cout << "Bit errors: " << errors << "/" << tx.payload_bits.size()
              << " (BER = " << static_cast<double>(errors) / tx.payload_bits.size() << ")\n";

    return 0;
}
