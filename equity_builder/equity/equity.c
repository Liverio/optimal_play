// ----------------------------------------------------
// Project     : Texas Hold'em hand evaluator
// Module Name : equity.c
// Author      : Javier Olivito (JO)
// ----------------------------------------------------
// Revisions:
// Date        Version     Author      Description
// 2020/06/14      1.0         JO      Initial release 
// ----------------------------------------------------

#include "equity.h"
#include "../hand_strength/hand_strength.h"
typedef uint64_t u64;

// -------------------
// -- Hand encoding --
// -------------------
// (Bit) 63 62 ... 51 50 | 47 ... 34 | 31 ... 18 | 15 ...  2
//       Ac Kc ... 2c Ac | Ad ... Ad | Ah ... Ah | As ... As

void deal_board(u64* hand_0, u64* hand_1){
    int card;
    char hits;

    hits = 0;
    while(hits < 5){
        // [0, 51]
        card = rand() % 52;
        if (!((1ULL << card) & (*hand_0 | *hand_1))){
            *hand_0 |= (1ULL << card);
            *hand_1 |= (1ULL << card);
            hits++;
        }
    }
}

char hand_outcome(u64 cards_0, u64 cards_1){
    u64 hand_value_0;
    u64 hand_value_1;

    hand_strength(cards_0, &hand_value_0);
    hand_strength(cards_1, &hand_value_1);

    if (hand_value_0 > hand_value_1)
        return 1;
    if (hand_value_0 < hand_value_1)
        return -1;

    // Split
    return 0;
}

void hand_encoder(unsigned char hand_0_idx, unsigned char hand_1_idx, u64* hand_0, u64* hand_1){
    unsigned char suit;
    unsigned char suit_card_0;

    // ------------------------
    // -- hand_0: first card --
    // ------------------------
    // [0, 3]
    suit = rand() % 4;
    // First card of hand_0 is unconstrained
    *hand_0 = 1ULL << (13 * suit + hand_cards_idx[hand_0_idx][0]);
    
    // --------------------------
    // -- hand_0 : second card --
    // --------------------------
    // -- Suited --
    if (hand_0_idx >= HANDS_OFFSUITED){
        *hand_0 |= 1ULL << (13 * suit + hand_cards_idx[hand_0_idx][1]);
    }
    // -- Offsuited --
    else{
        suit_card_0 = suit;
        suit = rand() % 4;
        while(suit == suit_card_0)
            suit = rand() % 4;

        *hand_0 |= 1ULL << (13 * suit + hand_cards_idx[hand_0_idx][1]);
    }
    
    // ------------------------
    // -- hand_1: first card --
    // ------------------------
    suit = rand() % 4;
    // -- Suited --
    if (hand_1_idx >= HANDS_OFFSUITED){
        // When suited, suit choosen for card_0 must allow picking card_1 (i.e., not picked in hand_0)
        while((*hand_0 & (1ULL << (13 * suit + hand_cards_idx[hand_1_idx][0]))) ||
              (*hand_0 & (1ULL << (13 * suit + hand_cards_idx[hand_1_idx][1])))){
            suit = rand() % 4;
        }
    }
    // -- Offsuited --
    else{
        while(*hand_0 & (1ULL << (13 * suit + hand_cards_idx[hand_1_idx][0]))){
            suit = rand() % 4;
        }
    }
    
    *hand_1 = 1ULL << (13 * suit + hand_cards_idx[hand_1_idx][0]);

    // --------------------------
    // -- hand_1 : second card --
    // --------------------------
    suit_card_0 = suit;
    // -- Suited --
    if (hand_1_idx >= HANDS_OFFSUITED){
        // Force same suit than card_0
        *hand_1 |= 1ULL << (13 * suit + hand_cards_idx[hand_1_idx][1]);
    }
    // -- Offsuited --
    else{
        suit = rand() % 4;
        while(((*hand_0 | *hand_1) & (1ULL << (13 * suit + hand_cards_idx[hand_1_idx][1]))) ||
              (suit_card_0 == suit)){
            suit = rand() % 4;
        }
            
        *hand_1 |= 1ULL << (13 * suit + hand_cards_idx[hand_1_idx][1]);
    }
}

float allin_equity(unsigned char hand_0_idx, unsigned char hand_1_idx){
    int cum_allin_equity;
    u64 hand_0_sim;
    u64 hand_1_sim;
    int i;  

    cum_allin_equity = 0;
    for (i = 0; i < EQUITY_SIMS; i++){
        hand_encoder(hand_0_idx, hand_1_idx, &hand_0_sim, &hand_1_sim);
        deal_board(&hand_0_sim, &hand_1_sim);

        cum_allin_equity += hand_outcome(hand_0_sim, hand_1_sim);
    }

    return (float)(cum_allin_equity) / (float)(EQUITY_SIMS);
}

void allin_equity_builder(){
    unsigned char hand_0_idx;
    unsigned char hand_1_idx;
    FILE* f_allin_equity;

    f_allin_equity = fopen("allin_equity.csv", "w");
    for (hand_0_idx = 0; hand_0_idx < HANDS_OFFSUITED + HANDS_SUITED; hand_0_idx++){
        for (hand_1_idx = 0; hand_1_idx < HANDS_OFFSUITED + HANDS_SUITED; hand_1_idx++){
            fprintf(f_allin_equity, "%.4f,", allin_equity(hand_0_idx, hand_1_idx));
        }
    }
    fclose(f_allin_equity);
}

