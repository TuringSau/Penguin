a = 10
b = 20

def addition(a,b):
	return a+b

def multiplication(a,b):
    return a*b
    
def division(a,b):
    return a/b

def substraction(a,b):
    return a-b

intvalue = input("Enter the value")
if intvalue == 1:
    addition(a,b)
elif intvalue == 2:
    multiplication(a,b)
elif intvalue == 3:
    division(a,b)
elif intvalue == 4:
    substraction(a,b)
