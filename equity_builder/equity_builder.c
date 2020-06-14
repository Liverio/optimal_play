// ----------------------------------------------------
// Project     : Texas Hold'em hand evaluator
// Module Name : equity_builder.c
// Author      : Javier Olivito (JO)
// ----------------------------------------------------
// Revisions:
// Date        Version     Author      Description
// 2020/06/14      1.0         JO      Initial release 
// ----------------------------------------------------

#include <time.h>
#include "./equity/equity.h"

void main(){
    // Init random seed
    srand(time(NULL));
    allin_equity_builder();
}
