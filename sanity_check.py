#!/bin/python3 

import subprocess
import test_generator
import os
import filecmp

print("parallel times: ")
for _ in range(10):
    rv = subprocess.run(["./parallel_FW", "tests/N_1024_input.txt", "1"], capture_output=True, text=True)
    print("rv: ", rv)


print("serial times: ")
for _ in range(10):
    rv = subprocess.run(["./serial_FW", "tests/N_1024_input.txt", "1"], capture_output=True, text=True)
    print("rv: ", rv)