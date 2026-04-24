
CC = g++
CFLAGS = -O3 -std=c++17

code: solution.cpp
	$(CC) $(CFLAGS) solution.cpp -o code

clean:
	rm -f code
