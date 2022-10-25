from set_paras import set_paras
import pandas as pd
import matplotlib.pyplot as plt
import sys


method = sys.argv[1]
filename = 'textfiles/' + method + '_non_0.txt'

data = pd.read_csv(filename, header=None)
n = str(len(data))
plt.plot(data[0], data[3])
set_paras('t($\mu s$)','z($\mu m$)','z-position vs time (' + n + ' iterations)','z_' + method + '_' + n)
