import numpy as np

EPSILON = 0.001

def det(A, B, C):
    matrix = np.array([[A[0], A[1], 1], 
                       [B[0], B[1], 1],
                       [C[0], C[1], 1]])

    return np.linalg.det(matrix)

def main():
    n = int(input("n="))
    points = []
    for i in range(n):
        points.append((float(input("x"+str(i)+"=")), float(input("y"+str(i)+"="))))

    p = (float(input("x=")), float(input("y=")))

    for i in range(n):
        j = (i + 1) % n
        if det(p, points[i], points[j]) == 0:
            print("Punctul este pe o latura")
            exit()

    realArea = 0
    pointArea = 0
    for i in range(n):
        j = (i+1) % n
        realArea += points[i][0] * points[j][1] - points[i][1] * points[j][0]
        pointArea += det(points[i], points[j], p)

    if abs(realArea - pointArea) > EPSILON:
        print("Punctul este in afara poligonului")
        exit()

    print("Punctul este in interiorul poligonului")

if (__name__ == "__main__"):
    main()
