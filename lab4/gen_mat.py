import numpy as np
from random import random

n = int(random() * 20 + 5)
for tol in range(10):
    g = np.random.rand(n, n)
    coeffs = list(range(n))
    np.random.shuffle(coeffs)
    sep = 10 ** (-tol)
    init_eig = n * sep
    mat = np.diagflat([init_eig + k * sep for k in coeffs])
    mat = g @ mat @ np.linalg.inv(g)

    with open(f"./gen_files/gen_mat_{n}_{sep}.txt", 'w', encoding='utf8') as f:
        for row in mat:
            f.write(f"{' '.join(map(str, row))}\n")
        f.write(f'\n\n{init_eig}\n\n')
