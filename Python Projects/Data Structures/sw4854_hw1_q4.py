def fibs(n):
    """Creates a generator that yields the fibonacci sequence"""
    counter = 1
    while counter < 3:
        yield 1
        counter += 1


    i = 0
    value = 1
    prev_value = 1
    while i < n-2:
        output = value + prev_value
        prev_value = value
        value = output
        i += 1

        yield output


# for curr in fibs(8):
#     print(curr)


