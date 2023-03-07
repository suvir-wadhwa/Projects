def findChange(lst01):
    start = 0
    end = len(lst01) - 1

    # We split by 2 to halve the amount of search we do
    while start <= end:
        mid_index = (end + start)//2
        mid_val = lst01[mid_index]
        if (mid_val == 1) and ((mid_index == 0) or (mid_val - 1 == 0)):
            return mid_index
        elif mid_val == 1:
            end = mid_index - 1
        elif mid_val == 0:
            start = mid_index



# print(find_change([0, 0, 1]))

