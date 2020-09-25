# About Runaway Indicator
Repository for the Runaway Indicator Kepler actor for integration into [IMAS](https://core.ac.uk/download/pdf/207980869.pdf) and [ETS](https://wpcd-workflows.github.io/). 

# How to clone repository
The latest release of the code should be checked out using

`git clone --depth 1 --branch <tag_name> https://github.com/osrep/Runin.git`.


# How to build
This code can only be run and compiled on ITM or IMAS environments. To build simply type:

`./build.sh`

If you want to build and test type:

`./test.sh`

# High level summary of functions
Indicating the presence of runaway electrons:

1. Indicate, whether the absolute value of the electric field exceeds the critical level, thus runaway generation is possible.

2. Indicate, whether the primary runaway electron (RE) growth rate exceeds a preset limit. This calculation takes only the Dreicer runaway generation method in account and assumes a velocity distribution close to Maxwellian, therefore this result should be considered with caution.

# Detailed documentation
Detailed documentation can be found [here](https://github.com/osrep/Runin/tree/master/doc)

# References
To cite Runaway Indicator as a tool please use the a following paper:

 G.I. Pokol, et. al, Runaway electron modelling in the self-consistent core European Transport Simulator, ETS, Nuclear Fusion 59, 076024 (2019)
