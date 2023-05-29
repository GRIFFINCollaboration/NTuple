#ifndef __SETTINGS_HH
#define __SETTINGS_HH

#include <string>
#include <map>
#include <vector>

#include "TF1.h"

class Settings {
public:
    Settings(std::string, int);
    ~Settings(){};

    std::string NtupleName() {
        return fNtupleName;
    }

    int VerbosityLevel() {
        return fVerbosityLevel;
    }
    double DaemonThresholdSettings() {
        return fDaemonThreshold;
    }
    double DaemonWidthSettings() {
        return fDaemonWidth;
    }

    int BufferSize() {
        return fBufferSize;
    }

    int SortNumberOfEvents() {
        return fSortNumberOfEvents;
    }

    bool WriteTree() {
        return fWriteTree;
    }

    bool Write2DHist() {
        return fWrite2DHist;
    }

    //bool Write3DHist() {
    //    return fWrite3DHist;
    //}

    bool WriteNDHist() {
        return fWriteNDHist;
    }
    
    bool Write2DSGGHist() {
        return fWrite2DSGGHist;
    }

    bool WriteGriffinAddbackVector() {
        return fWriteGriffinAddbackVector;
    }

    double GriffinAddbackVectorLengthmm() {
        return fGriffinAddbackVectorLengthmm;
    }

    double GriffinAddbackVectorDepthmm() {
        return fGriffinAddbackVectorDepthmm;
    }

    double GriffinAddbackVectorCrystalFaceDistancemm() {
        return fGriffinAddbackVectorCrystalFaceDistancemm;
    }
    double Resolution(int systemID, int detectorID, int crystalID, double en) {
        if(fResolution.find(systemID) != fResolution.end()) {
	//	std::cout<<"test"<<std::endl;
		if (systemID >=8000  && systemID <= 8100)
		return fResolution[systemID].at(detectorID-1).at(crystalID).Eval(en);
		if (systemID ==8710)
		return fResolution[systemID].at(detectorID).at(crystalID).Eval(en);
		if (systemID ==8720)
		return fResolution[systemID].at(detectorID-15).at(crystalID).Eval(en);
		if (systemID ==8730)
		return fResolution[systemID].at(detectorID-15-20).at(crystalID).Eval(en);
		if (systemID ==8740)
		return fResolution[systemID].at(detectorID-15-20-15).at(crystalID).Eval(en);
		if (systemID ==8750)
		return fResolution[systemID].at(detectorID-15-20-15-10).at(crystalID).Eval(en);
		if (systemID >=1010  && systemID <= 1100)
		return fResolution[systemID].at(detectorID-1).at(crystalID-1).Eval(en);
		else return fResolution[systemID].at(detectorID).at(crystalID).Eval(en);
        }
        return 0.;
    }
    double Threshold(int systemID, int detectorID, int crystalID) {
        if(fThreshold.find(systemID) != fThreshold.end()) {
		if (systemID >=8000  && systemID <= 8100)
            return fThreshold[systemID].at(detectorID-1).at(crystalID);
		if (systemID ==8710)
            return fThreshold[systemID].at(detectorID).at(crystalID);
		if (systemID ==8720)
            return fThreshold[systemID].at(detectorID-15).at(crystalID);
		if (systemID ==8730)
            return fThreshold[systemID].at(detectorID-15-20).at(crystalID);
		if (systemID ==8740)
            return fThreshold[systemID].at(detectorID-15-20-15).at(crystalID);
		if (systemID ==8750)
            return fThreshold[systemID].at(detectorID-15-20-15-10).at(crystalID);
		if (systemID >=1010  && systemID <= 1100)
            return fThreshold[systemID].at(detectorID-1).at(crystalID-1);
		else return fThreshold[systemID].at(detectorID).at(crystalID);
        }
        return 0.001;
    }
    double ThresholdWidth(int systemID, int detectorID, int crystalID) {
        if(fThresholdWidth.find(systemID) != fThresholdWidth.end()) {
		if (systemID >=8000  && systemID <= 8100)
            return fThresholdWidth[systemID].at(detectorID-1).at(crystalID);
		if (systemID == 8710)
            return fThresholdWidth[systemID].at(detectorID).at(crystalID);
		if (systemID == 8720)
            return fThresholdWidth[systemID].at(detectorID-15).at(crystalID);
		if (systemID == 8730)
            return fThresholdWidth[systemID].at(detectorID-15-20).at(crystalID);
		if (systemID == 8740)
            return fThresholdWidth[systemID].at(detectorID-15-20-15).at(crystalID);
		if (systemID == 8750)
            return fThresholdWidth[systemID].at(detectorID-15-20-15-10).at(crystalID);
		if (systemID >=1010  && systemID <= 1100)
            return fThresholdWidth[systemID].at(detectorID-1).at(crystalID-1);
		else return fThresholdWidth[systemID].at(detectorID).at(crystalID);
        }
        return 0.;
    }
    double TimeWindow(int systemID, int detectorID, int crystalID) {
        if(fTimeWindow.find(systemID) != fTimeWindow.end()) {
		if (systemID >=8000  && systemID <= 8100)
            return fTimeWindow[systemID].at(detectorID-1).at(crystalID);
		if (systemID ==8710)
            return fTimeWindow[systemID].at(detectorID).at(crystalID);
		if (systemID ==8720)
            return fTimeWindow[systemID].at(detectorID-15).at(crystalID);
		if (systemID ==8730)
            return fTimeWindow[systemID].at(detectorID-15-20).at(crystalID);
		if (systemID ==8740)
            return fTimeWindow[systemID].at(detectorID-15-20-15).at(crystalID);
		if (systemID ==8750)
            return fTimeWindow[systemID].at(detectorID-15-20-15-10).at(crystalID);
		if (systemID >=1010  && systemID <= 1100)
            return fTimeWindow[systemID].at(detectorID-1).at(crystalID-1);
		else return fTimeWindow[systemID].at(detectorID).at(crystalID);
        }
        return 0.;
    }


    int NofBins(std::string directoryName) {
        if(fNofBins.find(directoryName) != fNofBins.end()) {
            return fNofBins[directoryName];
        }
        return 10000;
    }
    double RangeLow(std::string directoryName) {
        if(fRangeLow.find(directoryName) != fRangeLow.end()) {
            return fRangeLow[directoryName];
        }
        return 0.5;
    }
    double RangeHigh(std::string directoryName) {
        if(fRangeHigh.find(directoryName) != fRangeHigh.end()) {
            return fRangeHigh[directoryName];
        }
        return 10000.5;
    }

private:
    std::string fNtupleName;

    int fVerbosityLevel;
    int fBufferSize;
    int fSortNumberOfEvents;

    bool fWriteTree;
    bool fWrite2DHist;
    //bool fWrite3DHist;
    bool fWriteNDHist;
    bool fWrite2DSGGHist;
    bool fWriteGriffinAddbackVector;

    double fGriffinAddbackVectorLengthmm;
    double fGriffinAddbackVectorDepthmm;
    double fGriffinAddbackVectorCrystalFaceDistancemm;

    
    double fDaemonWidth; 
    double fDaemonThreshold;

    std::map<int,std::vector<std::vector<TF1> > > fResolution;
    std::map<int,std::vector<std::vector<double> > > fThreshold;
    std::map<int,std::vector<std::vector<double> > > fThresholdWidth;
    std::map<int,std::vector<std::vector<double> > > fTimeWindow;

    std::map<std::string,int> fNofBins;
    std::map<std::string,double> fRangeLow;
    std::map<std::string,double> fRangeHigh;
};

#endif
