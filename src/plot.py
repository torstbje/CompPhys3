from plotting import set_paras, make_dir
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt




file_dir = 'plots'
n_parts = 2

make_dir(file_dir)

def plt_zvt():
	# plot z vs t
	filenames = ['textfiles/rk4_int_0.txt']

	for filename in filenames:
		data = pd.read_csv(filename, header=None)
		plt.plot(data[0], data[3], label=filename[14:-6])

	set_paras('time($\mu s$)','z position($\mu m$)','z position vs time $dt=0.01\mu s$','z,dt=0.01.pdf', file_dir, has_label=True)


plt_zvt()


def plt_z_phase():
	# plot z vs v_z
	filenames = ['textfiles/rk4_int_0.txt']

	for filename in filenames:
		data = pd.read_csv(filename, header=None)
		plt.plot(data[3], data[6], label=filename[14:-6])


	set_paras('z position($\mu m$)','z velocity($m/s$)','z velocity vs z position $dt=0.01\mu s$','z_phase,dt=0.01.pdf', file_dir, has_label=True)


plt_z_phase()


def plt_x_phase():
	# plot z vs v_z
	filenames = ['textfiles/rk4_int_0.txt']

	for filename in filenames:
		data = pd.read_csv(filename, header=None)
		plt.plot(data[1], data[4], label=filename[14:-6])


	set_paras('x position($\mu m$)','x velocity($m/s$)','x velocity vs x position $dt=0.01\mu s$','x_phase,dt=0.01.pdf', file_dir, has_label=True)


plt_x_phase()

def plt_xy():

	for part_id in range(n_parts):
		int_data = pd.read_csv('textfiles/rk4_int_' + str(part_id) + '.txt', header=None)
		non_data = pd.read_csv('textfiles/rk4_non_' + str(part_id) + '.txt', header=None)
		plt.plot(int_data[1],int_data[2],label='int'+str(part_id))
		plt.plot(non_data[1],non_data[2],label='non'+str(part_id))

	set_paras('x($\mu m$)','y($\mu m$)','trajectory in x-y plane', 'x-y.pdf', file_dir, has_label=True)
	plt.axis('equal')



plt_xy()
