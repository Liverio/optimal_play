// ----------------------------------------------------
// Project     : Texas Hold'em hand evaluator
// Module Name : kicker.c
// Author      : Javier Olivito (JO)
// ----------------------------------------------------
// Revisions:
// Date        Version     Author      Description
// 2020/06/14      1.0         JO      Initial release 
// ----------------------------------------------------

#include "kicker.h"

u64 kicker_value(u64 cards, char kickers_no){
    const u64 rank_mask = 0x0008004002001000;
    char i;
    u64  value = 0;
    char found = 0;

    // Suits ORed
    for (i = 0; i < 13; i++){
        if (cards & (rank_mask >> i)){
            value |= 1ULL << (12 - i);
            found++;
            if (found == kickers_no)
                return value;
        }
    }

    return value;
}
