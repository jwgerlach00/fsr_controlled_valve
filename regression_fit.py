import pandas as pd
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from sklearn.preprocessing import PolynomialFeatures
import numpy as np
from sklearn.metrics import r2_score, mean_squared_error


# Variables
voltage_trials = 3

# Import calibration data
calibration_df = pd.read_excel('wheatstone_calibration_values.xlsx')
grams = calibration_df.pop('grams').to_list()
volts = calibration_df.to_numpy().flatten()

# Make the dimensions and order of grams match volts
grams = voltage_trials*grams
grams.sort()

# Polynomial fits
fits = [np.polyfit(volts, grams, deg) for deg in [1, 2, 3]]

# Plot calibration data
plt.scatter(volts, grams, label='measured data')

# Plot fits
coor_coeffs = []
rmses = []
x = np.linspace(min(volts), max(volts), 1000)
for i, fit in enumerate(fits):
    plt.plot(x, np.polyval(fit, x), label='order {0} fit'.format(i + 1))
    coor_coeffs.append(r2_score(grams, np.polyval(fit, volts)))
    rmses.append(mean_squared_error(grams, np.polyval(fit, volts), squared=False))
print(coor_coeffs)
print(rmses)
print(fits)

plt.xlabel('Voltage (volts)')
plt.ylabel('Mass (grams)')
plt.title('FSR Calibration Curve')
plt.legend()
plt.show()