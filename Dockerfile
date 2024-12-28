FROM gcc:latest

WORKDIR /

COPY . .

RUN g++ -v -o docker main.cpp \
    algorithms/round_robin.cpp \
    algorithms/srt.cpp \
    algorithms/fb1.cpp \
    algorithms/aging.cpp \
    algorithms/HRRN.cpp \
    algorithms/FCFS.cpp \
    algorithms/SPN.cpp \
    algorithms/fb2i.cpp

CMD ["./docker"]
