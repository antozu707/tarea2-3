import matplotlib.pyplot as plt
import numpy as np

casos = ["Caso 1 (S1='', S2='')", 
         "Caso 2 (S1='nothing', S2='')", 
         "Caso 3 (S1='', S2='something')",
         "Caso 4 (S1='sea', S2='flea')",
         "Caso 5 (S1='form', S2='from')",
         "Caso 6 (S1='btceugtsay', S2='qcznywhsifnry')"]

time_fb = [0.00000098, 0.000000526, 0.00000031, 0.000012683, 0.000023866, 6.98676]
time_pd = [0.000004348, 0.000003407, 0.000000752, 0.000002096, 0.00000228, 0.000012911]

fig, ax = plt.subplots(figsize=(12, 6))
x = np.arange(len(casos))  

ax.plot(x, time_fb, label='Fuerza Bruta', marker='o', color='blue', linewidth=2)
ax.plot(x, time_pd, label='Programación Dinámica', marker='o', color='orange', linewidth=2)

ax.set_yscale("log")

ax.set_xlabel("Casos", fontsize=12)
ax.set_ylabel("Tiempo de Ejecución (segundos)", fontsize=12)
ax.set_title("Comparación de Tiempos de Ejecución", fontsize=14)
ax.set_xticks(x)
ax.set_xticklabels(casos, rotation=15, ha='right')
ax.legend(fontsize=12)

ax.grid(which="both", linestyle="--", linewidth=0.5, alpha=0.7)

plt.tight_layout()

plt.savefig("comparacion_tiempos_lineas.png", dpi=300)
print("Gráfica guardada como 'comparacion_tiempos_lineas.png'")
