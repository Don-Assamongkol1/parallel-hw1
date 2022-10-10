import subprocess
import test_generator
import os
import filecmp

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
Ns = []
serial_times = []
for filename in filenames:
    rv = subprocess.run(["./serial_FW", filename, "1"], capture_output=True, text=True)
    N = rv.args[1].split("_")[1]
    time = rv.stdout.split(":")[1].strip() # time in ms 
    
    Ns.append(N)
    serial_times.append(time)

print("N: ", Ns)
print("serial_times: ", serial_times)

Ns = [] 
parallel_overhead_times = [] 
print("\nrunning parallel overhead execution T=1")
for filename in filenames:
    rv = subprocess.run(["./parallel_FW", filename, "1"], capture_output=True, text=True)
    N = rv.args[1].split("_")[1]
    time = rv.stdout.split(":")[1].strip() # time in ms 

    Ns.append(N)
    parallel_overhead_times.append(time)
    
print("N: ", Ns)
print("parallel_overhead_times: ", parallel_overhead_times)

print("\nrunning parallel speedup executions")
Ts_to_test = [2, 4, 8, 16, 32, 64]
for filename in filenames:
    thread_times = []

    for T in Ts_to_test:
        rv = subprocess.run(["./parallel_FW", filename, str(T)], capture_output=True, text=True)
        N = rv.args[1].split("_")[1]
        time = rv.stdout.split(":")[1].strip() # time in ms 

        thread_times.append(time)

        if T == 64:
            print(f"for N={N}", thread_times)
    
print("verifying that outputs are the same...")
files_to_compare = [
    "tests/N_16_T_1_serial_output.txt",
    "tests/N_16_T_1_parallel_output.txt", 
    "tests/N_16_T_2_parallel_output.txt", 
    "tests/N_16_T_4_parallel_output.txt", 
    "tests/N_16_T_8_parallel_output.txt", 
    "tests/N_16_T_16_parallel_output.txt", 
    "tests/N_16_T_32_parallel_output.txt", 
    "tests/N_16_T_64_parallel_output.txt", 
]
for file in files_to_compare:
    if not filecmp.cmp(files_to_compare[0], file, shallow=False):
        print("Error! Did not correctly generate dist array between serial/parallel versions of our code!")

print("Done!")


# input = 
# want to then process this into two graphs: 
# Graph 1: Parallel Overhead. Plot parallel with T=1 against serial. N is on x axis, time is on y axis

# Graph 2: Parallel Speedup. Plot serial graph (N vs time) and a separate curve for each parallel T=2,4,8,...