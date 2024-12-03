import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit


x = np.array([ 0.050096, 0.0400614, 0.033376, 0.025024, 0.0222412, 0.0200153, 0.0181945, 0.0166773, 0.0153937, 0.0142935, 0.0133402, 0.012506, 0.01177, 0.0111158, 0.0105306, 0.0100038, 0.00952729, 0.0455339, 0.0370897, 0.0312875, 0.0270551, 0.0238313, 0.021294, 0.019245])
y = np.array([ 0.142823, 0.153807, 0.159957, 0.16802, 0.170891, 0.170891, 0.173863, 0.175387, 0.176939, 0.180126, 0.178518, 0.180126, 0.18176, 0.180126, 0.18343, 0.181763, 0.18343, 0.148112, 0.157439, 0.162558, 0.16662, 0.170891, 0.169444, 0.175387])
s_x = np.array([0.000177949, 0.0001138, 7.89871e-05, 4.44018e-05, 3.50754e-05, 2.84063e-05, 2.3473e-05, 1.97215e-05, 1.68025e-05, 1.44866e-05, 1.26186e-05, 1.10898e-05, 9.82295e-06, 8.76139e-06, 7.86306e-06, 7.09612e-06, 6.43616e-06, 0.000147014, 9.75427e-05, 6.94111e-05, 5.19021e-05, 4.02701e-05, 3.21515e-05, 2.62616e-05 ])
s_y = np.array([0.00144639, 0.00167741, 0.00181425, 0.00200175, 0.00207076, 0.00207076, 0.00214339, 0.00218114, 0.00221991, 0.0023006, 0.00225971, 0.0023006, 0.00234261, 0.0023006, 0.00238577, 0.00234261, 0.00238577, 0.00155549, 0.00175757, 0.00187371, 0.00196854, 0.00207076, 0.00203582, 0.00218114])
p = np.array([19.9617, 24.9617, 29.9617, 39.9617, 44.9617, 49.9617, 54.9617, 59.9617, 64.9617, 69.9617, 74.9617, 79.9617, 84.9617, 89.9617, 94.9617, 99.9617, 104.962, 21.9617, 26.9617, 31.9617, 36.9617, 41.9617, 46.9617, 51.9617,])
q = np.array([7.00167, 6.50167, 6.25167, 5.95167, 5.85167, 5.85167, 5.75167, 5.70167, 5.65167, 5.55167, 5.60167, 5.55167, 5.50167, 5.55167, 5.45167, 5.50167, 5.45167, 6.75167, 6.35167, 6.15167, 6.00167, 5.85167, 5.90167, 5.70167 ])
scartix= np.array([ 0.0589565, 0.02129, 0.0286, 0.03333])
scartiy=np.array([0.134, 0.1717, 0.1644, 0.15697])
# Determina il range di x per la retta
x_retta = np.linspace(x.min(), x.max(), 500)
y_retta = -x_retta + 0.192991

# Crea il grafico
plt.figure(figsize=(10, 6))
plt.scatter(x, y, color= "blue", alpha=0.7)
plt.plot(x_retta, y_retta, label=f"Retta interpolante Y= -X + A_0", color='red')
plt.errorbar(x, y, color='blue', alpha=0.7, yerr=s_y, ecolor='green',fmt='o', capsize=5)
plt.errorbar(x, y, color='blue', alpha=0.7, xerr= s_x, ecolor='orange', fmt='o', capsize=5)
plt.xlabel("X=1/p, (cm)")
plt.ylabel("Y=1/q (cm)")
plt.title("Linearizzazione del problema e interpolazione")
plt.legend()
plt.grid(True)
plt.show()


def linear_model(x, A, B):
    return A + B * x

# Stima dei parametri con curve_fit
params, covariance = curve_fit(linear_model, x, y)
A, B = params  # Parametri della retta

# Calcolo delle incertezze sui parametri
errors = np.sqrt(np.diag(covariance))
A_err, B_err = errors

# Stampa dei risultati
print(f"I parametri della retta sono:")
print(f"A = {A:.2f} ± {A_err:.2f}")
print(f"B = {B:.2f} ± {B_err:.2f}")

chi_p = np.sum(((y-1.93-x)**2)/((s_y**2 + s_x**2)))
chi_p1 = np.sum(((y-1.93+0.97*x)**2)/((s_y**2 + (0.97*s_x)**2)))
F= (chi_p - chi_p1)/((chi_p1)/(24-2))

print(f"test f ={F}")