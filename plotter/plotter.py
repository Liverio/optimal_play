# ----------------------------------------------------
# Project     : Heads-up push/fold solver
# Module Name : plotter.py
# Author      : Javier Olivito (JO)
# ----------------------------------------------------
# Revisions:
# Date        Version     Author      Description
# 2020/06/14      1.0         JO      Initial release 
# ----------------------------------------------------

import numpy as np
import matplotlib.pyplot as plt
import heatmap

def optimal_play_chart(player):
    data = np.genfromtxt('../HU_push_fold/nash_' + player + '.csv', delimiter = ',', dtype = float)
    data = np.reshape(data, (13, 13))

    fig, ax = plt.subplots()
    title = 'Small blind optimal play' if player == 'sb' else 'Big blind optimal play'
    ax.set_title(title)
    axis_labels = ["A", "K", "Q", "J", "T", "9", "8", "7", "6", "5", "4", "3", "2"]
    im, cbar = heatmap.heatmap(data, axis_labels, axis_labels, ax = ax,
                               cmap = "YlGn", cbarlabel = "Big Blinds")
    texts = heatmap.annotate_heatmap(im, valfmt = "{x:.1f}")
    
    fig.tight_layout()
    fig.savefig('./' + player + '_range.svg')

def converge_dynamics(player):
    data = np.genfromtxt('../HU_push_fold/' + player + '_dynamics_15.0.csv', delimiter = ',', dtype = float)

    hands = []
    for i in range(169):
        hands.append([])

    for iter in range(len(data)):
        for hand in range(169):
            hands[hand].append(data[iter][hand])
    
    fig, ax = plt.subplots()
    title = 'Small blind convergence dynamics' if player == 'sb' else 'Big blind convergence dynamics'
    ax.set_title(title)
    ax.set_xlabel('Iteration')
    ylabel = 'Push ratio' if player == 'sb' else 'Call ratio'
    ax.set_ylabel(ylabel)
    for i in range(169):
        plt.plot(hands[i], linewidth = 0.5)
        
    fig.savefig('./' + player + '_15bb.svg')

def main():
    optimal_play_chart('sb')
    optimal_play_chart('bb')

    converge_dynamics('sb')
    converge_dynamics('bb')
        
if __name__ == "__main__":
    main()