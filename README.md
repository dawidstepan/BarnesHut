# Final Project

Approved for project start by Kampl and Klemenschits.

Applied Programming with C++ 360.253

<!-- Choose a meaningful title for your project -->
# Barnes Hut gravity simulation engine

## General Description
<!-- short description 
- what is out there so far?
- how would this project fit in?
- in one paragraph with about 100 words. -->
An N-body simulation is a simulation of a dynamical system of particles, for example celestial bodies, affected by gravity. In such a system, every particle interacts with every other particle leading to an order $\mathcal{O}(N^2)$. This problem is barely tractable and in practice approximation schemes have to be used.
The Barnes-Hut algorithm [1] is one method for approximating the gravitational forces between celestial bodies, reducing the order to $\mathcal{O}(N \log N)$. It divides space into a tree data structure, in which each cell represents a region of space containing multiple celestial bodies. By recursively subdividing the tree until a desired level of accuracy is achieved, the algorithm can approximate gravitational forces between bodies more efficiently.

## Current Status
<!-- In this example project, there are no dependencies, but if you do require some, make sure you list them here! -->
There are existing implementations for 2D gravity simulations employing the Barnes-Hut algorithm, e.g. Ref. [2]. We want to provide a modern C++ implementation which stands out by more flexible user input options.

### Dependencies
* SFML
* random
* cmath

## Project Goals
<!-- General description of what the final software should be able to do, including a rough description of the available API -->
Simulate the gravitational attraction between celestial bodies, e.g. colliding galaxies, and provide a way of visualizing the output.

### Goals
<!-- Detailed bullet-point list of specific parts of the software which need to be present at the end -->
* Simulate the gravitational attraction between a set of points in 2D, preferably using the Barnes-Hut algorithm for better efficiency (but also try brute force)
* implement an integrator for Newton's equations of motions
* Visualize the results, using a graphic library, for example SFML
* parse user input to set the initial position and momentum of our bodies
* store results from simulation on the disk in order to generate animations
* develop a helper-tool to create reasonable inputs (e.g. two galaxies colliding)
* implement collision detection
* create an extensive documentation using doxygen
* optionally create a python interface using pybind11

## Team
<!-- A list of team mebers including student ID and their tasks.
NOTE: "Testing" is not a valid task: EVERY memeber should immediately write tests for the components they implemented. However, there should be one person tying all tests together and creating some end-to-end tests. -->
- Max S.: Team lead, build configuration, input-parser
- Dawid Stepanovic: Barnes-Hut and collision detection and integrator, and build configuration
- Florian B.: Barnes-Hut 
- Dominik P.: collision detection and integrator
- Florian S.: collision detection and integrator
- Jakob H.: python wrapping
- Nico U.: SFML GUI
- Nika K.: helper-tool

## References
[1] https://www.nature.com/articles/324446a0 \
[2] https://github.com/womogenes/GravitySim 
