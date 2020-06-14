// Hand evaluation in Texas Hold'em
// Author   : Javier Olivito
// Date     : 2-Jun-2020
// Releases : 1.0 Initial release

#ifndef STRATEGY_H
#define STRATEGY_H

#define SB_FOLD_REWARD      -0.5f
#define SB_PUSH_FOLD_REWARD  1.0f
#define BB_FOLD_REWARD      -1.0f

void init_strategy(float* strategy);
void update_sb_strategy(float* strategy_sb, float* strategy_bb, float stack, float* precomputed_equity, float weight);
void update_bb_strategy(float* strategy_sb, float* strategy_bb, float stack, float* precomputed_equity, float weight);
void find_nash_equilibrium(float* push_threshold, float* call_threshold);

#endif
