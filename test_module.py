import subprocess

print("beginning test module...")

# compile the code
subprocess.call(
    [
        "gcc",
        "-Wall",
        "-Werror",
        "-O3",
        "parallel_hw1.c",
        "-o",
        "customer_software_serial",
    ]
)

# run the serial program for various inputs
input_filenames = ["sample_input.txt"]

for input_filename in input_filenames:
    subprocess.call(["./customer_software_serial", input_filename, "128"])


# run the parallel program for various inputs


print("finished running test module...")
