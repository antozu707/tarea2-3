import random
import string

def cadena_random(n):
    return ''.join(random.choices(string.ascii_lowercase, k=n))

def generar_cadena():
    datasets = [
        ("", ""),
        ("nothing", ""),
        ("", "something"),
        ("sea", "flea"),  
        ("form", "from"),
        (cadena_random(10), cadena_random(13)) 
    ]
    
    with open('strings.txt', 'w') as f:
        for (s1, s2) in datasets:
            f.write(f"{s1}\n{s2}\n\n")

generar_cadena()
