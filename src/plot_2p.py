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


if len(sys.argv) < 4:
    raise Exception ("You're missing parameters!")
    

# Sets values from commandline arguments
method = sys.argv[1]
interaction = sys.argv[2]
n = sys.argv[3]

# For using in titles and filenames
if interaction == 'int':
    info = 'with interactions ('
else:
    info = 'without interactions ('

info += method + ': n = ' + n + ' iterations)  '
file_desc = method + '_' + interaction + '_' + n
output_name = file_desc + '.pdf'


filename = 'textfiles/' + file_desc
data_1 = pd.read_csv(filename + '_0.txt', header=None)
data_2 = pd.read_csv(filename + '_1.txt', header=None)

p1 = []
p2 = []
for index in [1,2,3,4,6]:
    p1.append(data_1[index])
    p2.append(data_2[index])

area = 5**2

# plot x-y plane

plt.plot(p1[0],p1[1],label='Particle 1',lw=1)
plt.plot(p2[0],p2[1],label='Particle 2',lw=1)
plt.scatter([p1[0][0],p2[0][0]], [p1[1][0],p2[1][0]],s=area,c=['#1f77b4','#ff7f0e'],marker='o', alpha=0.75)
plt.scatter([p1[0][len(p1[0])-1],p2[0][len(p2[0])-1]], [p1[1][len(p1[1])-1],p2[1][len(p2[1])-1]],s=area,c=['#1f77b4','#ff7f0e'],marker='^', alpha=0.75)
plt.axis('equal')
set_paras('x($\mu m$)','y($\mu m$)','Trajectory in x-y plane ' + info, 'xy_' + output_name, has_label=True)


# plot phase space in x direction
plt.plot(p1[0],p1[3],label='Particle 1',lw=1)
plt.plot(p2[0],p2[3],label='Particle 2',lw=1)
plt.scatter([p1[0][0],p2[0][0]], [p1[3][0],p2[3][0]],s=area,c=['#1f77b4','#ff7f0e'],marker='o', alpha=0.75)
plt.scatter([p1[0][len(p1[0])-1],p2[0][len(p2[0])-1]], [p1[3][len(p1[3])-1],p2[3][len(p2[3])-1]],s=area,c=['#1f77b4','#ff7f0e'],marker='^', alpha=0.75)
set_paras('position($\mu m$)','velocity($m/s$)','Phase space trajectory in x-direction ' + info,'x_phase_' + output_name, has_label=True)


# plot phase space in z direction
plt.plot(p1[2],p1[4],label='Particle 1',lw=1)
plt.plot(p2[2],p2[4],label='Particle 2',lw=1)
plt.scatter([p1[2][0],p2[2][0]], [p1[4][0],p2[4][0]],s=area,c=['#1f77b4','#ff7f0e'],marker='o', alpha=0.75)
plt.scatter([p1[2][len(p1[2])-1],p2[2][len(p2[2])-1]], [p1[4][len(p1[4])-1],p2[4][len(p2[4])-1]],s=area,c=['#1f77b4','#ff7f0e'],marker='^', alpha=0.75)
set_paras('position($\mu m$)','velocity($m/s$)','Phase space trajectory in z-direction ' + info,'z_phase_' + output_name, has_label=True)


# plot x-y-z space
ax = plt.figure().add_subplot(projection='3d')
ax.plot(p1[0], p1[1], p1[2], label='Particle 1',lw=1)
ax.plot(p2[0], p2[1], p2[2], label='Particle 2',lw=1)
set_paras3D(ax,'x($\mu m$)','y($m/s$)','z($m/s$)','Trajectory in 3D space ' + info, 'xyz_' + output_name, has_label=True)
