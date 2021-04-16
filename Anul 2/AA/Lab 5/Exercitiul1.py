import numpy as np

def main():
    A = float(input("xA = ")), float(input("yA = "))
    B = float(input("xB = ")), float(input("yB = "))
    C = float(input("xC = ")), float(input("yC = "))

    matrix = np.array([[A[0], A[1], 1], 
                       [B[0], B[1], 1],
                       [C[0], C[1], 1]])

    det = np.linalg.det(matrix)

    if det < 0:
        print("Viraj la dreapta")
    elif det > 0:
        print("Viraj la stanga")
    else:
        print("Puncte coliniare")

if (__name__ == "__main__"):
    main()