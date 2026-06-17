def find_peak(arr):
    left = 0
    right = len(arr) - 1
    
    while left < right:
        mid = (left + right) // 2
        
        # если средний элемент меньше правого соседа значит пик справа
        if arr[mid] < arr[mid + 1]:
            left = mid + 1
        else:
            # иначе пик слева 
            right = mid
    
    return arr[left]

n = int(input())
arr = list(map(int, input().split()))


print(find_peak(arr))