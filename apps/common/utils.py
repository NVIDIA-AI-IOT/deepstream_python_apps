import ctypes

def long_to_int(l):
    value = ctypes.c_int(l & 0xffffffff).value
    return value
