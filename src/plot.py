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
	for part_id in range(n_parts):
		int_data = pd.read_csv('textfiles/rk4_int_' + str(part_id) + '.txt', header=None)
		plt.plot(int_data[3],int_data[6],label='Particle '+str(part_id))

	set_paras('z position($\mu m$)','z velocity($m/s$)','z velocity vs z position with interactions','z_phase_int', file_dir, has_label=True)

	for part_id in range(n_parts):
		int_data = pd.read_csv('textfiles/rk4_non_' + str(part_id) + '.txt', header=None)
		plt.plot(int_data[3],int_data[6],label='Particle '+str(part_id))

	set_paras('z position($\mu m$)','z velocity($m/s$)','z velocity vs z position without interactions','z_phase_non', file_dir, has_label=True)


plt_z_phase()


def plt_x_phase():
	# plot x vs v_x
	for part_id in range(n_parts):
		int_data = pd.read_csv('textfiles/rk4_int_' + str(part_id) + '.txt', header=None)
		plt.plot(int_data[1],int_data[4],label='Particle '+str(part_id))

	set_paras('x position($\mu m$)','x velocity($m/s$)','x velocity vs x position with interactions','x_phase_int', file_dir, has_label=True)

	for part_id in range(n_parts):
		int_data = pd.read_csv('textfiles/rk4_non_' + str(part_id) + '.txt', header=None)
		plt.plot(int_data[1],int_data[4],label='Particle '+str(part_id))

	set_paras('x position($\mu m$)','x velocity($m/s$)','x velocity vs x position without interactions','x_phase_non', file_dir, has_label=True)


plt_x_phase()

def plt_xy():

	for part_id in range(n_parts):
		int_data = pd.read_csv('textfiles/rk4_int_' + str(part_id) + '.txt', header=None)
		plt.plot(int_data[1],int_data[2],label='int'+str(part_id))

	set_paras('x($\mu m$)','y($\mu m$)','trajectory in x-y plane with interactions', 'x-y_int.pdf', file_dir, has_label=True)
	plt.axis('equal')

	for part_id in range(n_parts):
		non_data = pd.read_csv('textfiles/rk4_non_' + str(part_id) + '.txt', header=None)
		plt.plot(non_data[1],non_data[2],label='non'+str(part_id))

	set_paras('x($\mu m$)','y($\mu m$)','trajectory in x-y plane without interactions', 'x-y_non.pdf', file_dir, has_label=True)
	plt.axis('equal')



plt_xy()
