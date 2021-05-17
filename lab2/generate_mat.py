import numpy as np
from random import random

step = 250

for i in range(1, 41):
    n = int(random() * 50 + 10)
    diag = np.diagflat(np.linspace(1, step*i, n))
    orth, _ = np.linalg.qr(np.random.rand(n, n))
    mat = orth @ diag @ np.transpose(orth)
    cond = np.linalg.cond(mat)

    b = [random() * 100 for _ in range(n)]
    s = np.linalg.solve(mat, b)

    with open(f"gen_files/gen_mat{n}_{int(cond)}.txt", 'w', encoding='utf8') as f:
        for row, b_ in zip(mat, b):
            f.write(f"{' '.join(map(str, row))} {b_}\n")
        f.write(f"{' '.join(map(str, s))}\n")
