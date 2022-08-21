#Graficos de comparacion

import matplotlib.pyplot as plt

lista1 = []
lista2 = []

archivo = open("graficoacomparar.txt", 'r')
for linea in archivo:
    linea = linea.strip().split('&')
    lista1.append(linea[0])
    lista2.append(float(linea[2]))



fig, ax = plt.subplots()
plt.plot(lista1, lista2,'-', color='tab:orange')

plt.xlabel('Instancias [U]')
plt.ylabel('Tiempo de ejecución [seg]')
plt.show()