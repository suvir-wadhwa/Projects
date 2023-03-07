def calc_squares():
    """
    Docstring would appear here...
    """
    pairs = {}

    num = input("Enter an integer (or ‘q’ to quit): ")

    while num != 'q':
        if num not in pairs:
            pairs[num] = int(num)**2

        num = input("Enter an integer (or ‘q’ to quit): ")
       
    for key in pairs.keys():
        print("{}".format(pairs[key]), end= " ")

calc_squares()
