"""List comprehension"""

# List comprehension that produces the list [1, 10, 100, 1000, 10000, 100000]

list_1 = [10**i for i in range(6)]

# print(list_1)

# List comprehension that produces the list [0, 2, 6, 12, 20, 30, 42, 56, 72, 90]

list_2 = [i+(i ** 2) for i in range(10)]

# print(list_2)
