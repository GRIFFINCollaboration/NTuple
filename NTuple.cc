#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"

#include "CommandLineInterface.hh"
#include "Utilities.hh"

#include "Settings.hh"
#include "Converter.hh"

int main(int argc, char** argv) {
    //parse all command line options
    CommandLineInterface interface;
    std::string settingsFileName;
    interface.Add("-sf","settings file (required)",&settingsFileName);
    std::vector<std::string> inputFileNames;
    interface.Add("-if","input file(s) (required)",&inputFileNames);
    std::string outputFileName = "Converted.root";
    interface.Add("-of","output file (default = 'Converted.root')",&outputFileName);
    int verbosityLevel = 0;
    interface.Add("-vl","verbosity level (default = 0)",&verbosityLevel);

    //-------------------- check flags and arguments --------------------
    interface.CheckFlags(argc, argv);

    bool missingFlags = false;
    if(settingsFileName.empty()) {
        std::cerr<<"Missing a settings file name!"<<std::endl;
        missingFlags = true;
    }
    if(inputFileNames.size() == 0) {
        std::cerr<<"Missing input file name(s)!"<<std::endl;
        missingFlags = true;
    }

    if(missingFlags) {
        return 1;
    }

    //read settings
    Settings settings(settingsFileName, verbosityLevel);

    //create converter and run
    Converter converter(inputFileNames, outputFileName, &settings);
    if(!converter.Run()) {
        std::cerr<<"processing ended abnormally!"<<std::endl;
        return 1;
    }

    return 0;
}
