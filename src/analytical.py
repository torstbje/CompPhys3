import numpy as np


def analytical(step_size):
    MAX_TIME = 50

    q = 1
    m = 40
    B0 = 96.5
    v0 = 25
    vod2 = 9.65 # V_0/d^2

    x0 = 20
    z0 = 20
    w0 = q*B0/m
    wz = np.sqrt(2*q*vod2/m)


    wp = (w0+np.sqrt(w0**2-2*wz**2))/2
    wm = (w0-np.sqrt(w0**2-2*wz**2))/2
    Ap = (v0+wm*x0)/(wm-wp)
    Am = -(v0+wp*x0)/(wm-wp)

    r = np.empty((step_size,3))
    t = np.arange(0,MAX_TIME,MAX_TIME/(step_size))
    r[:,0] = Ap*np.cos(-wp*t)+Am*np.cos(-wm*t)
    r[:,1] = Ap*np.sin(-wp*t)+Am*np.sin(-wm*t)
    r[:,2] = np.cos(wz*t)

    return t, r
