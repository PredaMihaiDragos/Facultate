import numpy as np
from itertools import chain

def det(A, B, C):
    matrix = np.array([[A[0], A[1], 1], 
                       [B[0], B[1], 1],
                       [C[0], C[1], 1]])

    return np.linalg.det(matrix)

def CH(points):
    n = len(points)

    start = points.index(min(points))
    ans = []

    for i in chain(range(start, n), range(0, start)):
        while len(ans) >= 2 and det(ans[-2], ans[-1], points[i]) >= 0:
            ans.pop()
        ans.append(points[i])

    while len(ans) >= 3 and det(ans[-2], ans[-1], ans[0]) >= 0:
        ans.pop()

    return ans


def main():
    n = int(input("n="))
    points = []
    for i in range(n):
        points.append((float(input("x"+str(i)+"=")), float(input("y"+str(i)+"="))))

    ans = []

    while len(points) > 0:
        ch = CH(points)
        for p in ch:
            points.remove(p)
        ans.extend(ch)

    print(ans)


if (__name__ == "__main__"):
    main()
