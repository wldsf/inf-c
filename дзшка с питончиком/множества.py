def peresechand(setA, setB, t):
    ed = setA & setB
    rez = {x for x in ed if x > t}
    
    return rez

def input_set(name):
    print(f"Введите элементы множества {name} через пробел:")
    elements = input().split()
    result_set = set(map(int, elements))
    return result_set
    

A = input_set("A")
B = input_set("B")

t = int(input("Введите значение t: "))

result = peresechand(A, B, t)

print(f"Результат (элементы присутствующие в обоих множествах и больше {t}):")
if result:
    print(f"Пересечение = {result}")
else:
    print("Таких элементов нет")