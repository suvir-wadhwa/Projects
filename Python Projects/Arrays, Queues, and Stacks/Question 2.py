from ArrayList import *
from ArrayStack import *


class MaxStack:

    def __init__(self):
        self.MStack = ArrayStack()
        self.max_element_list = []

    def is_empty(self):
        return self.MStack.is_empty()

    def __len__(self):
        return len(self.MStack)

    def push(self, e):
        self.MStack.push(e)
        if len(self.max_element_list) == 0:
            self.max_element_list.append(e)
        if e >= self.max_element_list[-1]:
            self.max_element_list.append(e)
            self.max_element = e
        else:
            self.max_element_list.append(self.max_element)

    def top(self):
        if self.MStack.is_empty():
            raise Exception("Stack is empty!")
        else:
            return self.MStack.top()

    def pop(self):
        if self.MStack.is_empty():
            raise Exception("Stack is empty!")
        else:
            self.max_element_list.pop()
            return self.MStack.pop()

    def max(self):
        if self.MStack.is_empty():
            raise Exception("Stack is empty!")
        return self.max_element_list[-1]

# maxS = MaxStack()
# maxS.push(3)
# maxS.push(1)
# maxS.push(6)
# maxS.push(4)
# print(maxS.max())
# print(maxS.pop())
# print(maxS.pop())
# print(maxS.max())

