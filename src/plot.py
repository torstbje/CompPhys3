from plotting import *
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt




file_dir = 'plots'
n_parts = 2

make_dir(file_dir)

def plt_zvt():
	# plot z vs t
	filenames = ['textfiles/eul_int_pos_0.txt', 'textfiles/rk4_int_pos_0.txt']

	for filename in filenames:
		data = pd.read_csv(filename, header=None)
		plt.plot(data[0], data[3], label=filename[14:-6])


	set_paras('time($\mu s$)','z position($\mu m$)','z position vs time $dt=0.01\mu s$','z,dt=0.01.pdf', file_dir, has_label=True)


plt_zvt()

def plt_xy():

	for part_id in range(n_parts):
		int_data = pd.read_csv('textfiles/rk4_int_pos_' + str(part_id) + '.txt', header=None)
		non_data = pd.read_csv('textfiles/rk4_int_pos_' + str(part_id) + '.txt', header=None)
		plt.plot(int_data[1],int_data[2],label='int'+str(part_id))
		plt.plot(non_data[1],non_data[2],label='non'+str(part_id))

	set_paras('x($\mu m$)','y($\mu m$)','trajectory in x-y plane', 'x-y.pdf', file_dir, has_label=True)
	plt.axis('equal')



plt_xy()
