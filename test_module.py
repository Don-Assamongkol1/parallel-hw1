import subprocess
import test_generator
import os

# run using python3 test_module.py

print("generating test cases")
Ns_to_generate = [16, 32, 64, 128, 256, 512, 1024]
filenames = []
for N in Ns_to_generate:
    filename = test_generator.generate_matrix_file(N)
    filenames.append(filename)

# compile the code
os.system("make serial parallel")

# run the serial program for various inputs
print("\nrunning serial execution")
for filename in filenames:
    rv = subprocess.run(["./serial_FW", filename, "1"], capture_output=True, text=True)
    N = rv.args[1].split("_")[1]
    T = rv.args[2] # number of threads (always 1 if serial)
    time = rv.stdout.split(":")[1].strip() # time in ms 
    print(N, T, time)

# print("\nrunning parallel overhead execution T=1")
# for filename in filenames:
#     rv = subprocess.run(["./parallel_FW", filename, "1"], capture_output=True, text=True)
#     print(rv)

# print("\nrunning parallel speedup executions")
# Ts_to_test = [2, 4, 8, 16, 32, 64]
# for filename in filenames:
#     for T in Ts_to_test:
#         rv = subprocess.run(["./parallel_FW", filename, str(T)], capture_output=True, text=True)
#         print(rv)
#     print(" ")
    


# want to then process this into two graphs: 

# Graph 1: Parallel Overhead. Plot parallel with T=1 against serial. N is on x axis, time is on y axis

# Graph 2: Parallel Speedup. Plot serial graph (N vs time) and a separate curve for each parallel T=2,4,8,...