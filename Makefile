CXX = clang++

all: divisibility prime prime-opt prime-opt2

divisibility: divisibility.cpp
	${CXX} -O3 -Wall -Wextra -std=c++0x -o $@ $<

prime: prime.cpp
	${CXX} -O3 -Wall -Wextra -o $@ $<

prime-opt: prime-opt.cpp
	${CXX} -O3 -Wall -Wextra -o $@ $<

prime-opt2: prime-opt2.cpp
	${CXX} -O3 -Wall -Wextra -o $@ $<


.PHONY: clean
clean:
	rm divisibility prime prime-opt
