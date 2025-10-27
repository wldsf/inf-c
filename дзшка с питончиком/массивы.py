n = int(input("размер массива А: "))
a = []
for i in range(n):
    v = int(input())
    a.append(v)

n2 = int(input("размер массива B: "))
b = []
for i in range(n2):
    v = int(input())
    b.append(v)

t = int(input("введите число для сравнения: "))

def countbol(arr, t):
    return sum(1 for x in arr if x > t)

reza = countbol(a, t)
rezb = countbol(b, t)

if reza <= rezb:
    print(f"массив A:  {a}")
    print(f"массив B: {b}")
else:
    print(f"массив B: {b}")
    print(f"массив A:  {a}")