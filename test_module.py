import subprocess

print("beginning test module...")

# run this file to execute the tests
# eg. python3 test_module.py

# compile the code
subprocess.call(
    [
        "gcc", 
        -Wall,
        -Werror,
        -O3 parallel_FW.c,
        input_module.c,
        output_module.c,
        fw_parallel_module.c,
        stopwatch.c,
        -pthread,
        -o ,
        parallel_FW
    ]
)

# run the serial program for various inputs
input_filenames = ["1_sample_input.txt"]

### run serial here


# run the parallel program for various inputs
for input_filename in input_filenames:
    subprocess.call(["./parallel_FW", input_filename, "2"])


print("finished running test module...")
