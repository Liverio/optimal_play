// ----------------------------------------------------
// Project     : Heads-up push/fold solver
// Module Name : main.c
// Author      : Javier Olivito (JO)
// ----------------------------------------------------
// Revisions:
// Date        Version     Author      Description
// 2020/06/14      1.0         JO      Initial release 
// ----------------------------------------------------

#include "./equity/equity.h"
#include "./strategy/strategy.h"
#include "./plotter/plotter.h"
#include <time.h>

void main(){
    float push_threshold[HANDS_OFFSUITED + HANDS_SUITED];
    float call_threshold[HANDS_OFFSUITED + HANDS_SUITED];
    
    // Apply fictious play to solve the game
    srand(time(NULL));
    find_nash_equilibrium(push_threshold, call_threshold);

    // Dump equilibrium in a chart-formatted csv
    chart_formatter(push_threshold, call_threshold);
}
