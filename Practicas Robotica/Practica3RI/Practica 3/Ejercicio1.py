import numpy as np

# Si la matriz no es cuadrada hay que recurrir a métodos de descomposición de valores singulares
#ai vi nulos

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