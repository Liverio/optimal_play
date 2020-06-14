// ----------------------------------------------------
// Project     : Texas Hold'em hand evaluator
// Module Name : two_pair.c
// Author      : Javier Olivito (JO)
// ----------------------------------------------------
// Revisions:
// Date        Version     Author      Description
// 2020/06/14      1.0         JO      Initial release 
// ----------------------------------------------------

#include "two_pair.h"
#include "../kicker/kicker.h"

// ---------------------------------------
// -- Custom pair detector for two pair --
// ---------------------------------------
static char pair(u64 cards, char* rank){
    const u64 rank_mask = 0x0008004002001000;
    // --------------------
    // -- Pair detectors --
    // --------------------
    const u64 mask[6] = {0x0008004000000000,
                         0x0008000000001000,
                         0x0000000002001000,
                         0x0008000002000000,
                         0x0000004000001000,
                         0x0000004002000000};
    u64 rank_masked;
    char i, j;

    for (i = 0; i < 13; i++){
        // Mask non-i ranks
        rank_masked = cards & (rank_mask >> i);

        // Pair of i-rank
        for (j = 0; j < 6; j++){
            if (rank_masked == (mask[j] >> i)){
                *rank = 12 - i;
                return 1;
            }
        }
    }

    return 0;
}

char two_pair(u64 cards, u64* hand_value){
    const u64 rank_mask = 0x0008004002001000;
    u64 rank_masked;
    char rank_0, rank_1;
 
    // Highest ranked pair
    if (pair(cards, &rank_0)){
        // Mask pair rank
        rank_masked = cards & (~rank_mask >> (12 - rank_0));
        // Second higher ranked pair
        if (pair(rank_masked, &rank_1)){
            *hand_value = (1ULL << (32 + rank_0)) + (1ULL << (16 + rank_1));
            // Mask low pair cards to identify the kicker
            rank_masked &= ~rank_mask >> (12 - rank_1);
            
            *hand_value |= kicker_value(rank_masked, 1);
            return 1;
        }
    }

    return 0;
}
