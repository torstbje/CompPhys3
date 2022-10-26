from set_paras import set_paras, set_paras3D
import pandas as pd
import matplotlib.pyplot as plt
import sys


for f in (0.1,0.4,0.7):
    data = pd.read_csv("textfiles/p_frac_500_" + str(f) + ".txt", header=None)
    plt.plot(data[0],data[1], label= "f = " + str(f))

set_paras('$\omega_v$','Fraction of Particles in Trap', "p_frac_500", "p_frac_500.pdf", has_label=True)