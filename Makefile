CFLAGS=-std=c++2a

SOLUTION_HEADERS=source/include/parser.h source/include/utils.h

all: bench run
solve: solve.cpp source/include/parser.h source/include/split.h $(SOLUTION_HEADERS)
	$(CC) solve.cpp -o bin/solve $(CFLAGS)

benchmark: benchmark.cpp source/include/parser.h source/include/split.h source/include/binaryToDecimal.h $(SOLUTION_HEADERS)
	$(CC) benchmark.cpp -o bin/benchmark $(CFLAGS) -isystem benchmark/include -L/Users/sven/source/google-test/benchmark/build/src -lbenchmark -lpthread

bench: benchmark
	./bin/benchmark

run: solve
	./bin/solve

clean:
	rm -f solve benchmark
