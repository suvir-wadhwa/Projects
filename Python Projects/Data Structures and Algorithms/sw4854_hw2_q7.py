def split_by_sign(lst, low, high):

    if len(lst) <= 1:
        return lst

    if low < high:
        if (lst[low] > 0) and (lst[high] < 0):
            placement = lst[low]
            lst[low] = lst[high]
            lst[high] = placement
            split_by_sign(lst, low + 1, high - 1)

        elif lst[low] > 0:
            split_by_sign(lst, low, high - 1)

        elif lst[low] < 0:
            split_by_sign(lst, low + 1, high)

    return lst



print(split_by_sign([-1, 2, 3, -5, -2, 0], 0, 5))


