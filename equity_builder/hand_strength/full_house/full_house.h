// ----------------------------------------------------
// Project     : Texas Hold'em hand evaluator
// Module Name : full_house.h
// Author      : Javier Olivito (JO)
// ----------------------------------------------------
// Revisions:
// Date        Version     Author      Description
// 2020/06/14      1.0         JO      Initial release 
// ----------------------------------------------------

#include <stdint.h>
#include <inttypes.h>
typedef uint64_t u64;

char full_house(u64 cards, u64* hand_value);
