# from DoublyLinkedList import *
# from LinkedBinaryTree import *

class CompactString:

    class Node:
        def __init__(self, data=None, next=None, prev=None):
            self.data = data
            self.next = next
            self.prev = prev

    def __init__(self, orig_str):
        """ Initializes a CompactString object representing the string given in orig_str"""
        self.header = self.Node("Header")
        self.trailer = self.Node("Trailer")
        self.header.next = self.trailer
        self.trailer.back = self.header
        self.number_of_nodes = 0
        self.output_list = []
        if len(orig_str)!= 0:
            var = [orig_str[0], 1]
            for i in range(1,len(orig_str)):
                if var[0] == orig_str[i]:
                    var[1] += 1
                else:
                    self.output_list.append(var)
                    var = [orig_str[i],1]

            if len(self.output_list) == 0 or var[0] != self.output_list[-1][0]:
                self.output_list.append(var)

            for i in self.output_list:
                self.enter(tuple(i))

    def enter(self, string_number):
        node = self.Node(string_number)
        node.back = self.trailer.back
        node.next = self.trailer
        self.trailer.back.next = node
        self.trailer.back = node

    def __add__(self, other):
        ''' Creates and returns a CompactString object that represent the concatenation of self and other,
        also of type CompactString'''
        output_comp_string = CompactString("")
        pointer_1 = self.header.next
        while pointer_1 != self.trailer.prev:
            output_comp_string.enter((pointer_1.data[0], pointer_1.data[1]))
            pointer_1 = pointer_1.next

        pointer_2 = other.header.next

        if self.trailer.prev.data[0] == pointer_2.data[0]:
            mid_sum = self.trailer.prev.data[1] + pointer_2.data[1]
            output_comp_string.enter((pointer_2.data[0], mid_sum))

        pointer_2 = pointer_2.next

        while pointer_2 != other.trailer:
            output_comp_string.enter((pointer_2.data[0], pointer_2.data[1]))
            pointer_2 = pointer_2.next

        return output_comp_string


def __lt__(self, other):
    ''' returns True if"f self is lexicographically less than other, also of type CompactString'''
    counter_1 = self.header.next
    counter_2 = other.header.next
    while True:
        if counter_1==self.trailer and counter_2!=other.trailer:
            return True
        elif counter_1!=self.trailer and counter_2==other.trailer:
            return False
        elif counter_1==self.trailer and counter_2==other.trailer:
            return False
        if counter_1.data[0].upper() < counter_2.data[0].upper():
            return True
        elif counter_1.data[0].upper() > counter_2.data[0].upper():
            return False
        else:
            if counter_1.data[1] < counter_2.data[1]:
                counter_1 = counter_1.next
            elif counter_1.data[1] > counter_2.data[1]:
                counter_2 = counter_2.next
            else:
                counter_1 = counter_1.next
                counter_2 = counter_2.next


def __le__(self, other):
    ''' returns True if”f self is lexicographically less than or equal to other, also of type CompactString'''
    counter_1 = self.header.next
    counter_2 = other.header.next
    while True:
        if counter_1==self.trailer and counter_2!=other.trailer:
            return True
        elif counter_1!=self.trailer and counter_2==other.trailer:
            return False
        elif counter_1==self.trailer and counter_2==other.trailer:
            return True
        if counter_1.data[0].upper() < counter_2.data[0].upper():
            return True
        elif counter_1.data[0].upper() > counter_2.data[0].upper():
            return False
        else:
            if counter_1.data[1] < counter_2.data[1]:
                counter_1 = counter_1.next
            elif counter_1.data[1] > counter_2.data[1]:
                counter_2 = counter_2.next
            else:
                counter_1 = counter_1.next
                counter_2 = counter_2.next


def __gt__(self, other):
    ''' returns True if”f self is lexicographically greater than other, also of type CompactString'''
    counter_1 = self.header.next
    counter_2 = other.header.next
    while True:
        if counter_1 == self.trailer and counter_2 != other.trailer:
            return False
        elif counter_1 != self.trailer and counter_2 == other.trailer:
            return True
        elif counter_1 == self.trailer and counter_2 == other.trailer:
            return False
        if counter_1.data[0].upper() < counter_2.data[0].upper():
            return False
        elif counter_1.data[0].upper() > counter_2.data[0].upper():
            return True
        else:
            if counter_1.data[1] < counter_2.data[1]:
                counter_1 = counter_1.next
            elif counter_1.data[1] > counter_2.data[1]:
                counter_2 = counter_2.next
            else:
                counter_1 = counter_1.next
                counter_2 = counter_2.next

def __ge__(self, other):
    ''' returns True if”f self is lexicographically greater than or equal to other, also of type CompactString'''
    counter_1 = self.header.next
    counter_2 = other.header.next
    while True:
        if counter_1==self.trailer and counter_2!=other.trailer:
            return False
        elif counter_1!=self.trailer and counter_2==other.trailer:
            return True
        elif counter_1==self.trailer and counter_2==other.trailer:
            return True
        if counter_1.data[0].upper() < counter_2.data[0].upper():
            return False
        elif counter_1.data[0].upper() > counter_2.data[0].upper():
            return True
        else:
            if counter_1.data[1] < counter_2.data[1]:
                counter_1 = counter_1.next
            elif counter_1.data[1] > counter_2.data[1]:
                counter_2 = counter_2.next
            else:
                counter_1 = counter_1.next
                counter_2 = counter_2.next

def __repr__(self):
    ''' Creates and returns the string representation (of type str) of self'''

    output_string = ""
    pointer = self.header.next
    if pointer is None:
        return
    while pointer != self.trailer:
        if pointer != None:
            output_string += str(pointer.data)
            pointer = pointer.next
    print(output_string)
    return output_string

# #
#
# s1 = CompactString("aaabbbbcccd")
# s2 = CompactString("bbaaaawww")
# __repr__(s1)
# __repr__(s2)


