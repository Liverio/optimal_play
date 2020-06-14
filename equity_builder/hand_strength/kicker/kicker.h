// ----------------------------------------------------
// Project     : Texas Hold'em hand evaluator
// Module Name : kicker.h
// Author      : Javier Olivito (JO)
// ----------------------------------------------------
// Revisions:
// Date        Version     Author      Description
// 2020/06/14      1.0         JO      Initial release 
// ----------------------------------------------------

#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
typedef uint64_t u64;

u64 kicker_value(u64 cards, char kickers_no);
