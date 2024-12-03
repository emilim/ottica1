import numpy as np
import matplotlib.pyplot as plt

p = np.array([19.9617, 24.9617, 29.9617, 39.9617, 44.9617, 49.9617, 54.9617, 59.9617, 64.9617, 69.9617, 74.9617, 79.9617, 84.9617, 89.9617, 94.9617, 99.9617, 104.962, 21.9617, 26.9617, 31.9617, 36.9617, 41.9617, 46.9617, 51.9617,])
q = np.array([7.00167, 6.50167, 6.25167, 5.95167, 5.85167, 5.85167, 5.75167, 5.70167, 5.65167, 5.55167, 5.60167, 5.55167, 5.50167, 5.55167, 5.45167, 5.50167, 5.45167, 6.75167, 6.35167, 6.15167, 6.00167, 5.85167, 5.90167, 5.70167 ])
s_q = np.sqrt(2*0.05*0.05 + 0.01*0.01/4 + 0.01*0.01/36)
f = p*q / (p+q)
f_medio = np.mean(f)
s_f = np.sqrt(np.sum((f-f_medio)**2) / (f.size * (f.size -1)))

print(p.size)
print(f_medio, " \pm ", s_f)

plt.errorbar(p, q, color='blue', alpha=0.7, yerr=s_q, ecolor='green',fmt='o', capsize=5, label="incertezze")
x=np.linspace(min(p), max(p), 100)
y = x*f_medio / (x-f_medio)
plt.plot(x, y, color="red", label=" fit iperbolico")

plt.xlabel("X=p, (cm)")
plt.ylabel("Y=q, (cm)")
plt.title("Visualizzazione grafica dei dati p, q")
plt.legend()
plt.grid(True)
plt.show()
