// ----------------------------------------------------
// Project     : Heads-up push/fold solver
// Module Name : plotter.c
// Author      : Javier Olivito (JO)
// ----------------------------------------------------
// Revisions:
// Date        Version     Author      Description
// 2020/06/14      1.0         JO      Initial release 
// ----------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../equity/equity.h"

// +: Suited
// -: Offsuited

//   A K Q J T 9 8 7 6 5 4 3 2
// A - + + + + + + + + + + + + 
// K - - + + + + + + + + + + + 
// Q - - - + + + + + + + + + +
// J - - - - + + + + + + + + +
// T - - - - - + + + + + + + +
// 9 - - - - - - + + + + + + +
// 8 - - - - - - - + + + + + +
// 7 - - - - - - - - + + + + +
// 6 - - - - - - - - - + + + +
// 5 - - - - - - - - - - + + +
// 4 - - - - - - - - - - - + +
// 3 - - - - - - - - - - - - +
// 2 - - - - - - - - - - - - -

void chart_formatter(float* push_threshold, float* call_threshold){
    float push_chart[13][13];
    float call_chart[13][13];
    unsigned char element;
    unsigned char row, column;

    // Offsuited
    element = 0;
    for (column = 0; column < 13; column++){
        for (row = column; row < 13; row++){
            push_chart[row][column] = push_threshold[element];
            call_chart[row][column] = call_threshold[element];
            element++;
        }
    }

    // Suited
    for (row = 0; row < 13; row++){
        for (column = row + 1; column < 13; column++){
            push_chart[row][column] = push_threshold[element];
            call_chart[row][column] = call_threshold[element];
            element++;
        }
    }

    FILE* f_nash_push;
    FILE* f_nash_call;

    f_nash_push = fopen("nash_sb.csv", "w");
    f_nash_call = fopen("nash_bb.csv", "w");

    for (row = 0; row < 13; row++){
        for (column = 0; column < 13; column++){
            fprintf(f_nash_push, "%.1f", push_chart[row][column]);
            fprintf(f_nash_call, "%.1f", call_chart[row][column]);
            
            if (!(row == 12 && column == 12)){
                fprintf(f_nash_push, ",");
                fprintf(f_nash_call, ",");
            }
        }
    }
    
    fclose(f_nash_push);
    fclose(f_nash_call);
}

void track_convergence_dynamics(float* strategy_sb, float* strategy_bb, 
                                float* dynamic_sb,  float* dynamic_bb,  int iter){
    int offset;

    offset = (HANDS_OFFSUITED + HANDS_SUITED) * iter;
    memcpy(&(dynamic_sb[offset]), strategy_sb, (HANDS_OFFSUITED + HANDS_SUITED) * sizeof(float));
    memcpy(&(dynamic_bb[offset]), strategy_bb, (HANDS_OFFSUITED + HANDS_SUITED) * sizeof(float));
}

void dump_convergence_dynamics(float* dynamics_sb,  float* dynamics_bb,  int iters, float stack){
    FILE* f_sb_dynamics;
    FILE* f_bb_dynamics;
    char file_name[100];

    sprintf(file_name, "sb_dynamics_%.1f.csv", stack);
    f_sb_dynamics = fopen(file_name, "w");

    sprintf(file_name, "bb_dynamics_%.1f.csv", stack);
    f_bb_dynamics = fopen(file_name, "w");
    
    int iter;
    unsigned char hand;
    int element = 0;
    
    for (iter = 0; iter < iters; iter++){
        for (hand = 0; hand < HANDS_OFFSUITED + HANDS_SUITED; hand++){
            fprintf(f_sb_dynamics, "%.4f", dynamics_sb[element]);
            fprintf(f_bb_dynamics, "%.4f", dynamics_bb[element]);
            element++;
            
            if (hand < HANDS_OFFSUITED + HANDS_SUITED - 1){
                fprintf(f_sb_dynamics, ",");
                fprintf(f_bb_dynamics, ",");
            }
        }
        fprintf(f_sb_dynamics, "\n");
        fprintf(f_bb_dynamics, "\n");
    }

    fclose(f_sb_dynamics);
    fclose(f_bb_dynamics);
}

