import numpy as np

lines = [line for line in open("gen_files/gen_mat.txt", "r", encoding='utf8')]
mat, bs = [], []
for row in lines:
    *_m, b = map(float, row.split())
    mat.append(_m)
    bs.append(b)

els = np.linspace(0.63, 0.7, 7, endpoint=False)
els = np.append(els, np.linspace(0.7, 1.5, 9))

with open("gen_files/gen_sols.txt", "w", encoding='utf8') as f:
    for e in els:
        mat[~0][~0] = e
        print(e, np.linalg.det(mat))
        f.write(f"{e} {np.linalg.det(mat)} ")
        f.write(f"{' '.join(map(str,np.linalg.solve(mat, bs)))}\n")

print(els)