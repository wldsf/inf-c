import time
import sys
import matplotlib.pyplot as plt


def measure_execution_time(func, *args):
    start_time = time.perf_counter()
    result = func(*args)
    end_time = time.perf_counter()

    duration_ms = (end_time - start_time) * 1000  
    return result, duration_ms


def find_in_stack(stack, value):
    temp_stack = stack.copy()  

    while temp_stack:
        if temp_stack[-1] == value:
            return True
        temp_stack.pop()

    return False

def calculate_memory(stack):
    total_size = sys.getsizeof(stack)
    for item in stack:
        total_size += sys.getsizeof(item)
    return total_size

sizes = [
    10, 100, 1000, 10000, 100000,
    200000, 400000, 600000, 800000, 1000000
]

times_ms = []
memory_kb = []


for n in sizes:
    stack = []

    for i in range(n):
        stack.append(i)

    target = -1  # худший случай

    result, time_ms = measure_execution_time(find_in_stack, stack, target)

    memory_bytes = calculate_memory(stack)
    memory_in_kb = memory_bytes / 1024

    times_ms.append(time_ms)
    memory_kb.append(memory_in_kb)


plt.figure()
plt.plot(sizes, times_ms, marker="o")
plt.xlabel("Размер стека (n)")
plt.ylabel("Время (мс)")
plt.title("Зависимость времени поиска от размера стека")
plt.grid(True)
plt.show()


plt.figure()
plt.plot(sizes, memory_kb, marker="o")
plt.xlabel("Размер стека (n)")
plt.ylabel("Память (КБ)")
plt.title("Зависимость памяти от размера стека")
plt.grid(True)
plt.show()