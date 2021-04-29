import numpy as np
from random import random

for i in range(20):
    n = int(random() * 50 + 10)
    m = [[random() * 100 for _ in range(n)] for _ in range(n)]
    b = [random() * 100 for _ in range(n)]
    s = np.linalg.solve(m, b)
    assert len(s) == len(m)
    with open(f"gen_files/gen_mat{n}_{i}.txt", 'w', encoding='utf8') as f:
        for row, b_ in zip(m, b):
            f.write(f"{' '.join(map(str, row))} {b_}\n")
        f.write(f"{' '.join(map(str, s))}\n")
