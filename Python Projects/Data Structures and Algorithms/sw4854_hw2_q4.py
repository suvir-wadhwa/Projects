def split_parity(lst):
    if len(lst) <= 1:
        return lst

    start_val = 0
    end_val = len(lst) - 1

    while start_val < end_val:
        if (lst[end_val] % 2 == 0):
            end_val -= 1
        if (lst[start_val] % 2 == 1):
            start_val += 1

        if (lst[start_val] % 2 == 0) and (lst[end_val] % 2 == 1):
            placement = lst[start_val]
            lst[start_val] = lst[end_val]
            lst[end_val] = placement
            start_val += 1
            end_val -= 1

    return lst


# print(split_parity([1,2,3,4,7, 9, 6, 7, 7]))
