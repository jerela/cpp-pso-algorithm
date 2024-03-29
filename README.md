# Particle swarm optimization algorithm

- [Introduction](#introduction)
- [Getting started](#getting-started)
- [Prerequisites](#prerequisites)
- [Classes](#working-principles)
  * [ParticleSwarmOptimizer](#particleswarmoptimizer)
  * [Particle](#particle)
- [License](#license)
<!-- toc -->

## Introduction

This is a C++ implementation of the particle swarm optimization algorithm to estimate optimum parameters for various problems.
Instead of all particles being aware of each other, this algorithm uses a ring-shaped social neighbourhood. Each particle has a neighbourhood comprising one tenth of all particles. Geometrical distance doesn't matter, so particles in a neighbourhood can be (but most likely won't be) far from one another.

The particles often get stuck in local minima. To alleviate this issue, each particle has a small chance of being relocated to a random position within the search space whenever positions are updated. This chance increases with each update that the particle hasn't reduced its error.
Additionally, a slight random offset is applied to all particles each update step. This step supposed to give them a chance to "vibrate" off of local minima, but hasn't proven very effective in preliminary tests.

The algorithm itself is in two classes:
- ParticleSwarmOptimizer
- Particle

Written as a hobby project after getting inspiration from the book "Bio-inspired Artificial Intelligence: theories, methods, and technologies" by Dario Floreano and Claudio Mattiussi.

## Getting started
**main.cpp** contains a working example.

## Prerequisites

None. This package is self-contained as long as you have a working C++ compiler. It uses objects from the C++ standard library but nothing from 3rd party libraries.

## Classes

### Particle

The Particle class describes a single particle in the swarm. Its private attributes include factors that weight the importance of momentum, particle-specific lowest error position, and neighbourhood-specific lowest error position in calculating the particle's velocity; knowledge of the lowest error it has had so far and the corresponding position; and knowledge of the lowest error in its neighbourhood so far and the corresponding position.
The user shouldn't worry about the interface of this class, as the ParticleSwarmOptimizer class communicates with it and stores instances of it in a container.

### ParticleSwarmOptimizer

The ParticleSwarmOptimizer class handles communication with Particle objects and interface with the user.

It has only one public function, **optimizeParameters**, which takes all the necessary data to run the particle swarm optimization algorithm.

**void optimizeParameters**(const std::vector<std::vector<double>>& *inputs*, const std::vector<double>& *targets*, size_t *dim*, double *lowerBound = -100*, double *upperBound = 100*, unsigned int *nParticles = 200*, unsigned int *maxEpochs = 1000*, double *threshold = 1e-5*)
- *inputs*: control input data
- *targets*: observed data
- *dim*: dimension of particles in the swarm (the number of parameters to solve)
- *lowerBound*: lower boundary of the search space (default: -100)
- *upperBound*: upper boundary of the search space (default: 100)
- *nParticles*: number of particles in the swarm (default: 200)
- *maxEpochs*: number of epochs to run the algorithm (default: 1000)
- *threshold*: threshold of error required to break from the epoch loop early (default: 1e-5)


## License

```
   Copyright 2023 Jere Lavikainen

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

```