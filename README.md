# tacit_ronin
Elevator Sim exercise for Outside Analytics

In order to build the source:
`mkdir build`
`cd build`
`cmake ..`
`make`
`./bin/tacit_ronin "2, 3, 4"` or `./bin/tacit_ronin_tests`

Dockerhub push coming soon. In order to build and run the docker container in this repository:
`docker build -t tacit_ronin_container .`
`docker run tacit_ronin_container "2, 3, 4"`
