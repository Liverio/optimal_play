// ----------------------------------------------------
// Project     : Texas Hold'em hand evaluator
// Module Name : full_house.c
// Author      : Javier Olivito (JO)
// ----------------------------------------------------
// Revisions:
// Date        Version     Author      Description
// 2020/06/14      1.0         JO      Initial release 
// ----------------------------------------------------
#include "full_house.h"

// ----------------------------------------------------
// -- Custom three_of_a_kind detector for full_house --
// ----------------------------------------------------
static char three_of_a_kind(u64 cards, char* rank){
    const u64 rank_mask = 0x0008004002001000;
    // -------------------------------------
    // -- Masks to detect three of a kind --
    // -------------------------------------
    const u64 mask[4] = {0x0008004002000000,
                         0x0008004000001000,
                         0x0008000002001000,
                         0x0000004002001000};
    u64 rank_masked;
    char i, j;

    for (i = 0; i < 13; i++){
        // Mask non-i ranks
        rank_masked = cards & (rank_mask >> i);

        // Three of a kind of i-rank
        for (j = 0; j < 4; j++){
            if (rank_masked == (mask[j] >> i)){
                *rank = 12 - i;
                return 1;
            }
        }
    }

    return 0;
}

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

char full_house(u64 cards, u64* hand_value){
    char rank_0, rank_1;

    if (three_of_a_kind(cards, &rank_0)){
        if (pair(cards, &rank_1)){
            *hand_value  = 1ULL << (32 + rank_0);
            *hand_value |= 1ULL << (16 + rank_1);
            return 1;
        }
    }

    return 0;
}
