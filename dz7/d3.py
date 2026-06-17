n = int(input())
a = list(map(int, input().split()))

s = sum(a)
if s % 2 != 0:
    print(False)
else:
    target = s // 2
    summs = {0}  # множество достижимых сумм
    for x in a:
        # добавляем новые суммы, к каждой прибавляем х
        new_sums = {sum + x for sum in summs if sum + x <= target}
        summs.update(new_sums)
    if target in summs:
        print(True)
    else:
        print(False)
