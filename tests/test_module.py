import subprocess

print("beginning test module...")

# run this file to execute the tests
# eg. python3 test_module.py

# compile the code


# run the serial program for various inputs
# input_filenames = ["1_sample_input.txt"]
input_filenames = ["1_sample_input.txt", "2_sample_input.txt", "3_sample_input.txt", "4_sample_input.txt"]

### run serial here
# for input_filename in input_filenames:
#     subprocess.call(["./serial", input_filename, "1"])

# run the parallel program for various inputs
for input_filename in input_filenames:
    subprocess.call(["./parallel_FW", input_filename, "2"])
    sleep(5)


print("finished running test module...")
