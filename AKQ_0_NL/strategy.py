# -*- coding: utf-8 -*-
"""
Created on Sat Apr 21 20:17:05 2018

@author: Liverio
"""
import random

# ---------------
# -- Constants --
# ---------------
# Players
P1 = 0
P2 = 1

# Hands
A = 2
K = 1
Q = 0

# Actions
CHECK = 0
BET   = 1
FOLD  = 2
CALL  = 3

# Game sequence
def action(player, hand, P1_call_freq, P2_bluff_freq):
    if player == P1:
        if hand == A:
            return CALL
        
        if hand == K:
            if random.random() <= P1_call_freq:
                return CALL
                
            return FOLD
            
        # Q
        return FOLD
        
    else:
        if hand == A:
            return BET
               
        if hand == K:
            return CHECK
            
        # Q
        if random.random() <= P2_bluff_freq:
            return BET
                
        return CHECK

def outcome(player, P1_hand, P1_action, P2_hand, P2_action, pot_size, bet_size):
    if player == P1:
        if P2_action == CHECK:
            if P2_hand > P1_hand:
                return 0
                
            # x-x and X wins
            return pot_size
            
        if P2_action == BET:
            if P1_action == FOLD:
                return 0;
            
            # x-c and X losses
            if P2_hand > P1_hand:
               return -(bet_size * pot_size)
            
            # x-c and X wins
            return pot_size + bet_size * pot_size
    else:
        if P2_action == CHECK:
            if P2_hand > P1_hand:
                return pot_size
            
            # x-x and X wins
            return 0
        
        if P2_action == BET:
            if P1_action == FOLD:
                return pot_size;
            
            # b-c and X losses
            if P2_hand > P1_hand:
                return pot_size + bet_size * pot_size
            
            # b-c and X wins
            return -(bet_size * pot_size)

    