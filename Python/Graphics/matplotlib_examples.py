
# Import Matplotlib and allow plots to show in the Jupyter Notebook
# pip install matplotlib
# pip install pandas
# https://matplotlib.org/stable/users/installing.html
import matplotlib.pyplot as plot

# Import NumPy and Pandas
import numpy as np
import pandas as pd

# ---------------------- Histograms ----------------------------
# Roll 2 6 sided dies get the sum and plot the histogram
arr_1 = np.random.randint(1,7,5000)
arr_2 = np.random.randint(1,7,5000)
arr_3 = arr_1 + arr_2
# Bins reprsent the number of options available 2 thru 12 = 11
# Density returns the frequency of each bin
# Range gets tuple with bin range interested in
# cumulative=True use a cumulative distribution
# histtype='step' genrates a line plot
# orientation='horizontal'
# color='orange' change bar color
plot.hist(arr_3, bins=11, density=True, stacked=True)
plot.show()
plot.savefig('output')