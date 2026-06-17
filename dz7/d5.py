def find_partitions(n):
    result = []  # список для хранения всех разбиений
    
    def backtrack(remaining, start, current):
        # remaining сколько осталось набрать
        # start минимальное число, которое можно добавить
        # current текущая комбинация чисел
    
        # если набрали нужную сумму
        if remaining == 0:
            result.append(current[:])
            return
        
        # перебираем возможные числа для добавления
        for i in range(start, remaining + 1):
            current.append(i)
            backtrack(remaining - i, i, current)
            current.pop()
    
    # поиск
    backtrack(n, 1, [])
    return result

n = int(input())

partitions = find_partitions(n)

for partition in partitions:
    print(' '.join(map(str, partition)))