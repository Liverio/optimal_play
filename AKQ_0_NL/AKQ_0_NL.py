# -*- coding: utf-8 -*-
"""
Created on Sat Apr 21 00:29:38 2018

@author: Liverio
"""
import math
import numpy as np
from strategy import *
import matplotlib.pyplot as plt

from simulator import simulate

def main():
    # number of simulations
    SIMS_NO = 2000000
    
    # pot size is normalized
    pot_size = 1
    
    # Optimal play parameters
    P1_call_freq  = (1 - P2_bet_size) / (1 + P2_bet_size);
    P2_bet_size = math.sqrt(2) - 1
    P2_bluff_freq = P2_bet_size / (P2_bet_size + 1); 
    
    print('Optimal values:')
    print('\tP1 call frequency  = ', round(100 * P1_call_freq, 1), '%\n')
    print('\tP2 bluff frequency = ', round(100 * P2_bluff_freq, 1), '%')
    print('\tP2 bet size (pots) = ', round(100 * P2_bet_size, 1), '%')
    
    # --------------------------------------
    # -- Explore different P2's bet sizes --
    # --------------------------------------
    bet_sizes = np.linspace(0, 1, 51)
    
    P2_to_P1_EV = []
    P1_call_freqs = []
    P2_bluff_freqs = []
    
    # legends for plotting
    labels = ['P1 call frequency',
              'P2 bluff frequency']
    
    for i, P2_bet_size in enumerate(bet_sizes):
        
        P2_bluff_freq = P2_bet_size / (P2_bet_size + 1); 
        P1_call_freq  = (1 - P2_bet_size) / (1 + P2_bet_size);
        
        P2_bluff_freqs.append(100 * P2_bluff_freq)
        P1_call_freqs.append(100 * P1_call_freq)
        
        EV = simulate(P1_call_freq, P2_bluff_freq, P2_bet_size, pot_size, SIMS_NO)
            
        # P2 to P1 expectation ratio
        P2_to_P1_EV.append(EV[P2] / EV[P1])
        
    # ------------------
    # -- Plot results --
    # ------------------
    fig, axis_1 = plt.subplots()
    axis_1.set_xlabel('P2 bet size')
    axis_1.set_ylabel('P2 to P1 expectation ratio', color = 'tab:red')
    axis_1.tick_params(axis='y', labelcolor='tab:red')
    axis_1.plot(bet_sizes, P2_to_P1_EV, '-', linewidth = 2.0, color = 'tab:red')
    
    
    axis_2 = axis_1.twinx()
    axis_2.set_ylabel('Frequency (%)')
    axis_2.plot(bet_sizes, P1_call_freqs, '-', linestyle='dashed', color = 'magenta')
    axis_2.plot(bet_sizes, P2_bluff_freqs, '-', linestyle='dashed', color = 'cyan')
    
    plt.legend(labels, loc = 'best')
    plt.show()

if __name__ == "__main__":
    main()
    
	
