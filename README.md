# NTuple

A program that sorts the Geant4 NTuple output into histograms, matrices, etc. This program accepts a settings file that includes thresholds, resolutions, etc, for each detection system. This program was written by Vinzenz Bildstein, and later modified and edited by Evan Rand. 

-----------------------------------------
 Installation
-----------------------------------------
The NTuple code requires the CommandLineInterface library (https://github.com/GRIFFINCollaboration/CommandLineInterface.git), please clone and compile this library first.
The Makefile assumes that the code of the CommandLineInterface library is in ~/CommandLineInterface, if this is not the case, edit the Makefile to point COMM_DIR to the directory where the code is.
The Makefile also assumes that you have a ~/lib directory where the shared-object libraries from the CommandLineInterface are installed. Again, if this is not the case, modify the Makefile so that LIB_DIR points to where these shared-object libraries are.
Once the Makefile has been adjusted, the code can be compiled with a simple make.
