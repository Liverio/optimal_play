// ----------------------------------------------------
// Project     : Heads-up push/fold solver
// Module Name : strategy.h
// Author      : Javier Olivito (JO)
// ----------------------------------------------------
// Revisions:
// Date        Version     Author      Description
// 2020/06/14      1.0         JO      Initial release 
// ----------------------------------------------------

#ifndef STRATEGY_H
#define STRATEGY_H

#define SB_FOLD_REWARD      -0.5f
#define SB_PUSH_FOLD_REWARD  1.0f
#define BB_FOLD_REWARD      -1.0f

#define FICTIOUS_PLAY_ITERS 50000

void find_nash_equilibrium(float* push_threshold, float* call_threshold);

#endif
