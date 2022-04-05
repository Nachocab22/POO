EXES = test-P1-auto test-P1-consola
CXX = g++
CXXFLAGS = -g -Wall -std=c++11 -pedantic
CPPFLAGS = -DP1 -I../Test-auto -I.
VPATH = ../Tests-auto:.

CLASSES = cadena.o fecha.o
.PHONY: all clean

all: $(EXES)

test-P1-auto: test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o $(CLASSES)
	$(CXX) $(CXXFLAGS) $^ -o $@

test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o: \
	test-caso0-fecha-auto.cpp test-caso0-cadena-auto.cpp \
	test-auto.cpp test-auto.hpp fecha.hpp cadena.hpp

test-P1-consola: test-P1-consola.o $(CLASSES)
	$(CXX) -o $@ $(LDFLAGS) $^

test-P1-consola.o: fecha.cpp fecha.hpp cadena.cpp cadena.hpp
	$(CXX) -c fecha.cpp cadena.cpp

fecha.o: fecha.hpp fecha.cpp
cadena.o: cadena.hpp cadena.cpp

clean:
	@$(RM) $(EXES) *.o