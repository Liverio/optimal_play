// ----------------------------------------------------
// Project     : Texas Hold'em hand evaluator
// Module Name : two_pair.h
// Author      : Javier Olivito (JO)
// ----------------------------------------------------
// Revisions:
// Date        Version     Author      Description
// 2020/06/14      1.0         JO      Initial release 
// ----------------------------------------------------

#include <stdint.h>
#include <inttypes.h>
typedef uint64_t u64;

char two_pair(u64 cards, u64* hand_value);
