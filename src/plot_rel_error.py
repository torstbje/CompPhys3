import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import sys
from analytical import analytical
from set_paras import set_paras

if len(sys.argv) < 2:
    print("You're missing parameters!")

method = sys.argv[1]
step_sizes = [4000,8000,16000,32000]

filename = 'textfiles/' + method + '_non_'
max_diff = []

for steps in step_sizes:
    r_sim = pd.read_csv(filename + str(steps) + '_0.txt',usecols = [1,2,3], header=None)
    t, r_ana = analytical(steps)

    diff = np.mean(abs(r_sim - r_ana), axis = 1)
    err = diff/np.mean(abs(r_ana),axis = 1)
    plt.plot(t,err, label = 'Steps = ' + str(steps))
    max_diff.append(max(diff))

error_converge = sum([np.log(max_diff[i+1]/max_diff[i])/np.log(step_sizes[i+1]/step_sizes[i]) for i in range(3)])/3
set_paras('t($\mu s$)','Error','Relative error in position. Error convergence: %.4f' % (error_converge), 'rel_error_' + method + '_', has_label = True)
