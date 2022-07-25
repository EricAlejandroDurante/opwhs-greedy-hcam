#Graficos de comparacion

import matplotlib.pyplot as plt

fig, ax = plt.subplots()
plt.plot([3,6,9], [106,113,113],'-', color='tab:orange')

plt.xlabel('Iteraciones')
plt.ylabel('Calidad Solución [Puntaje]')
plt.show()