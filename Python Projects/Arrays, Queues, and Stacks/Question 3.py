from ArrayStack import *
from ArrayDeque import *


class MidStack:
    def __init__(self):
        self.mid_Stack = ArrayStack()
        self.mid_Queue = ArrayDeque()
        self.number_of_items = len(self.mid_Stack) + len(self.mid_Queue)

    def is_empty(self):
        return self.number_of_items == 0

    def level_stack_queue(self):
        if len(self.mid_Stack) < len(self.mid_Queue):
            self.mid_Stack.push(self.mid_Queue.dequeue_first())

    def __len__(self):
        return self.number_of_items

    def push(self, e):
        self.mid_Queue.enqueue_last(e)
        self.level_stack_queue()

    def top(self):
        if self.mid_Stack.is_empty():
            raise Exception("Stack is empty!")
        else:
            return self.mid_Queue.last()

    def pop(self):
        if self.mid_Stack.is_empty():
            raise Exception("Stack is empty!")

        if len(self.mid_Queue) > 0:
            return self.mid_Queue.dequeue_last()
        else:
            return self.mid_Stack.pop()

    def mid_push(self, value):
        self.level_stack_queue()
        self.mid_Queue.enqueue_first(value)
        self.level_stack_queue()


#
# midS = MidStack()
# print(midS.push(2))
# print(midS.mid_Stack.data)
# print(midS.mid_Queue.data)
# print(len(midS.mid_Stack))
# print(len(midS.mid_Queue))
# print(midS.push(4))
# print(midS.mid_Stack.data)
# print(midS.mid_Queue.data)
# print(len(midS.mid_Stack))
# print(len(midS.mid_Queue))
# print(midS.push(6))
# print(midS.mid_Stack.data)
# print(midS.mid_Queue.data)
# print(len(midS.mid_Stack))
# print(len(midS.mid_Queue))
# print(midS.push(8))
# print(midS.push(9))
# print(midS.push(11))
#
# print(midS.mid_Stack.data)
# print(midS.mid_Queue.data)
# print(len(midS.mid_Stack))
# print(len(midS.mid_Queue))
# print(midS.mid_push(10))
#
# print(midS.pop())
# print(midS.pop())
# print(midS.pop())
# print(midS.pop())
# print(midS.pop())
# print(midS.pop())
# print(midS.pop())



