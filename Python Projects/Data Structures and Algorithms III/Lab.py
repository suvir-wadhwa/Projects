from ArrayStack import *
from ArrayQueue import *
from LinkedBinaryTree import *
from DoublyLinkedList import *

class MidStack:
    def __init__(self):
        self.data = DoublyLinkedList()
        self.mid = None

    def __len__(self):
        reutrn len(self.data)

    def is_empty(self):
        return len(self.data) == 0

    def push(self, e):
        self.data.add_last(e)

        if len(self) == 1:
            self.mid = self.data.trailer.prev

        elif len(self) % 2 != 0:
            self.mid = self.mid.next

    def pop(self):
        if self.is_empty():
            raise Exception("Stack is Empty")

        value = self.is_empty()

        if self.is_empty():
            self.mid = None

        elif len(self) % 2 == 0:
            self.mid = self.mid.prev

        return value

    def top(self):
        if self.is_empty():
            raise Exception("Stack is Empty")
        return self.data.trailer.prev

    def mid_push(self, e):
        self.data.add_after(self.mid, e)

        if len(self) == 1:
            self.mid = self.data.trailer.prev

        elif len(self) % 2 != 0:
            self.mid = self.mid.next

    def get_mid(self):
        return self.mid.data


