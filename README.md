Yet another implementation of a multi layer perceptron
======================================================

This implementation is done for learning purposes. It is our first C++ project, due with a strict deadline, so please be sympathetic ;)  We implemented a standard perceptron with an arbitrary number of layers, the standard backpropagation algorithm, and RProp. It can read two CSV files, one for training, the other for test, train the network and print the differents relevant parameters at each step.

The focus for this project was to have a tested code. Most of the classes are tested by the 20 differents tests. We are pretty confident that the code works. It can run on Linux and on Windows, although the tests compile only under Linux.

A report, in French, of this project, is also included in this directory. It also contains the Doxygen documentation at the end.

We use Eigen for linear computations and Unittest++ for unit testing. They are both included in the repository.

How to use it
-------------

You need qmake and the standard building tools. Try it with

```
qmake && make && ./tests/test && ./neuralnetwork
```

The documentation can be generated using Doxygen.
