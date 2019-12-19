# Particle-Simulator

This is a program which simulates an n-body particle system using equations of motion using C++. It predicts the motion of a group of particles interacting with each other through gravitational forces.

Given the initial parameters of each particle (such as initial speed, position ) the program can predict the position of all the particle after any number of time steps.

The following variables can be redefined to change the simulation charecteristics
1) N : This defines the number of particles in the system
2) ITERATIONS : This defines the total number of iterations in which the positions of the objects will be calculated
3) TIME_STEP_LENGTH : This defines the total length of each time step

# Testing

Simpy compile the program using : g++ nbody3d.cpp -o nbody3d
And run it using : ./nbody3d

Note : The initialization for positions can also be changed to suit one's requirements
