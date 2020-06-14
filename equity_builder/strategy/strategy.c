// Hand evaluation in Texas Hold'em
// Author   : Javier Olivito
// Date     : 2-Jun-2020
// Releases : 1.0 Initial release

#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "strategy.h"
#include "../equity/equity.h"

void init_strategy(float* strategy){
    unsigned char hand;

    for (hand = 0; hand < HANDS_OFFSUITED + HANDS_SUITED; hand++){
        strategy[hand] = (float)rand() / (float)RAND_MAX;
    }
}

void update_sb_strategy(float* strategy_sb, float* strategy_bb, float stack, float* precomputed_equity, float weight){
    float total_combos;
    float cum_equity;
    unsigned char hand_sb, hand_bb;

    for (hand_sb = 0; hand_sb < HANDS_OFFSUITED + HANDS_SUITED; hand_sb++){
        // -------------------------------------------
        // -- Get expectation against bb's strategy --
        // -------------------------------------------
        total_combos = 0;
        cum_equity   = 0;

        for (hand_bb = 0; hand_bb < HANDS_OFFSUITED + HANDS_SUITED; hand_bb++){
            total_combos += (float)(combos[hand_bb]);
            // -------------------------------------------
            // -- BB's strategy is (potentially) mixed ---
            // -------------------------------------------
            cum_equity += ((1 - strategy_bb[hand_bb]) * (float)(combos[hand_bb]) * SB_PUSH_FOLD_REWARD) +
                          ((    strategy_bb[hand_bb]) * (float)(combos[hand_bb]) * precomputed_equity[hand_sb * (HANDS_OFFSUITED + HANDS_SUITED) + hand_bb] * stack);
        }

        // Select the most valued move against the bb strategy and update the strategy
        strategy_sb[hand_sb] = cum_equity / total_combos > SB_FOLD_REWARD ? (1 - weight) * strategy_sb[hand_sb] + weight * 1.0 :
                                                                            (1 - weight) * strategy_sb[hand_sb];
    }
}

void update_bb_strategy(float* strategy_sb, float* strategy_bb, float stack, float* precomputed_equity, float weight){
    float total_combos;
    float cum_equity;
    unsigned char hand_sb, hand_bb;

    for (hand_bb = 0; hand_bb < HANDS_OFFSUITED + HANDS_SUITED; hand_bb++){
        // -------------------------------------------
        // -- Get expectation against sb's strategy --
        // -------------------------------------------
        total_combos = 0;
        cum_equity   = 0;

        for (hand_sb = 0; hand_sb < HANDS_OFFSUITED + HANDS_SUITED; hand_sb++){
            total_combos += (float)(combos[hand_sb]) * strategy_sb[hand_sb];
            // -------------------------------------------
            // -- SB's strategy is (potentially) mixed ---
            // -------------------------------------------
            cum_equity += ((float)(combos[hand_sb]) * strategy_sb[hand_sb])                         *
                           precomputed_equity[hand_bb * (HANDS_OFFSUITED + HANDS_SUITED) + hand_sb] *
                           stack;
        }

        // Select the most valued move against the bb strategy and update the strategy
        strategy_bb[hand_bb] = cum_equity / total_combos > BB_FOLD_REWARD ? (1 - weight) * strategy_bb[hand_bb] + weight * 1.0 :
                                                                            (1 - weight) * strategy_bb[hand_bb];
    }
}

void find_nash_equilibrium(float* push_threshold, float* call_threshold){
    float* precomputed_equity;
    float strategy_sb[HANDS_OFFSUITED + HANDS_SUITED];
    float strategy_bb[HANDS_OFFSUITED + HANDS_SUITED];
    unsigned char hand;
    float stack;
    
    precomputed_equity = (float*)malloc((HANDS_OFFSUITED + HANDS_SUITED) * (HANDS_OFFSUITED + HANDS_SUITED) * sizeof(float));
    load_allin_equity(precomputed_equity);
    
    for (hand = 0; hand < HANDS_OFFSUITED + HANDS_SUITED; hand++){
        push_threshold[hand] = 15.0;
        call_threshold[hand] = 15.0;
    }

    for (stack = 15.0; stack > 1.5; stack -= 0.1){
printf("%.1f\n", stack);
        init_strategy(strategy_sb);
        init_strategy(strategy_bb);
      
        int n;
        float weight;
        
        // ---------------------------------------------------------
        // -- Converge to nash equilibrium applying fictious play --
        // ---------------------------------------------------------
        for (n = 2; n < 20000; n++){
            weight = 1 / (float)n;
            update_sb_strategy(strategy_sb, strategy_bb, stack, precomputed_equity, weight);
            update_bb_strategy(strategy_sb, strategy_bb, stack, precomputed_equity, weight);
        }
        
        // ----------------------------------
        // -- Find the push/fold threshold --
        // ----------------------------------
        for (hand = 0; hand < HANDS_OFFSUITED + HANDS_SUITED; hand++){
            if (strategy_sb[hand] < 0.5){
                push_threshold[hand] = stack;
            }
            if (strategy_bb[hand] < 0.5){
                call_threshold[hand] = stack;
            }     
        }
    }
    
    free(precomputed_equity);
}
