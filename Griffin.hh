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
