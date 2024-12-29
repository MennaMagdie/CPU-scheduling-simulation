CXX = g++
CXXFLAGS = -std=c++17

SRC = main.cpp algorithms/round_robin.cpp algorithms/srt.cpp algorithms/fb1.cpp algorithms/aging.cpp algorithms/HRRN.cpp algorithms/FCFS.cpp algorithms/SPN.cpp algorithms/fb2i.cpp
TARGET = lab6

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(SRC) $(CXXFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)

test: all
	bash ./run_tests.sh

.PHONY: all clean test