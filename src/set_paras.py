import matplotlib.pyplot as plt
from matplotlib import rcParams
import os

def set_paras(x_lab,y_lab,title=None,filename=None,file_dir='plots',has_label=False):

    '''set all the parameters in the figure and save files'''

    # Sets axis labels and title
    plt.title(title)
    plt.xlabel(x_lab)
    plt.ylabel(y_lab)
    file_handling(filename,file_dir,has_label)



def set_paras3D(ax,x_lab,y_lab,z_lab,title = None, filename=None,file_dir='plots',has_label=False):
    plt.title(title)
    ax.set_xlabel(x_lab)
    ax.set_ylabel(y_lab)
    ax.set_zlabel(z_lab)
    file_handling(filename,file_dir,has_label)


def file_handling(filename=None,file_dir='plots',has_label=False):

    ''' Save file '''

    #checks if the directory exists if not make one
    if not os.path.exists(file_dir):
        os.mkdir(file_dir)

    # Checks if label is included
    if has_label:
        plt.legend()

    # Saves or shows file
    if filename:
        full_path = os.path.join(file_dir, filename)
        rcParams.update({'figure.autolayout': True})
        plt.savefig(full_path)
        plt.close()
    else:
        plt.show()
