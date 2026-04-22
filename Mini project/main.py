import ctypes

# load shared library
lib = ctypes.CDLL('./libcalc.so')

# define argument & return types
lib.add.argtypes = (ctypes.c_int, ctypes.c_int)
lib.add.restype = ctypes.c_int

lib.multiply.argtypes = (ctypes.c_int, ctypes.c_int)
lib.multiply.restype = ctypes.c_int

lib.subtract.argtypes=(ctypes.c_int, ctypes.c_int)
lib.subtract.restype=ctypes.c_int 

# call functions
a = 15
b = 5

print("Add     :", lib.add(a, b))
print("Multiply:", lib.multiply(a, b))
print("Subtract:", lib.subtract(a, b))