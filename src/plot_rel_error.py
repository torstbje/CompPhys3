import numpy as np
import matplotlib.pyplot as plt


if len(sys.argv) < 2:
    print("You're missing parameters!")

method = sys.argv[1]
step_sizes = ['4000','8000','16000','32000']
filename = 'textfiles/' + method + '_non_'


data = [pd.read_csv(filename + step + '_0.txt', header=None) for steps in step_sizes]
