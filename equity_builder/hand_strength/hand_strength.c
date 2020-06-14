// ----------------------------------------------------
// Project     : Texas Hold'em hand evaluator
// Module Name : hand_strength.c
// Author      : Javier Olivito (JO)
// ----------------------------------------------------
// Revisions:
// Date        Version     Author      Description
// 2020/06/14      1.0         JO      Initial release 
// ----------------------------------------------------

#include "hand_strength.h"
#include "full_house/full_house.h"
#include "two_pair/two_pair.h"
#include "kicker/kicker.h"

// ---------------------
// -- Hand evaluation --
// ---------------------
char straight_flush(u64 cards, u64* hand_value){
    const u64 mask_0 = 0x000F800000000000;
    const u64 mask_1 = 0x0008078000000000;
    char i, j;
    char offset = 0;

    for (i = 0; i < 4; i++){
        for (j = 0; j < 9; j++){
            if ((cards & (mask_0 >> (offset + j))) == (mask_0 >> (offset + j))){
                // rank_0
                *hand_value = 12 - j;
                return 1;
            }
        }
        // 5-4-3-2-A
        if ((cards & (mask_1 >> offset)) == (mask_1 >> offset)){
            // rank_0
            *hand_value = 3;
            return 1;
        }
        offset += 13;
    }

    return 0;
}

char four_of_a_kind(u64 cards, u64* hand_value){
    const u64 mask = 0x0008004002001000;
    u64 cards_masked;
    char i;
   
    for (i = 0; i < 13; i++){
        if ((cards & (mask >> i)) == (mask >> i)){
            // rank_1
            *hand_value = 1ULL << (16 + (12 - i));
            
            // Mask four of kind cards to indentify the kicker
            cards_masked = cards & (~mask >> i);
            *hand_value |= kicker_value(cards_masked, 1);
            return 1;
        }
    }

    return 0;
}

char flush(u64 cards, u64* hand_value){
    const u64 mask = 0x0008000000000000;
    char flush_count;
    char i, j;
    char suit_offset = 0;

    for (i = 0; i < 4; i++){
        *hand_value = 0;
        flush_count = 0;
        for (j = 0; j < 13; j++){
            if (cards & (mask >> (suit_offset + j))){
                flush_count++;
                // rank_0
                *hand_value |= 1ULL << (12 - j);
                if (flush_count == 5)
                    return 1;
            }
        }
        suit_offset += 13;
    }
    return 0;
}

char straight(u64 cards, u64* hand_value){
    const u64 rank_mask = 0x0008004002001000;
    const u64 mask_0    = 0x000F800000000000;
    const u64 mask_1    = 0x0008078000000000;
    u64 cards_no_suit = 0;
    char i;

    // Suits ORed
    for (i = 0; i < 13; i++){
        if (cards & (rank_mask >> i)){
            cards_no_suit |= rank_mask >> i;
        }
    }

    // Straights from A-K-Q-J-T to 6-5-4-3-2
    for (i = 0; i < 9; i++){
        if ((cards_no_suit & (mask_0 >> i)) == (mask_0 >> i)){
            // rank_0
            *hand_value = 12 - i;
            return 1;
        }
    }
    // 5-4-3-2-A
    if ((cards_no_suit & mask_1) == mask_1){
        // rank_0
        *hand_value = 3;
        return 1;
    }

    return 0;
}

char three_of_a_kind(u64 cards, u64* hand_value){
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
                // rank_1
                *hand_value = 1ULL << (16 + (12 - i));
                rank_masked = cards & (~mask[j] >> i);
                // rank_0
                *hand_value |= kicker_value(rank_masked, 2);
                return 1;
            }
        }
    }

    return 0;
}

char pair(u64 cards, u64* hand_value){
    const u64 rank_mask = 0x0008004002001000;
    // --------------------
    // -- Pair detectors --
    // --------------------
    const u64 mask[6] = {0x0008004000000000,
                         0x0008000002000000,
                         0x0008000000001000,
                         0x0000004002000000,
                         0x0000004000001000,
                         0x0000000002001000
                        };
    u64 rank_masked;
    char i, j;

    for (i = 0; i < 13; i++){
        // Mask non-i ranks
        rank_masked = cards & (rank_mask >> i);

        // Pair of i-rank
        for (j = 0; j < 6; j++){
            if (rank_masked == (mask[j] >> i)){
                // rank_1
                *hand_value = 1ULL << (16 + (12 - i));
                
                // rank_0
                rank_masked = cards & (~mask[j] >> i);
                *hand_value |= kicker_value(rank_masked, 3);
                return 1;
            }
        }
    }

    return 0;
}

char high_card(u64 cards, u64* hand_value){
    const u64 rank_mask = 0x0008004002001000;
    char i;
    char found = 0;

    *hand_value = 0;
    // Suits ORed
    for (i = 0; i < 13; i++){
        if (cards & (rank_mask >> i)){
            *hand_value |= 1ULL << (12 - i);
            found++;
            if (found == 5){
                return 1;
            }
        }
    }

    return 0;
}

// -------------------
// -- Hand strength --
// -------------------
void hand_strength(u64 cards, u64* hand_value){
    if (straight_flush(cards, hand_value)){
        *hand_value |= 1ULL << (48 + 8);
        return ;
    }
    if (four_of_a_kind(cards, hand_value)){
        *hand_value |= 1ULL << (48 + 7);
        return ;
    }
    if (full_house(cards, hand_value)){
        *hand_value |= 1ULL << (48 + 6);
        return ;
    }
    if (flush(cards, hand_value)){
        *hand_value |= 1ULL << (48 + 5);
        return ;
    }
    if (straight(cards, hand_value)){
        *hand_value |= 1ULL << (48 + 4);
        return;
    }
    if (three_of_a_kind(cards, hand_value)){
        *hand_value |= 1ULL << (48 + 3);
        return ;
    }
    if (two_pair(cards, hand_value)){
        *hand_value |= 1ULL << (48 + 2);
        return ;
    }
    if (pair(cards, hand_value)){
        *hand_value |= 1ULL << (48 + 1);
        return ;
    }
    high_card(cards, hand_value);
    *hand_value |= 1ULL << (48 + 0);
    return ;
}
