from ArrayStack import *

def Postfix(postfix_list):
    operators = "*/+-"
    s = ArrayStack()
    for token in postfix_list:
        if token not in operators:
            s.push(int(token))
        else:
            y = s.pop()
            x = s.pop()

            if token == "+":
                result = x + y
            elif token == "-":
                result = x - y
            elif token == "*":
                result = x * y
            else:
                result = x / y

            s.push(result)

    return s.top()


variable_dict = {}
value = input("-->")
numbers_and_operators = "1234567890+-*/"
output = 0
while value != "done()":
    value_list = value.split(" ")
    if "=" in value_list:
        for i in range(len(value_list)):
            if value_list[i] in variable_dict.keys():
                value_list[i] = str(variable_dict[value_list[i]])
        variable_name = value_list[0]
        postfix_list = value_list[2:]
        output = Postfix(postfix_list)
        variable_dict[variable_name] = str(output)
        print(variable_name)
    elif (len(value_list) == 1) and (value not in numbers_and_operators):
        print(variable_dict[value])
    else:
        result = str(Postfix(value_list))
        print(result)


    value = input("-->")




