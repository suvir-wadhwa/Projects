from ArrayList import ArrayList

class ArrayStack:
    
    def __init__(self):
        self.data = ArrayList()
        #pass
        
        
    def __len__(self): # theta(1)
        return len(self.data)
        #pass
        
    
    def is_empty(self): # theta(1)
        return len(self.data) == 0
        #pass
        
    
    def push(self,item): # amortized theta(1)
        self.data.append(item)
        #pass
        
        
    
    def pop(self):# amortized theta(1)
        if (self.is_empty() == True):
            raise Exception("Stack is Empty!!!")
        return self.data.pop()
        #pass
    
    def top(self): #theta(1)
        if (self.is_empty()):
            raise Exception("Stack is Empty!!!")
        return self.data[-1]
        #pass
            
    
    
    
        

