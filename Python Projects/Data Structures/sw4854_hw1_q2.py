def shift(lst, k, direction="left"):
    """Shifts numbers N circularly with step k."""
    if direction == "left":
        counter = 0
        while counter < k:
            shift_element = lst.pop(0)
            lst.append(shift_element)
            counter += 1
    elif direction == "right":
        counter = 0
        k = len(lst) - k
        while counter < k:
            shift_element = lst.pop(0)
            lst.append(shift_element)
            counter += 1

    return lst

# lst = [1, 2, 3, 4, 5, 6]
# k = 2
# print(shift(lst, k, direction="right"))
