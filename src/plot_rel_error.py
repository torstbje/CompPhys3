import numpy as np
import matplotlib.pyplot as plt
import sys

MAX_TIME = 50

q = 1
m = 1
B0 = 96.5 
v0 = 25
vod2 = 9.65 # V_0/d^2

x0 = 20
z0 = 20
w0 = q*B0/m
wz = np.sqrt(2*q*vod2/m)

if len(sys.argv) < 2:
    print("You're missing parameters!")

method = sys.argv[1]
step_sizes = ['4000','8000','16000','32000']

filename = 'textfiles/' + method + '_non_'


data = [pd.read_csv(filename + step + '_0.txt', header=None) for steps in step_sizes]

def analytical(step_size):

    
    wp = (w0+np.sqrt(w0**2-2*wz**2))/2
    wm = (w0-np.sqrt(w0**2-2*wz**2))/2
    Ap = (v0+wm*x0)/(wm-wp)
    Am = -(v0+wp*x0)/(wm-wp)


    t = np.arange(0,MAX_TIME,MAX_TIME/step_size)
    x = Ap*np.cos(-wp*t)+Am*np.cos(-wm*t)
    y = Ap*np.sin(-wp*t)+Am*np.sin(-wm*t)
    z = np.cos(wz*t)

    return x,y,z

