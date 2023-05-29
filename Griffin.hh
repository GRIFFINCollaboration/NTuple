#ifndef __GRIFFIN_HH
#define __GRIFFIN_HH

#include "TVector3.h"

class Detector : public TObject {
public:
    Detector(){};
    Detector(int evNumber, int detNumber, int cryNumber, double simEnergy, double energy, TVector3 pos, double time)
        : fEventNumber(evNumber), fDetectorId(detNumber), fCrystalId(cryNumber), fSimulationEnergy(simEnergy), fEnergy(energy), fPosition(pos), fTime(time) {
    }
	  ~Detector(){};

    void AddEnergy(double simEnergy, double energy) {
        fSimulationEnergy += simEnergy;
        fEnergy += energy;
    }
    void Set(int evNumber, int detNumber, int cryNumber, double simEnergy, double energy, TVector3 pos, double time) {
        fEventNumber = evNumber;
        fDetectorId = detNumber;
        fCrystalId = cryNumber;
        fSimulationEnergy = simEnergy;
        fEnergy = energy;
        fPosition = pos;
        fTime = time;
    }
    void SetTime(double time) {
        fTime = time;
    }
    void Clear(Option_t* opt = NULL) {
        fEventNumber = -1;
        fDetectorId = 0;
        fCrystalId = 0;
        fSimulationEnergy = 0;
        fEnergy = 0;
        fPosition.SetXYZ(0.,0.,0.);
        fTime = 0;
    }

    int EventNumber() {
        return fEventNumber;
    }
    int DetectorId() {
        return fDetectorId;
    }
    int CrystalId() {
        return fCrystalId;
    }
    double SimulationEnergy() {
        return fSimulationEnergy;
    }
    double Energy() {
        return fEnergy;
    }
    TVector3 Position() {
        return fPosition;
    }
    double Time() {
        return fTime;
    }

    double EnergyTOF(double fTOFCorrected) {
		double fEnergyTOF;
	    if (fTOFCorrected>0) {
		    //double fDistance = 50. + 7.5;
		    double fDistance = 50.;
		double fMass = 1008664.91595e-6; // u //Allison
		double c = 299792458.; // m/s
		double fConversion1 = 9.3149410242e5; // keV/u // Allison
		double fConversion2;
		fConversion2 = fConversion1 / (c*c);
		    double velocity = (fDistance/100.)/(fTOFCorrected*1.e-9);
		    double vel2 = velocity*velocity;
		    fEnergyTOF = 0.5 * fMass * vel2 * fConversion2;
	    }else fEnergyTOF = -1.;

	    return fEnergyTOF;
    }

private:
    int fEventNumber;
    int fDetectorId;
    int fCrystalId;
    double fSimulationEnergy;
    double fEnergy;
    TVector3 fPosition;
    double fTime;

    ClassDef(Detector,1);
};

//class GriffinDetector : public Detector {
//public:
//  using Detector::Detector;
//
//private:
//  ClassDef(GriffinDetector,1);
//};
//
//class GriffinBgo : public Detector {
//public:
//  using Detector::Detector;
//
//private:
//  ClassDef(GriffinBgo,1);
//};

#endif
