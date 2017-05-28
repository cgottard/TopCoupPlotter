# TopCoupPlotter
***Input***
1.  A .txt file: this file contains the ntuples to run over. It is formatted as label \t path/to/the/ntuple. The first position has to be reserved to the signal sample

***Output***
1. A folder containing the all the plots requested in .pdf format.

***Description***

The class SB is essentially an histogram container for one sample. To each variable corresponds an histogram to which a string is assigned through a map. In main.cpp an SB object is define for each sample, filled and pushed in a vector.
Afterwards, the function plotSB implemented in SB.cc loops over the SB, each corresponding to a sample, and builds the stack plots.
