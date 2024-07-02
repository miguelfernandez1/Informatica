#Run cell
#%%
import numpy as np
import matplotlib.pyplot as plt

#Ejercicio 1 Prácica 2

def pcd (q1, q2, l1, l2):
    x = l1 * np.cos(q1) + l2 * np.cos(q1+q2)
    y = l2 * np.sin(q1) + l2 * np.sin(q1+q2) 
    return (x, y)

#Ejercicio 2 Práctica 2
def dibujar_pcd(q1s, q2s, l1, l2, pI, pD, pA, pF):
    n = min(len(q1s), len(q2s))
    xs = np.zeros(n)
    ys = np.zeros(n)

    for i in range(n):
        xs[i], ys[i] = pcd(q1s[i], q2s[i], l1, l2)

    x0, y0 = 0, 0
    x1, y1 = pcd(q1s[-1], 0, l1, 0)
    x2, y2 = pcd(q1s[-1], q2s[-1], l1, l2)
    x, y = [x0, x1, x2], [y0, y1, y2]

    #Dibujamos los puntos de control
    plt.plot(pI[0], pI[1], 'o')
    plt.plot(pD[0], pD[1], 'o')
    plt.plot(pA[0], pA[1], 'o')
    plt.plot(pF[0], pF[1], 'o')

    plt.plot(xs, ys, 'b')

    #Dibujamos el robot
    plt.plot(x, y, 'k')
    plt.plot(x0, y0, 'k.')
    plt.plot(x1, y1, 'k.')

#Ejercicio 5 Práctica 2
def animacion_trayectoria_pcd(q1s, q2s, l1, l2, xLim, yLim, pI, pD, pA, pF):
    n = min(len(q1s), len(q2s))
    for i in range(1, n):
        dibujar_pcd(q1s[0:i], q2s[0:i], l1, l2, pI, pD, pA, pF)
        plt.xlim(xLim[0], xLim[1])
        plt.ylim(yLim[0], yLim[1])
        plt.pause(0.005)

#Ejercicio 7 Práctica 2
def pci (x, y, l1, l2):
    q2 = np.arccos((x**2 + y**2 - l1**2 - l2**2) / (l1 * l2 * 2))
    q1 = np.arctan2(y,x) - np.arctan2(l2 * np.sin(q2), l1 + l2 * np.cos(q2))
    return (q1, q2)



def trayectoria434(qI, qD, qA, qF, t1, t2, t3):
    C = [[1, 1, 0, 0, 0, 0, 0], [3/t1, 4/t1, -1/t2, 0, 0, 0, 0,], [6/np.power(t1, 2), 12/np.power(t1, 2), 0,
    -2/np.power(t2, 2), 0, 0, 0],
    [0, 0, 1, 1, 1, 0, 0], [0, 0, 0, 0, 0, -1, 1],
    [0, 0, 1/t2, 2/t2, 3/t2, -3/t3, 4/t3],
    [0 , 0, 0, 2/np.power(t2, 2), 6/np.power(t2, 2), 6/np.power(t3, 2), -12/np.power(t3, 2)]]
    

    C = np.array(C)
    Y = np.array([qD - qI, 0, 0, qA - qD, qA - qF, 0, 0])
    X = np.inner(np.linalg.inv(C), Y)

    #Inicio Despegue: 5 coeficientes porque el polinomio es de orden 4
    fID = np.array([X[1], X[0], 0, 0, qI])

    #Despegue Arranque: 4 coeficientes el polinomio es de orden 3
    fDA = np.array([X[4], X[3], X[2], qD])

    #Arranque Fin: 5 coeficientes el polinomio es de orden 4
    fAF = ([X[6], X[5], 0, 0, qF])

    return (fID, fDA, fAF)

#Definición de variables
pI = [1, 0]
pD = [1, 0.1]
pA = [1.5, 0.1]
pF = [1.5, 0]
t1 = t2 = t3 = 1
l1 = l2 = 1
t = 0.05

#Definimos los límites de los ejes cartesianos para el gráfico
xLim = [-0.5, 2]
yLim = [-0.5, 0.5]

#Posiciones brazo robótico
q1I, q2I = pci(pI[0], pI[1], l1, l2)
q1D, q2D = pci(pD[0], pD[1], l1, l2)
q1A, q2A = pci(pA[0], pA[1], l1, l2)
q1F, q2F = pci(pF[0], pF[1], l1, l2)

fq1_ID, fq1_DA, fq1_AF = trayectoria434(q1I, q1D, q1A, q1F, t1, t2, t3)
fq2_ID, fq2_DA, fq2_AF = trayectoria434(q2I, q2D, q2A, q2F, t1, t2, t3)

q1s = np.r_[np.polyval(fq1_ID, np.arange(0, 1, t)),
            np.polyval(fq1_DA, np.arange(0, 1, t)),
            np.polyval(fq1_AF, np.arange(-1, 0.01, t))]


q2s = np.r_[np.polyval(fq2_ID, np.arange(0, 1, t)),
            np.polyval(fq2_DA, np.arange(0, 1, t)),
            np.polyval(fq2_AF, np.arange(-1, 0.01, t))]

#Animación trayectoria
animacion_trayectoria_pcd(q1s, q2s, l1, l2, xLim, yLim, pI, pD, pA, pF)
# %%
