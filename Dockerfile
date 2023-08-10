# Use a base image with a C++ compiler and standard library.
FROM ubuntu:latest

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

# Run the program.
ENTRYPOINT ["./build/bin/tacit_ronin"]
CMD []