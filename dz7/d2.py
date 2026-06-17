class Node:
    def __init__(self, value, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right

def pre_order(node, current, result):
    if not node:
        return
    
    current = current * 10 + node.value
    
    if not node.left and not node.right:
        #добавляем число пути к общей сумме
        result[0] += current
        return
    
    pre_order(node.left, current, result)
    
    pre_order(node.right, current, result)

def sum_numbers(root):
    if not root:
        return 0
    
    result = [0]
    pre_order(root, 0, result)
    return result[0]


root = Node(1)
root.left = Node(2)
root.right = Node(3)
root.left.left = Node(6)
root.right.left = Node(5)
root.right.right = Node(4)
root.right.right.left = Node(2)


result = sum_numbers(root)
print(f"Сумма чисел путей: {result}") #ответ: 281