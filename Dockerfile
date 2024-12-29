FROM gcc:latest

RUN apt-get update && apt-get install -y \
    make \
    bash

WORKDIR /app

COPY . /app

RUN make
CMD ["./lab6"]
