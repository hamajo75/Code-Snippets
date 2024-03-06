#!/usr/bin/env python3
import time
import threading

def read_function(array):
    while True:
        if array:
            print("Size:" + str(len(array)))
        else:
            print("Array empty")
        time.sleep(1)

def write_function():
    array = ["elem1", "elem2"]
    x = threading.Thread(target=read_function, args=(array,))
    x.start()
    print("started thread")
    time.sleep(10)
    array.append("xyyy")
    print("appended contents array")
    time.sleep(10)
    array.clear()
    print("cleared contents array")
    time.sleep(10)
    x.join()


write_function()