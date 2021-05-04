import numpy as np
from random import random

n = int(random() * 20 + 5)
for tol in range(10):
    orth, _ = np.linalg.qr(np.random.rand(n, n))
    coeffs = list(range(1, n + 1))
    np.random.shuffle(coeffs)
    sep = 10**(-tol)

    mat = np.diagflat([n + k * sep for k in coeffs])
    mat = np.transpose(orth) @ mat @ orth

    eigs = dict(zip(*np.linalg.eig(mat)))
    eig = min(eigs)
    eigvec = eigs[eig]
    with open(f"./gen_files/gen_mat_{n}_{sep}.txt", 'w', encoding='utf8') as f:
        for row in mat:
            f.write(f"{' '.join(map(str, row))}\n")
        f.write(f'\n\n{eig}\n\n')
        f.write(f'{" ".join(map(str, eigvec))}')
