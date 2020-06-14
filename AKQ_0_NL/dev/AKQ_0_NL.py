# -*- coding: utf-8 -*-
"""
Created on Sat Apr 21 00:29:38 2018

@author: Liverio
"""
import math
from strategy import *
import matplotlib.pyplot as plt

from simulator import simulate

DEBUG = 0

def main():
    # number of simulations
    SIMS_NO = 1000000
    #SIMS_NO = 10
    
    # pot size is normalized
    pot_size = 1
    
    # Optimal play parameters
    P2_bet_size = math.sqrt(2) - 1
    P2_bluff_freq = P2_bet_size / (P2_bet_size + 1); 
    P1_call_freq  = (1 - P2_bet_size) / (1 + P2_bet_size);
    print('P1 call frequency  = ', round(100 * P1_call_freq, 1), '%\n')
    print('P2 bluff frequency = ', round(100 * P2_bluff_freq, 1), '%')
    print('P2 bet size (pots) = ', round(100 * P2_bet_size, 1), '%')
    
    call_freq_values = np.linspace(0, 1, 11)
    # 5 unbalanced values and the optimal value
    bluff_freq_values = [1.0, 0.75, 0.50, 0.25, P2_bluff_freq, 0]
    
    P2_to_P1_EV = []
#    for i in range(0, len(bluff_freq_values)):
#        P2_to_P1_EV.append([0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0])
    
#    P2_to_P1_EV = [[0 for i in range(11)] for i in range(len(bluff_freq_values))]        
    
    # legends for plotting
    labels = ['Unbalanced (P2 bluffs 1.00)', 'Unbalanced (P2 bluffs 0.75)', 'Unbalanced (P2 bluffs 0.50)', 'Unbalanced (P2 bluffs 0.25)', 'Balanced (P2 bluffs 0.20)', 'Unbalanced (P2 bluffs 0.00)']
    
    for i, P2_bluff_freq in enumerate(bluff_freq_values):
        P2_to_P1_EV.append([])
        
        for j, P1_call_freq in enumerate(call_freq_values):
            EV = simulate(P1_call_freq, P2_bluff_freq, P2_bet_size, pot_size, SIMS_NO)
            #print(P1_call_freq, '\t', EV[P1] / (float)(SIMS_NO), '\t', EV[P2] / (float)(SIMS_NO), '\t', P2_bluff_freq)
            
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
    
	
