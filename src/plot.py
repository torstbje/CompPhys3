from plotting import set_paras, make_dir
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import os




file_dir = 'plots'
n_parts = 2

make_dir(file_dir)

def plt_zvt():
	# plot z vs t
	filenames = ['textfiles/rk4_int_0.txt']

	for filename in filenames:
		data = pd.read_csv(filename, header=None)
		plt.plot(data[0], data[3], label=filename[14:-6])

	set_paras('time($\mu s$)','z position($\mu m$)','z position vs time $dt=0.01\mu s$','z_dt=0_01', file_dir, has_label=True)


plt_zvt()


def plt_z_phase():
	# plot z vs v_z
	for part_id in range(n_parts):
		int_data = pd.read_csv('textfiles/rk4_int_' + str(part_id) + '.txt', header=None)
		plt.plot(int_data[3],int_data[6],label='Particle '+str(part_id + 1))

	set_paras('position($\mu m$)','velocity($m/s$)','Phase space trajectory in z-direction with interactions','z_phase_int', file_dir, has_label=True)

	for part_id in range(n_parts):
		non_data = pd.read_csv('textfiles/rk4_non_' + str(part_id) + '.txt', header=None)
		plt.plot(non_data[3],non_data[6],label='Particle '+str(part_id + 1))

	set_paras('position($\mu m$)','velocity($m/s$)','Phase space trajectory in z-direction without interactions','z_phase_non', file_dir, has_label=True)


plt_z_phase()


def plt_x_phase():
	# plot x vs v_x
	for part_id in range(n_parts):
		int_data = pd.read_csv('textfiles/rk4_int_' + str(part_id) + '.txt', header=None)
		plt.plot(int_data[1],int_data[4],label='Particle '+str(part_id + 1))

	set_paras('position($\mu m$)','velocity($m/s$)','Phase space trajectory in x-direction with interactions','x_phase_int', file_dir, has_label=True)

	for part_id in range(n_parts):
		non_data = pd.read_csv('textfiles/rk4_non_' + str(part_id) + '.txt', header=None)
		plt.plot(non_data[1],non_data[4],label='Particle '+str(part_id + 1))

	set_paras('position($\mu m$)','velocity($m/s$)','Phase space trajectory in x-direction without interactions','x_phase_non', file_dir, has_label=True)


plt_x_phase()

def plt_xy():

	for part_id in range(n_parts):
		int_data = pd.read_csv('textfiles/rk4_int_' + str(part_id) + '.txt', header=None)
		plt.plot(int_data[1],int_data[2],label='Particle '+str(part_id + 1))

	set_paras('x($\mu m$)','y($\mu m$)','Trajectory in x-y plane with interactions', 'x-y_int', file_dir, has_label=True)
	plt.axis('equal')

	for part_id in range(n_parts):
		non_data = pd.read_csv('textfiles/rk4_non_' + str(part_id) + '.txt', header=None)
		plt.plot(non_data[1],non_data[2],label='Particle '+str(part_id + 1))

	set_paras('x($\mu m$)','y($\mu m$)','Trajectory in x-y plane without interactions', 'x-y_non', file_dir, has_label=True)
	plt.axis('equal')



plt_xy()



def plt_xyz():
	ax = plt.figure().add_subplot(projection='3d')
	for part_id in range(n_parts):
		data = pd.read_csv('textfiles/rk4_int_' + str(part_id) + '.txt', header=None)
		ax.plot(data[1], data[2], data[3], label='Particle '+str(part_id + 1))

	full_path = os.path.join(file_dir, "xyz_int")
	plt.title('Trajectory in 3D plane with interactions')
	ax.set_xlabel('x')
	ax.set_ylabel('y')
	ax.set_zlabel('z')
	plt.legend()
	plt.savefig(full_path)
	plt.close()


	ax = plt.figure().add_subplot(projection='3d')
	for part_id in range(n_parts):
		data = pd.read_csv('textfiles/rk4_non_' + str(part_id) + '.txt', header=None)
		ax.plot(data[1], data[2], data[3], label='Particle '+str(part_id + 1))

	full_path = os.path.join(file_dir, "xyz_non")
	plt.title('Trajectory in 3D plane without interactions')
	ax.set_xlabel('x')
	ax.set_ylabel('y')
	ax.set_zlabel('z')
	plt.legend()
	plt.savefig(full_path)
	plt.close()


plt_xyz()
