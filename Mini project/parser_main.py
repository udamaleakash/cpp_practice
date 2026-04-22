import ctypes

# load C++ library
lib = ctypes.CDLL('./libparser.so')

# define function
lib.read_csv.argtypes = [ctypes.c_char_p]
lib.read_csv.restype = ctypes.c_char_p

# call function
filename = b"data.csv"
result = lib.read_csv(filename)

print("Parsed Data:\n")
print(result.decode())