#Run cell
#%%

import numpy as np
import matplotlib.pyplot as plt

#Ejercicio 7 Práctica 2
#Ejercicio 7 Práctica 2
def pci (x, y, l1, l2):
    q2 = np.arccos((x**2 + y**2 - l1**2 - l2**2) / (l1 * l2 * 2))
    q1 = np.arctan2(y,x) - np.arctan2(l2 * np.sin(q2), l1 + l2 * np.cos(q2))
    return (q1, q2)

#Definición de variables
pI = [1, 0]
pD = [1, 0.1]
pA = [1.5, 0.1]
pF = [1.5, 0]
t1 = t2 = t3 = 1
l1 = l2 = 1
t = 0.05

#Posiciones brazo robótico
q1I, q2I = pci(pI[0], pI[1], l1, l2)
q1D, q2D = pci(pD[0], pD[1], l1, l2)
q1A, q2A = pci(pA[0], pA[1], l1, l2)
q1F, q2F = pci(pF[0], pF[1], l1, l2)

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

fq1_ID, fq1_DA, fq1_AF = trayectoria434(q1I, q1D, q1A, q1F, t1, t2, t3)
fq2_ID, fq2_DA, fq2_AF = trayectoria434(q2I, q2D, q2A, q2F, t1, t2, t3)

#Cálculo de la posición
q1s = np.r_[np.polyval(fq1_ID, np.arange(0, 1, t)),
            np.polyval(fq1_DA, np.arange(0, 1, t)),
            np.polyval(fq1_AF, np.arange(-1, 0.01, t))]


q2s = np.r_[np.polyval(fq2_ID, np.arange(0, 1, t)),
            np.polyval(fq2_DA, np.arange(0, 1, t)),
            np.polyval(fq2_AF, np.arange(-1, 0.01, t))]

#Primera derivada: cálculo de la velocidad
v1_s = np.r_[np.polyval(np.polyder(fq1_ID), np.arange(0, 1, t)),
             np.polyval(np.polyder(fq1_DA), np.arange(0,1,t)),
             np.polyval(np.polyder(fq1_AF), np.arange(-1, 0.01, t))]

v2_s = np.r_[np.polyval(np.polyder(fq2_ID), np.arange(0, 1, t)),
             np.polyval(np.polyder(fq2_DA), np.arange(0,1,t)),
             np.polyval(np.polyder(fq2_AF), np.arange(-1, 0.01, t))]

#Segunda derivada: cálculo de la aceleración
a1_s = np.r_[np.polyval(np.polyder(fq1_ID, 2), np.arange(0,1,t)),
             np.polyval(np.polyder(fq1_DA,2), np.arange(0,1,t)),
             np.polyval(np.polyder(fq1_AF,2), np.arange(-1,0.01,t))]

a2_s = np.r_[np.polyval(np.polyder(fq2_ID, 2), np.arange(0,1,t)),
             np.polyval(np.polyder(fq2_DA,2), np.arange(0,1,t)),
             np.polyval(np.polyder(fq2_AF,2), np.arange(-1,0.01,t))]

T = np.arange(0, t1 + t2 + t3 + 0.01, t)
f,(ax1,ax2,ax3) = plt.subplots(3,1)

ax1.plot(T, q1s, 'b', label = 'q1') 
ax1.plot(T, q2s, 'r', label = 'q2') 
ax1.legend()
ax1.set_title("Posición")

ax2.plot(T, v1_s, 'b', label='v1')
ax2.plot(T, v2_s, 'r', label='v2')
ax2.legend()
ax2.set_title("Velocidad")

ax3.plot(T, a1_s, 'b', label='a1')
ax3.plot(T, a2_s, 'r', label='a2')
ax3.legend()
ax3.set_title("Aceleración")
# %%
