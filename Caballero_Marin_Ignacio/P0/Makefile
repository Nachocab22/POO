EXES = test-P0-auto test-P0-consola
CXX = g++
CXXFLAGS = -g -Wall -std=c++11 -pedantic
CPPFLAGS = -DP0 -I../Test-auto -l
VPATH = ../Tests-auto:.

CLASSES = cadena.o fecha.o
.PHONY: all clean

all: $(EXES)

test-P0-auto: test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o $(CLASSES)
	$(CXX) $(CXXFLAGS) $^ -o $@

test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o: \
	test-caso0-fecha-auto.cpp test-caso0-cadena-auto.cpp \
	test-auto.cpp test-auto.hpp fecha.hpp cadena.hpp

test-P0-consola: test-P0-consola.o $(CLASSES)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	@$(RM) $(EXES) *.o