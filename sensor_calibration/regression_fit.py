import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from sklearn.metrics import r2_score, mean_squared_error


def grams_to_newtons(grams):
    """
    Converts from grams to newtons.
    """
    kg = grams / 1e3
    accel_earth = 9.81  # m/s
    return accel_earth * kg


if __name__ == '__main__':
    # Variables
    voltage_trials = 3

    # Import calibration data
    calibration_df = pd.read_excel('wheatstone_calibration_values.xlsx')
    grams = calibration_df.pop('grams').to_list()
    volts = calibration_df.to_numpy().flatten()

    # Make the dimensions and order of grams match volts
    grams = voltage_trials*grams
    grams.sort()
    
    # Convert newtons to grams
    newtons = list(map(grams_to_newtons, grams))

    # Polynomial fits
    fits = [np.polyfit(volts, newtons, deg) for deg in [1, 2, 3]]

    # Plot calibration data
    plt.scatter(volts, newtons, label='measured data')

    # Plot fits
    coor_coeffs = []
    rmses = []
    x = np.linspace(min(volts), max(volts), 1000)
    for i, fit in enumerate(fits):
        plt.plot(x, np.polyval(fit, x), label='order {0} fit'.format(i + 1))
        coor_coeffs.append(r2_score(newtons, np.polyval(fit, volts)))
        rmses.append(mean_squared_error(newtons, np.polyval(fit, volts), squared=False))
    print(coor_coeffs)
    print(rmses)
    print(fits)

    plt.xlabel('Voltage (volts)')
    plt.ylabel('Force (newtons)')
    plt.title('FSR Calibration Curve')
    plt.legend()
    plt.savefig('calibration_curve')
    plt.show()