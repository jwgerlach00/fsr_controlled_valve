import pandas as pd
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from sklearn.preprocessing import PolynomialFeatures
import numpy as np
from sklearn.metrics import r2_score


# Variables
r_unknown = 2e3
r_others = 10e3
v_in_wheat = 3.3
v_in_amp = 5
gain = 2
voltage_trials = 3

# Import calibation data
calibration_df = pd.read_excel('resistance_calibration_values.xlsx')
grams = calibration_df.pop('grams').to_list()
volts = calibration_df.to_numpy().flatten()

# Make the dimensions and order of grams match volts
grams = voltage_trials*grams
grams.sort()

# Polynomial fits
fits = [np.polyfit(volts, grams, deg) for deg in [1, 2, 3, 4]]

# Plot calibration data
plt.scatter(volts, grams, label='measured data')

# Plot fits
coeffs = []
x = np.linspace(min(volts), max(volts), 1000)
for i, fit in enumerate(fits):
    plt.plot(x, np.polyval(fit, x), label='order {0} fit'.format(i + 1))
    coeffs.append(r2_score(grams, np.polyval(fit, volts)))
print(coeffs)
    
plt.legend()
plt.show()

