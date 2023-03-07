from DoublyLinkedList import *

class CompactString:

    class Node:
        def __init__(self, data=None, next=None, prev=None):
            self.data = data
            self.next = next
            self.prev = prev

    def __init__(self, orig_str):
        """ Initializes a CompactString object representing the string given in orig_str"""
        self.output_list_main = DoublyLinkedList()
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
                self.output_list_main.add_last(i)

    def __add__(self, other):
        ''' Creates and returns a CompactString object that represent the concatenation of self and other,
        also of type CompactString'''
        output_comp_string = CompactString("")
        pointer_1 = self.output_list_main.header.next
        while pointer_1 != self.output_list_main.trailer.prev:
            output_comp_string.output_list_main.add_last((pointer_1.data[0], pointer_1.data[1]))
            pointer_1 = pointer_1.next

        pointer_2 = other.output_list_main.header.next

        if self.output_list_main.trailer.prev.data[0] == pointer_2.data[0]:
            mid_sum = self.output_list_main.trailer.prev.data[1] + pointer_2.data[1]
            output_comp_string.output_list_main.add_last((pointer_2.data[0], mid_sum))

        pointer_2 = pointer_2.next

        while pointer_2 != other.output_list_main.trailer:
            output_comp_string.output_list_main.add_last((pointer_2.data[0], pointer_2.data[1]))
            pointer_2 = pointer_2.next

        return output_comp_string


    def __lt__(self, other):
        ''' returns True if"f self is lexicographically less than other, also of type CompactString'''
        counter_1 = self.output_list_main.header.next
        counter_2 = other.output_list_main.header.next
        while True:
            if counter_1 == self.output_list_main.trailer and counter_2 != other.output_list_main.trailer:
                return True
            elif counter_1!=self.output_list_main.trailer and counter_2==other.output_list_main.trailer:
                return False
            elif counter_1==self.output_list_main.trailer and counter_2==other.output_list_main.trailer:
                return False
            if ord(counter_1.data[0]) < ord(counter_2.data[0]):
                return True
            elif ord(counter_1.data[0]) > ord(counter_2.data[0]):
                return False
            else:
                if (counter_1.data[1]) < (counter_2.data[1]):
                    counter_1 = counter_1.next
                elif (counter_1.data[1]) > (counter_2.data[1]):
                    counter_2 = counter_2.next
                else:
                    counter_1 = counter_1.next
                    counter_2 = counter_2.next


    def __le__(self, other):
        ''' returns True if”f self is lexicographically less than or equal to other, also of type CompactString'''
        counter_1 = self.output_list_main.header.next
        counter_2 = other.output_list_main.header.next
        while True:
            if counter_1==self.output_list_main.trailer and counter_2!=other.output_list_main.trailer:
                return True
            elif counter_1!=self.output_list_main.trailer and counter_2==other.output_list_main.trailer:
                return False
            elif counter_1==self.output_list_main.trailer and counter_2==other.output_list_main.trailer:
                return True
            if ord(counter_1.data[0]) < ord(counter_2.data[0]):
                return True
            elif ord(counter_1.data[0]) > ord(counter_2.data[0]):
                return False
            else:
                if (counter_1.data[1]) < (counter_2.data[1]):
                    counter_1 = counter_1.next
                elif (counter_1.data[1]) > (counter_2.data[1]):
                    counter_2 = counter_2.next
                else:
                    counter_1 = counter_1.next
                    counter_2 = counter_2.next


    def __gt__(self, other):
        ''' returns True if”f self is lexicographically greater than other, also of type CompactString'''
        counter_1 = self.output_list_main.header.next
        counter_2 = other.output_list_main.header.next
        while True:
            if counter_1 == self.output_list_main.trailer and counter_2 != other.output_list_main.trailer:
                return False
            elif counter_1 != self.output_list_main.trailer and counter_2 == other.output_list_main.trailer:
                return True
            elif counter_1 == self.output_list_main.trailer and counter_2 == other.output_list_main.trailer:
                return False
            if ord(counter_1.data[0]) < ord(counter_2.data[0]):
                return False
            elif ord(counter_1.data[0]) > ord(counter_2.data[0]):
                return True
            else:
                if (counter_1.data[1]) < (counter_2.data[1]):
                    counter_1 = counter_1.next
                elif (counter_1.data[1]) > (counter_2.data[1]):
                    counter_2 = counter_2.next
                else:
                    counter_1 = counter_1.next
                    counter_2 = counter_2.next

    def __ge__(self, other):
        ''' returns True if”f self is lexicographically greater than or equal to other, also of type CompactString'''
        counter_1 = self.output_list_main.header.next
        counter_2 = other.output_list_main.header.next
        while True:
            if counter_1 == self.output_list_main.trailer and counter_2!=other.output_list_main.trailer:
                return False
            elif counter_1!=self.output_list_main.trailer and counter_2==other.output_list_main.trailer:
                return True
            elif counter_1==self.output_list_main.trailer and counter_2==other.output_list_main.trailer:
                return True
            if ord(counter_1.data[0]) < ord(counter_2.data[0]):
                return False
            elif ord(counter_1.data[0]) > ord(counter_2.data[0]):
                return True
            else:
                if (counter_1.data[1]) < (counter_2.data[1]):
                    counter_1 = counter_1.next
                elif (counter_1.data[1]) > (counter_2.data[1]):
                    counter_2 = counter_2.next
                else:
                    counter_1 = counter_1.next
                    counter_2 = counter_2.next

    def __repr__(self):
        ''' Creates and returns the string representation (of type str) of self'''

        output_string = ""
        pointer = self.output_list_main.header.next
        if pointer is None:
            return
        while pointer != self.output_list_main.trailer:
            if pointer != None:
                output_string += str(pointer.data)
                pointer = pointer.next
        return output_string


# s1 = CompactString("aaabbbbcccd")
# s2 = CompactString("bbaaaawww")
# a = s1 < s2
# print(a)
# print(s1)
# __repr__(s2)
