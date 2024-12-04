import random

def generar_fila(filename):
    with open(filename, 'w') as f:
        costs = [random.randint(1, 9) for _ in range(26)] 
        f.write(' '.join(map(str, costs)) + '\n')


def generar_matriz(filename):
    with open(filename, 'w') as f:
        matrix = [[0] * 26 for _ in range(26)] 
        for i in range(26):
            for j in range(i + 1, 26): 
                cost = random.randint(1, 9)  
                matrix[i][j] = cost
                matrix[j][i] = cost
        for row in matrix:
            f.write(' '.join(map(str, row)) + '\n')


generar_fila('cost_insert.txt') 
generar_fila('cost_delete.txt')  
generar_matriz('cost_replace.txt')  
generar_matriz('cost_transpose.txt')  
