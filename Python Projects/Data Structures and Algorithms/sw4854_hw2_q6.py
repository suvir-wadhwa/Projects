def count_lowercase(s, low, high):
    if low > high:
        return 0

    if s[low] == s[low].lower():
        return 1 + count_lowercase(s, low +1 , high)
    else:
        return count_lowercase(s, low +1 , high)


def is_number_of_lowercase_even(s, low, high):
    if low > high:
        return 0
    if s[low] == s[low].lower():
        val = 1 + count_lowercase(s, low +1, high)
    else:
        val = count_lowercase(s, low +1, high)

    if (val % 2 == 0):
        return True
    else:
        return False





