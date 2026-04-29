import random
import time
import matplotlib.pyplot as plt


def bubble_sort(array):
    a = array.copy()
    n = len(a)
    for i in range(n - 1):
        for j in range(n - 1):
            if a[j] > a[j + 1]:
                a[j], a[j + 1] = a[j + 1], a[j]
    return a


def merge_sort(array):
    if len(array) > 1:
        mid = len(array) // 2
        left = array[:mid]
        right = array[mid:]

        merge_sort(left)
        merge_sort(right)

        i = j = k = 0

        while i < len(left) and j < len(right):
            if left[i] < right[j]:
                array[k] = left[i]
                i += 1
            else:
                array[k] = right[j]
                j += 1
            k += 1

        while i < len(left):
            array[k] = left[i]
            i += 1
            k += 1

        while j < len(right):
            array[k] = right[j]
            j += 1
            k += 1

    return array


def quick_sort(array, start, end):
    if start < end:
        op_ind = razdel(array, start, end)
        quick_sort(array, start, op_ind - 1)
        quick_sort(array, op_ind + 1, end)


def razdel(array, start, end):
    op_ind = array[end]
    i = start - 1

    for j in range(start, end):  
        if array[j] <= op_ind:
            i += 1
            array[i], array[j] = array[j], array[i]

    array[i + 1], array[end] = array[end], array[i + 1]
    return i + 1


print("пример работы:\n")

arr = [5, 2, 9, 1, 5, 6]

print("исходный массив:", arr)
print("bubble:", bubble_sort(arr))
print("merge:", merge_sort(arr.copy()))
quick_sort(arr.copy(), 0, len(arr.copy()) - 1)
print("quick:", arr.copy())


sizes = [1000, 3000, 5000, 6000, 7000, 8000, 9000, 10000]

bubble_times = []
merge_times = []
quick_times = []

for size in sizes:
    arr = [random.randint(0, 100000) for _ in range(size)]

    # Bubble
    start = time.time()
    bubble_sort(arr)
    bubble_times.append(time.time() - start)

    # Merge
    start = time.time()
    merge_sort(arr.copy())
    merge_times.append(time.time() - start)

    # Quick
    tmp = arr.copy()
    start = time.time()
    quick_sort(tmp, 0, len(tmp) - 1)
    quick_times.append(time.time() - start)


print("\nТаблица:")
print("Размер\tBubble\tMerge\tQuick")

for i in range(len(sizes)):
    print(f"{sizes[i]}\t{bubble_times[i]:.4f}\t{merge_times[i]:.4f}\t{quick_times[i]:.4f}")



plt.plot(sizes, bubble_times, label="BubbleSort", marker='o')
plt.plot(sizes, merge_times, label="MergeSort", marker='o')
plt.plot(sizes, quick_times, label="QuickSort", marker='o')

plt.xlabel("Количество элементов в массиве")
plt.ylabel("Время выполнения алгоритма, с")

plt.title("Зависимость времени выполнения алгоритмов от размера массива")

plt.legend()
plt.grid()

plt.show()