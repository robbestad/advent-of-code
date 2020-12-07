CFLAGS=-std=c++2a

SOLUTION_HEADERS=source/day_6/main.h source/day_5/main.h source/day_4/main.h source/days/7.h

all: bench run
solve: solve.cpp source/include/parser.h source/include/split.h $(SOLUTION_HEADERS)
	$(CC) solve.cpp -o solve $(CFLAGS)

benchmark: benchmark.cpp source/include/parser.h source/include/split.h source/include/binaryToDecimal.h $(SOLUTION_HEADERS)
	$(CC) benchmark.cpp -o benchmark $(CFLAGS) -isystem benchmark/include -L/Users/sven/source/google-test/benchmark/build/src -lbenchmark -lpthread

bench: benchmark
	./benchmark

run: solve
	./solve

clean:
	rm -f solve benchmark
