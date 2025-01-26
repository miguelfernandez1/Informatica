Este dataset se denomina MetroPT-3 y consiste en lecturas de presión, temperatura, corriente del motor y válvulas de admisión de aire recogidas de la unidad de producción de aire del compresor (APU) de un metro operacional. En la documentación de MetroPT-3, se expecifica que este conjunto de datos puede ser utilizado para predicción de fallos, explicación de anomalías, entre otros.

Uno de los grandes dificultades a la hora de resolver problemas de predicción de mantenimiento industriales es el gran desbalanceo de datos. Los datos operacionales normales en comparación con el número de eventos donde hay fallos son muy distantes siendo este último la clase minoritaria.

Existen 1516948 instancias en el dataset con 15 características donde los datos son tabulares, multivariados y estructurado en series temporales. Los datos están sin etiquetado, sin embargo en la documentación de MetroPT-3 se especifican 4 fallos.

Se recomienda emplear el primer mes para training y el resto para test, indicando que lo ideal sería aplicar un algoritmos de incremental training.

No obstante, debido a que en esta asignatura no se ha impartido incremental training ni series temporales y debido a nuestro desconocimiento sobre este tipo de entrenamiento y enfoques de machine learning, no se emplearán para el desarrollo de esta práctica.

Inicialmente se emplea el dataset con el timestamp como índice para poder introducir los fallos reportados por el experto y para mantener la secuencialidad de los ciclos de trabajo a la hora de preprocesar los datos.

Nuestro objetivo será realizar un modelo predictivo que indique si el metro se encuentra en estado de fallo o avería prescindiendo de la variable temporal.

Información de las 15 características; (1-7) sensores análogos y (8-15) sensores digitales:

TP2 (bar) – presión del compresor
TP3 (bar) – presión generada en el panel neumático
H1 (bar) – presión generada debido a la caída de presión cuando se produce la descarga del filtro separador ciclónico
DV pressure (bar) – caída de presión generada cuando las torres descargan los secadores de aire; cero indica que el compresor opera con carga
Reservoirs (bar) – presión en dirección aguas abajo de los depósitos, debería ser cercano a la presión del panel neumático (TP3)
Motor Current (A) – corriente de una de las fases del motor trifásico; presenta valores cercanos a 0A - cuando se apaga, 4A - cuando el motor trabaja descargado, 7A - cuando trabaja bajo carga, y 9A - cuando entra en funcionamiento
Oil Temperature (ºC) – temperatura del aceite en el compresor
COMP - señal eléctrica de la válvula de entrada del aire en el compresor; se activa cuando no hay entrada de aire, indicando que el compresor está apagado o en un estado descargado
DV electric – señal eléctrica que controla la válvula de salida del compresor; se activa cuando el compresor funciona bajo carga, y es inactiva cuando el compresor o bien está apagado o funciona en estado de descarga.
TOWERS – señal eléctrica que especifica que torre está en funcionamiento. Existen dos torres; cuando el valor es 0 la torre responsable del secado del aire ésta activa; cuando el valor es 1 indica que la torre responsable del drenaje de la húmedad está activa.
MPG – señal eléctrica responsable de arrancar el compresor bajo carga activando la válvula de admisión cuando la presión en la APU desciende debajo de 8.2bar; activa el sensor COMP que asume el mismo comportamiento que MPG
LPS – señal eléctrica que detecta y se activa cuando la presión desciende por debajo de 7 bares.
Pressure Switch - señal eléctrica que detecta la descarga en las torres de secado al aires
Oil Level – señal eléctrica que detecta el nivel de aceite en el compresor; se activa cuando el aceite está por debajo de los valores esperados
Caudal Impulse – señal eléctrica que cuenta los impulsos generados por la cantidad absoluta de aire que fluye de la APU a los depósitos
Nuestra hipótesis e adquisición de conocimiento mediante un experto del tema con un ingeniero industrial sobre las variables que pueden llegar a ser más importantes son Motor current, Oil temperature y TP3.

No obstante todas las variables son importantes a la hora de resolver otro tipo de problema como puede ser predicción del tipo de mantenimiento necesario.