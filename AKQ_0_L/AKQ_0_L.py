# -*- coding: utf-8 -*-
"""
Created on Sat Apr 21 00:29:38 2018

@author: Liverium
"""
import math
import numpy as np
from strategy import *
import matplotlib.pyplot as plt

from simulator import simulate

def main():
    # number of simulations
    SIMS_NO = 1000000
    
    # pot size
    pot_size = 4
    
    # Optimal play parameters
    P1_call_freq  = (pot_size - 1) / (pot_size + 1);
    P2_bluff_freq = 1 / (pot_size + 1); 
    
    print('Pot = ', pot_size)
    print('Optimal values:')
    print('\tP1 call frequency  = ', round(100 * P1_call_freq, 1), '%\n')
    print('\tP2 bluff frequency = ', round(100 * P2_bluff_freq, 1), '%')
    
    
    # P1 varies his strategy 
    call_freq_values = np.linspace(0, 1, 11)
    
    # 5 unbalanced values and the optimal value for P2
    bluff_freq_values = [1.0, 0.75, 0.50, 0.25, P2_bluff_freq, 0]
    
    P2_to_P1_EV = []
    
    # legends for plotting
    labels = ['Unbalanced (P2 bluffs 1.00)',
              'Unbalanced (P2 bluffs 0.75)',
              'Unbalanced (P2 bluffs 0.50)',
              'Unbalanced (P2 bluffs 0.25)',
              '  Balanced (P2 bluffs 0.20)',
              'Unbalanced (P2 bluffs 0.00)']
    
    for i, P2_bluff_freq in enumerate(bluff_freq_values):
        P2_to_P1_EV.append([])
        
        # Try different P1's strategies
        for P1_call_freq in call_freq_values:
            EV = simulate(P1_call_freq, P2_bluff_freq, pot_size, SIMS_NO)
            
            # P2 to P1 expectation ratio
            P2_to_P1_EV[i].append(EV[P2] / EV[P1])
            
        # Plot results
        if i == len(bluff_freq_values) - 2:
            plt.plot(call_freq_values, P2_to_P1_EV[i], '--', linewidth = 2.0)
        else:
            plt.plot(call_freq_values, P2_to_P1_EV[i], '-')
    
    plt.xlabel('P1 call frequency')
    plt.ylabel('P2 to P1 expectation ratio')
    plt.axis([0, 1, 0.8, 1.7])
    plt.legend(labels)
    plt.show()

if __name__ == "__main__":
    main()
    
    
