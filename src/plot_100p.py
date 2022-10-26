from set_paras import set_paras, set_paras3D
import pandas as pd
import matplotlib.pyplot as plt
import sys

"""
This file takes three parameters: method (eul/rk2), interaction (int/non), n (number of iterations)
It makes 4 plots. Two files describing the motion of (2) particles are needed to run this,
name of files should be: (method)_(interaction)_(n)_0.txt and (method)_(interaction)_(n)_1.txt
These files are expected to have columns: time,x,y,z,vx,vy,vz
"""

for f in (0.1,0.4,0.7):
    data = pd.read_csv("textfiles/p_frac_500_" + str(f) + ".txt", header=None)
    plt.plot(data[0],data[1], label= "f = " + str(f))

set_paras('$\omega_v$','Fraction of Particles in Trap', "p_frac_500.pdf", has_label=True)