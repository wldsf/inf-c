import matplotlib.pyplot as plt

sizes = []
normal = []
t2 = []
t4 = []
t8 = []

with open("results.txt") as f:
    next(f)
    for line in f:
        s, n, a, b, c = map(float, line.split())
        sizes.append(s)
        normal.append(n)
        t2.append(a)
        t4.append(b)
        t8.append(c)

plt.plot(sizes, normal, label="Обычный")
plt.plot(sizes, t2, label="2 потока")
plt.plot(sizes, t4, label="4 потока")
plt.plot(sizes, t8, label="8 потоков")

plt.xlabel("Размер массива")
plt.ylabel("Время (мс)")
plt.title("Quick Sort: обычный vs параллельный")
plt.legend()
plt.grid()

plt.show()