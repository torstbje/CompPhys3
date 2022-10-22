from plotting import *
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

filenames = ['z_euler.txt', 'z_rk4.txt']

for filename in filenames:
	datas = pd.read_csv(filename, header=None)
	plt.plot(datas[0], datas[1], label=filename[2:-4])

plt.title('z position vs time $dt=0.01\mu s$')
plt.xlabel('time($\mu s$)')
plt.ylabel('z position($\mu m$)')
plt.legend()
plt.savefig('dt=0.01.pdf')
plt.show()