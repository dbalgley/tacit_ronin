# Use a base image with a C++ compiler and standard library.
FROM ubuntu:latest AS builder

# Install necessary packages.
RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    make \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory inside the container.
WORKDIR /usr/src/app

# Copy the local source files into the container.
COPY . .

# Build the project.
RUN mkdir build && cd build && cmake .. && make

FROM builder AS tester
RUN ./build/bin/tacit_ronin_test > test_results.txt
RUN cat test_results.txt

#FROM ubuntu:latest
#COPY --from=builder /usr/src/app/build/bin/tacit_ronin /usr/local/bin/tacit_ronin

# Run the program.
ENTRYPOINT ["./build/bin/tacit_ronin"]
#ENTRYPOINT ["/bin/bash"]
CMD []