import ctypes  # provides low-level arrays
def make_array(n):
    return (n * ctypes.py_object)()

class ArrayList:
    def __init__(self):
        self.data_arr = make_array(1)
        self.capacity = 1
        self.n = 0

    def __len__(self):
        return self.n


    def append(self, val): #amortized theta(1)
        if (self.n == self.capacity):
            self.resize(2 * self.capacity)
        self.data_arr[self.n] = val
        self.n += 1

    def resize(self, new_size):
        new_array = make_array(new_size)
        for i in range(self.n):
            new_array[i] = self.data_arr[i]
        self.data_arr = new_array
        self.capacity = new_size

    def extend(self, iter_collection):
        for elem in iter_collection:
            self.append(elem)


    def __getitem__(self, ind):
        if (not (-self.n <= ind <= self.n - 1)):
            raise IndexError('invalid index')
        if (ind < 0):
            ind = self.n + ind
        return self.data_arr[ind]

    def __setitem__(self, ind, val):
        if (not (-self.n <= ind <= self.n - 1)):
            raise IndexError('invalid index')
        if (ind < 0):
            ind = self.n + ind
        self.data_arr[ind] = val


    def pop(self, ind = -1):
        if (not (-self.n <= ind <= self.n - 1)):
            raise IndexError('invalid index')
        if (ind < 0):
            ind = self.n + ind
        elem = self.data_arr[ind]
        for i in range(ind+1, self.n):
            self.data_arr[i-1] = self.data_arr[i]
        self.data_arr[self.n - 1] = None
        self.n -= 1
        if (self.n < self.capacity // 4):
            self.resize(self.capacity // 2)
        return elem

    def insert(self, ind, value):
        if (not (-self.n <= ind <= self.n - 1)):
            raise IndexError('invalid index')
        if (ind < 0):
            ind = self.n + ind
        if (self.n == self.capacity):
            self.resize(2 * self.capacity)
        for j in range(self.n, ind, -1):
            self.data_arr[j] = self.data_arr[j - 1]
        self.data_arr[ind] = value
        self.n += 1

    def __repr__(self):
        data_as_strings = [str(self.data_arr[i]) for i in range(self.n)]
        return '[' + ', '.join(data_as_strings) + ']'

    def __add__(self, other):
        res = ArrayList()
        res.extend(self)
        res.extend(other)
        return res

    def __iadd__(self, other):
        self.extend(other)
        return self

    def __mul__(self, times):
        res = ArrayList()
        for i in range(times):
            res.extend(self)
        return res

    def __rmul__(self, times):
        return self * times



# =============================================================================
# mlst1 = ArrayList()
# for i in range(10):
#     mlst1.append(i)
# 
# for i in range(mlst1.n-1, -1,-1):
#     mlst1[i] = mlst1[i] + 10
# 
# print(mlst1)
# print(mlst1.pop())
# print(mlst1.pop())
# print(mlst1.pop(3))
# print(mlst1.pop(0))
# print(mlst1.pop(0))
# print(mlst1.pop(0))
# print(mlst1.pop(0))
# print(mlst1.pop(0))
# print(mlst1.pop(0))
# print(mlst1.pop(0))
# mlst2 = ArrayList()
# for i in range(5):
#     mlst2.append(2*i)
# 
# mlst3 = mlst1 + mlst2
# 
# mlst4 = 3 * mlst2
# 
# =============================================================================
