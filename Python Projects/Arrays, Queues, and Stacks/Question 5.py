from ArrayStack import *
from ArrayQueue import *


def permutations(lst):
    storage_queue_1 = ArrayQueue() # for temporary variables that haven't been in permutations yet
    storage_queue_2 = ArrayQueue() # for partial collections of permutations

    if len(lst) == 1:
        return [lst]
    for i in lst:
        temp_list = [i]
        # print(temp_list)
        storage_queue_2.enqueue(temp_list)
        stack_list = []
        for j in lst:
            if j != i:
                stack_list.append(j)
        # print(stack_list)
        storage_queue_1.enqueue(stack_list)

    while not storage_queue_1.is_empty():
        queue_perm = storage_queue_2.dequeue()
        # print(queue_perm)
        stack_perm = storage_queue_1.dequeue()
        # print(stack_perm)
        for i in stack_perm:
            # print(i)
            temp_queue_list = queue_perm.copy()
            temp_queue_list.append(i)
            # print(temp_queue_list)
            storage_queue_2.enqueue(temp_queue_list)
            # print(len(storage_queue))

            stack_list_2 = []
            if len(temp_queue_list) != len(lst):
                for j in lst:
                    if j not in temp_queue_list:
                        stack_list_2.append(j)
                if storage_queue_1 != []:
                    storage_queue_1.enqueue(stack_list_2)

    output_list = []
    while len(storage_queue_2) > 0:
        output_list.append(storage_queue_2.dequeue())

    return output_list

# lst = [1, 2, 3, 4]
# print(permutations(lst))









