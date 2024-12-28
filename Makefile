CXX = g++
CXXFLAGS = -o main

SRC = main.cpp algorithms/round_robin.cpp algorithms/srt.cpp algorithms/fb1.cpp algorithms/aging.cpp algorithms/HRRN.cpp algorithms/FCFS.cpp algorithms/SPN.cpp algorithms/fb2i.cpp
TARGET = main

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(SRC) $(CXXFLAGS)

clean:
	rm -f $(TARGET)

# g++ -o main main.cpp algorithms/round_robin.cpp algorithms/srt.cpp algorithms/fb1.cpp

test: all
	bash ./run_tests.sh


