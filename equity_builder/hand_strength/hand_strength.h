// ----------------------------------------------------
// Project     : Texas Hold'em hand evaluator
// Module Name : hand_strength.h
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

// -------------------
// -- Hand encoding --
// -------------------
// (Bit) 51 ... 39 | 38 ... 26 | 25 ... 13 | 12 ...  0
//       Ac ... 2c | Ad ... 2d | Ah ... 2h | As ... 2s

// ----------------
// -- Hand value --
// ----------------
// (Bit) 63:48 |  47:32 |  31:16 |   15:0
//        hand | rank_2 | rank_1 | rank_0

void hand_strength(u64 cards, u64* hand_value);
