from random import randint 
import os.path 

def generate_matrix_file(N):
    filename = f"tests/N_{N}_input.txt" # feed in relative path

    if os.path.isfile(filename):  # don't regenerate needlessly
        return filename 

    f = open(filename, "w")
    f.write(str(N) + "\n")

    for i in range(N):
        line_to_write = "" 
        
        for j in range(N):
            if i == j:
                line_to_write += ("0" + " ")
            else:
                line_to_write += (str(randint(1, 1000)) + " ")
        
        line_to_write += "\n"
        f.write(line_to_write)

    f.close()

    return filename