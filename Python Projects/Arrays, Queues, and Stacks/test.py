from ArrayQueue import *


def permutation(lst):
    placeholder = [0] * len(lst)
    perm_queue = ArrayQueue()
    perm_queue.enqueue(lst)
    counter = 1
    while counter < len(lst):
        if placeholder[counter] < counter:
            if counter % 2 == 0:
                temp_var = placeholder[counter]
            else:
                temp_var = 0

            lst[temp_var], lst[counter] = lst[counter], lst[temp_var]
            perm_queue.enqueue(lst)
            placeholder[counter] += 1
            counter = 1
        else:
            placeholder[counter] = 0
            counter += 1

        while not perm_queue.is_empty():
            print(perm_queue.dequeue())




lst = [1, 2, 3]
permutation(lst)
