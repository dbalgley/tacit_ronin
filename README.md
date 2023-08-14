# tacit_ronin
Elevator Sim exercise for Outside Analytics. Time taken: ~8hr

# Build from Source
In order to build the source:  
`mkdir build`  
`cd build`  
`cmake ..`  
`make`  
`./bin/tacit_ronin "2, 3, 4"` or `./bin/tacit_ronin_tests`

# Run from Docker
Docker image available at:
https://hub.docker.com/r/davisb42/tacit_ronin_dockerhub
Then run: 
`docker run tacit_ronin_container "2, 3, 4"`

In order to build and run the docker container in this repository:  
`docker build -t tacit_ronin_container .`  
`docker run tacit_ronin_container "2, 3, 4"`

# Details on the Program
The task for this program was:
> •       Provide code that simulates an elevator. You are free to use any language. Suggest C++ (and Unity if you like).  Feel free to be as creative and thorough as you like.  
> •       Upload the completed project to GitHub for discussion during interview.  
> •       Document all assumptions and any features that weren’t implemented.  
> •       The result should be an executable, or script, that can be run with the following inputs and generate the following outputs.  
>                    Inputs: [list of floors to visit] (e.g. elevator start=12 floor=2,9,1,32)  
>                    Outputs: [total travel time, floors visited in order] (e.g. 560 12,2,9,1,32)  
>                    Program Constants: Single floor travel time: 10  

There was also a directive to make it as "realistic as possible". The example given is utilizing a pathing algorithm that I implemented in `DirectElevator.cpp` but I also wanted to include an implementation of an algorithm that more closely emulated the behavior of modern elevators. After doing a little research, I found that the name for such an algorithm is (get ready for this) the *Elevator Algorithm*. (https://en.wikipedia.org/wiki/Elevator_algorithm). It is also referred to as a "SCAN Algorithm" or the "Disk Algorithm" as it dictates the motion of a HDD read arm across the sectors of a spinning Hard Drive Platter. Pretty neat. As such, this algorithm moves as far as is requested in one direction (up/down) and delivers passengers to all requested floors in that direction before reversing direction and heading back that way to achieve deliveries that way.

# Details on the Implementation
I took "realistic" to mean two things: realistic simulation of the elevator and also realistic simulation of a full-cycle software engineering product. Therefore, it was important to me that I deliver something that has a very low probability of installing/running improperly on the "Client" system. The features of the program that help with this are:
- Unit Testing, which runs when building the container and/or on push to the github repo
- Docker Image hosted on dockerhub so that it can be pulled down and doesn't require building from source
- Well commented code with clear explanations as to what is going on in the source

# Future Work
- I always believe more testing is a good thing, and there are some other unit tests I would have liked to have written, such as more edge case exploration
- I was not entirely satisfied with a third implementation of a pathing algorithm I wrote, so while the source is in and stubbed out, it is not currently runnable (nor is Direct, without changing source to keep everything simple)
- I have been working with build systems and docker with python, but haven't done so with C++ yet, so this project was an exploration into that which I found refreshing and fascinating. However, I am unsure if I am executing the build/run with "best practices" and would probably want to learn more about what is currently the industry standard.

All in all, I thank you for the opportunity and hope to hear from you soon!

-DB
