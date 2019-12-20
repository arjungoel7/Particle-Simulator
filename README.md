# Particle-Simulator

This is a program which simulates an n-body particle system using equations of motion using C++. It predicts the motion of a group of particles interacting with each other through gravitational forces.

![N Body Sytem ](https://ars.els-cdn.com/content/image/1-s2.0-S2211379718333771-gr1.jpg)

Given the initial parameters of each particle (such as initial speed, position ) the program can predict the position of all the particles after any number of time steps.

The following variables can be redefined to change the simulation charecteristics
1) N : This defines the number of particles in the system
2) ITERATIONS : This defines the total number of iterations in which the positions of the objects will be calculated
3) TIME_STEP_LENGTH : This defines the total length of each time step

### Testing

1) Compile using : g++ nbody3d.cpp -o nbody3d
2) Run using : ./nbody3d

Note : The initialization for positions can also be changed to suit one's requirements

## CUDA Implementation

The program nbody3dCUDA is an optimized implementation of the above program using CUDA. This optimization performs the updates on the parameters of the particles using threads which run in parallel. CUDA tends to fare better than the non-CUDA program when the number of particles is large. It can be run on a gpu with CUDA installed.

Note : Both the implementations give the execution time as an output which can be used to compare their efficiencies.

### Testing CUDA implementation

1) Compile using : nvcc nbody3dCUDA.cu -o nbody3dCUDA
2) Run using : ./nbody3dCUDA
