// ----------------------------------------------------
// Project     : Heads-up push/fold solver
// Module Name : equity.c
// Author      : Javier Olivito (JO)
// ----------------------------------------------------
// Revisions:
// Date        Version     Author      Description
// 2020/06/14      1.0         JO      Initial release 
// ----------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "equity.h"

void load_allin_equity(float* allin_equity){
    unsigned char i, j;
    FILE* f_allin_equity;

    if ((f_allin_equity = fopen("../equity_builder/allin_equity.csv", "r")) == NULL){
        printf("Error opening precomputed allin equity\n");
        exit(0);
    }

    for (i = 0; i < HANDS_OFFSUITED + HANDS_SUITED; i++){
        for (j = 0; j < HANDS_OFFSUITED + HANDS_SUITED; j++){
            fscanf(f_allin_equity, "%f,", &(allin_equity[i * (HANDS_OFFSUITED + HANDS_SUITED) + j]));
        }
    }
    fclose(f_allin_equity);
}


