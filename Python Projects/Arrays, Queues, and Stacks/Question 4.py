
from ArrayStack import *


class Queue:

    def __init__(self):
        self.stack_1 = ArrayStack()
        self.stack_2 = ArrayStack()

    def __len__(self):
        return len(self.stack_1)

    def is_empty(self):
        return (self.stack_1.is_empty() and self.stack_2.is_empty())

    def enqueue(self, item):
        self.stack_1.push(item)

    def dequeue(self):
        if self.stack_2.is_empty():
            while not self.stack_1.is_empty():
                var = self.stack_1.pop()
                self.stack_2.push(var)

        return self.stack_2.pop()


