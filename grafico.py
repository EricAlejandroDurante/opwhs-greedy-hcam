import matplotlib.pyplot as plt

def trazar_lineas(archive, colore):
    lista_inicial_x = []
    lista_inicial_y = []

    archivo = open(archive, 'r')
    for linea in archivo:
        if("---" in linea):
            break
        linea = linea.strip().split(',')
        lista_inicial_x.append(linea[0])
        lista_inicial_y.append(linea[1])
        
    lista_inicial_x = list(map(float, lista_inicial_x))
    lista_inicial_y = list(map(float, lista_inicial_y))    

    plt.plot(lista_inicial_x, lista_inicial_y,'-', color=colore)

archivo = open("64-45-1-2.ophs", 'r')
lista_x = []
lista_y = []

lista_x_fe = []
lista_y_fe = []

lista_x_h = []
lista_y_h = []

n = 0
for linea in archivo:
    if(n==0):
        linea = linea.strip().split('\t')
        h = float(linea[1])
    elif("-----" in linea):
            break
    elif(n>=4):
        linea = linea.strip().split('\t')
        if(n==4 or n==5):
            lista_x_fe.append(linea[0])
            lista_y_fe.append(linea[1])
        elif(h>0):
            lista_x_h.append(linea[0])
            lista_y_h.append(linea[1])
            h-=1
        else:
            lista_x.append(linea[0])
            lista_y.append(linea[1])
    n+=1

# Fixing random state for reproducibility
#np.random.seed(19680801)
lista_x = list(map(float, lista_x))
lista_y = list(map(float, lista_y))

lista_x_fe = list(map(float, lista_x_fe))
lista_y_fe = list(map(float, lista_y_fe))

lista_x_h = list(map(float, lista_x_h))
lista_y_h = list(map(float, lista_y_h))

fig, ax = plt.subplots()

plt.plot(lista_x_fe, lista_y_fe, 'v', color ='tab:red')
plt.plot(lista_x, lista_y, 'o', color ='tab:blue')
plt.plot(lista_x_h, lista_y_h,'^', color='tab:red')

colors = ['tab:blue',
'tab:orange',
'tab:green',
'tab:red',
'tab:purple',
'tab:brown',
'tab:pink',
'tab:gray',
'tab:olive',
'tab:cyan']

for i in range(1, 10):
    try:
        trazar_lineas(str(i) + ".txt", colors[i])
    except:
        print("file dont exits")
        break














plt.show()
