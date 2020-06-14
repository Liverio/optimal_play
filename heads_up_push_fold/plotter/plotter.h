// ----------------------------------------------------
// Project     : Heads-up push/fold solver
// Module Name : plotter.h
// Author      : Javier Olivito (JO)
// ----------------------------------------------------
// Revisions:
// Date        Version     Author      Description
// 2020/06/14      1.0         JO      Initial release 
// ----------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

void chart_formatter(float* push_threshold, float* call_threshold);
void track_convergence_dynamics(float* strategy_sb, float* strategy_bb, 
                                float* dynamic_sb,  float* dynamic_bb,  int iter);
void dump_convergence_dynamics(float* dynamics_sb,  float* dynamics_bb,  int iters, float stack);