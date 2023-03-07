from ArrayStack import *
from ArrayQueue import *
from LinkedBinaryTree import *
from DoublyLinkedList import *

class LinkedStack:
    def __init__(self):
        self.data = DoublyLinkedList()

    def __len__(self):
        return len(self.data)

    def is_empty(self):
        return len(self) == 0

    def push(self, s):
        self.data.add_last(e)

    def pop(self):
        if self.is_empty():
            raise Exception("Stack is Empty")
        return self.data.delete_last()

    def top(self):
        if self.is_empty():
            raise Exception("Stack is Empty")

        return self.data.trailer.prev.data



