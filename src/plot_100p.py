from set_paras import set_paras, set_paras3D
import pandas as pd
import matplotlib.pyplot as plt
import sys

if len(sys.argv) < 2:
    print("You're missing parameters!")

time = sys.argv[1];
description = "p_frac" + "_" + time

for f in (0.1,0.4,0.7):
    data = pd.read_csv("textfiles/" + description + "_" + str(f) + ".txt", header=None)
    plt.plot(data[0],data[1], label= "f = " + str(f))

set_paras('$\omega_v$','Fraction of Particles in Trap', description, description + ".png", has_label=True)
