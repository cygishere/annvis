# Annvis - ANN VISualizer

**WORK IN PROGRESS**

A visualizer for ANNs, lets you visualize the impact of weights change on the output of a simple ANN.

In order to visualize ANN in a 2D plane, the input layer and output layer are constrained to contain only a single neuron respectively.

## Dependencies
- [raylib](https://www.raylib.com/)

## Roadmap
- ANN part
    - [x] Structure
    - [x] Utilities for inspection
    - [x] ANN forwarding
    - [ ] ANN backprop (partial)
      - [ ] equation 1
      - [ ] equation 2
- Graphics part
    - [x] Graph sampling
    - [x] Graph rendering
    - [ ] User interface
    
## Current Problems
- How to deal with overflow & underflow?

## Build

``` sh
git clone https://github.com/cygishere/annvis.git
cd annvis/bin
make
```

