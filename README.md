# Genetic Algorithm for The Traveling Thief Problem

The Traveling Thief Problem (TTP) [1] is a combination of two well-known problems in
computer sciency: the Knapsack Problem (KP) and the Traveling Salesman Problem (TSP).

This project is trying to develop a Genetic Algorithm (GA) that solves instances of TTP (model 1) provided by [2].

## Dependecies

* [Gnuplot](http://www.gnuplot.info/)
* [g++-5](https://gcc.gnu.org/gcc-5/changes.html)
* [Qt Creator](https://www.qt.io/ide/) (*Only to use the .pro file*)

## Build Instructions

### Ubuntu 14.04 x64 LTS

* Install Gnuplot:

```
sudo apt-get install gnuplot
```

* Install g++-5

```
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt-get install gcc-5 g++-5
```

* Install Qt Creator

Follow https://wiki.qt.io/Install_Qt_5_on_Ubuntu.

* Compile it

To compile the MCGA, just open the .pro file with QtCreator, set to the Release mode with g++-5 added and setted to the build kit. Now just build it.

## References

1. [The travelling thief problem: The first step in the transition from theoretical problems to realistic problems](http://ieeexplore.ieee.org/xpl/login.jsp?tp=&arnumber=6557681&url=http%3A%2F%2Fieeexplore.ieee.org%2Fxpls%2Fabs_all.jsp%3Farnumber%3D6557681)

2. [A Comprehensive Benchmark Set and Heuristics for the Traveling Thief Problem](http://cs.adelaide.edu.au/~optlog/research/2014gecco-ttp.pdf)
