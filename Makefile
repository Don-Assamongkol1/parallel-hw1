CFLAGS = -O3 -Wall -g -I src/include -pthread 
SRCS_SERIAL = src/input_output/* src/utils/* src/serial_main/*
SRCS_PARALLEL = src/input_output/* src/utils/* src/parallel_main/*

serial: $(SRCS_SERIAL) ./src/include
	gcc $(CFLAGS) -o serial_FW $(SRCS_SERIAL)

parallel: $(SRCS_PARALLEL) ./src/include 
	gcc $(CFLAGS) -o parallel_FW $(SRCS_PARALLEL)

clean:
	rm serial_FW parallel_FW