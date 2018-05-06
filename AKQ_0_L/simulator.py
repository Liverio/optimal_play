# -*- coding: utf-8 -*-
"""
Created on Sun Apr 22 01:03:51 2018

@author: Liverio
"""

import random
from strategy import *

SHOW_TRACE = 0

def simulate(P1_call_freq, P2_bluff_freq, pot_size, sims):
    # Cumulative EV
    EV = [0, 0]
    
    hand = [0, 0]
    
    for sims in range(0, sims):
        # ----------------
        # -- Deal hands --
        # ----------------
        hand[P1] = random.randrange(3)
                
        if hand[P1] == A:
            if random.randrange(2) == 0:
                hand[P2] = K
            else:
                hand[P2] = Q
        elif hand[P1] == K:
            if random.randrange(2) == 0:
                hand[P2] = A
            else:
                hand[P2] = Q
        else:
            if random.randrange(2) == 0:
                hand[P2] = A
            else:
                hand[P2] = K
        
        if SHOW_TRACE:
            print('P1 was dealt ', 'A' if hand[P1] == 2 else 'K' if hand[P1] == 1 else 'Q')
            print('P2 was dealt ', 'A' if hand[P2] == 2 else 'K' if hand[P2] == 1 else 'Q', '\n')
    
        
        # ----------------------
        # -- Players' actions --
        # ----------------------
        # P1 is forced to check
        action_P1 = CHECK
        if SHOW_TRACE:
            print('P1 checks, ', end='')
        
        action_P2 = action(P2, hand[P2], P1_call_freq, P2_bluff_freq)
        if SHOW_TRACE:
            print('P2', 'checks' if action_P2 == CHECK else 'bets, ', end='')
        
        if action_P2 == BET:
            action_P1 = action(P1, hand[P1], P1_call_freq, P2_bluff_freq)
        
            if SHOW_TRACE:
                print('P1', 'folds' if action_P1 == FOLD else 'calls', end='')
        
        if SHOW_TRACE:
            print('\n')
        
        # ----------------------
        # -- Players' outcome --
        # ----------------------
        outcome_P1 = outcome(P1, hand[P1], action_P1, hand[P2], action_P2, pot_size)
        outcome_P2 = outcome(P2, hand[P1], action_P1, hand[P2], action_P2, pot_size)
        EV[P1] = EV[P1] + outcome_P1
        EV[P2] = EV[P2] + outcome_P2
        
        if SHOW_TRACE:
            print(' ++ EV[P1] = ', EV[P1], '(', outcome_P1, ') ++')
            print(' ++ EV[P2] = ', EV[P2], '(', outcome_P2, ') ++\n')
    
    return EV