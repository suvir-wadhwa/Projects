class Vector:
    def __init__(self, d):
        if isinstance(d, int):
            self.coords = [0] * d
        elif isinstance(d, list):
            self.coords = d

    def __len__(self):
        return len(self.coords)

    def __getitem__(self, j):
        return self.coords[j]

    def __setitem__(self, j, val):
          self.coords[j] = val

    def __add__(self, other):
        if len(self) != len(other):
            raise ValueError("dimensions must agree")
        result = Vector(len(self))
        for j in range(len(self)):
            result[j] = self[j] + other[j]
        return result

    def __sub__(self, other):
        if len(self) != len(other):
            raise ValueError("dimensions must agree")
        result = Vector(len(self))
        for j in range(len(self)):
            result[j] = self[j] - other[j]
        return result

    def __neg__(self):
        output_coords = []
        for i in self.coords:
            output_coords.append(-i)

        return Vector(output_coords)

    def __mul__(self, other):
        """Multiply each coordinate by 3"""
        output_coords = []
        if isinstance(other, int):
            for i in self.coords:
                output_coords.append(other * i)
            return Vector(output_coords)

        elif isinstance(other, Vector):
            for i in range(len(self.coords)):
                coord_val = self.coords[i] * other.coords[i]
                output_coords.append(coord_val)

            return sum(output_coords)


    def __rmul__(self, other):
        output_coords = []
        if isinstance(other, int):
            for i in self.coords:
                output_coords.append(other * i)
            return Vector(output_coords)

        elif isinstance(other, Vector):
            for i in range(len(self.coords)):
                coord_val = self.coords[i] * other.coords[i]
                output_coords.append(coord_val)

            return sum(output_coords)


    def __eq__(self, other):
        return self.coords == other.coords

    def __ne__(self, other):
        return not (self == other)

    def __str__(self):
        return '<' + (str(self.coords)[1: -1]) + '>'

    def __repr__(self):
        return str(self)

#
# val = Vector(4)
# print(val.coords)
