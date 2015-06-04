#ifndef __CONVERTER_HH
#define __CONVERTER_HH

#include <vector>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TRandom3.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TH3I.h"
#include "TVector3.h"

#include "Settings.hh"
#include "Griffin.hh"

class Converter {
public:
    Converter(std::vector<std::string>&, const std::string&, Settings*);
    ~Converter();

    bool Run();

private:
    bool AboveThreshold(double, int);
    bool InsideTimeWindow();

    // GRIFFIN
    void CheckGriffinCrystalAddback();
    void SupressGriffin();
    void SupressGriffinByNeighbouringAncillaryBgos();
    void SupressGriffinBySceptar();
    void AddbackGriffin();
    void AddbackGriffinNeighbour();
    void AddbackGriffinNeighbourVector();
    // LaBr
    void CheckLaBrDetectorAddback();
    void SupressLaBr();
    void SupressLaBrByNeighbouringGriffinShields();
    void AddbackLaBr();
    // EightPi
    void CheckEightPiDetectorAddback();
    void SupressEightPi();
    void AddbackEightPi();
    // Ancillary BGO
    void CheckAncillaryBgoCrystalAddback();
    void AddbackAncillaryBgo();
    // SCEPTAR
    void CheckSceptarDetectorAddback();
    void AddbackSceptar();
    // DESCANT
    void CheckDescantDetectorAddback();
    void AddbackDescant();
    // Paces
    void CheckPacesDetectorAddback();
    void AddbackPaces();

    void PrintStatistics();

    TH1F* Get1DHistogram(std::string, std::string);
    TH2F* Get2DHistogram(std::string, std::string);
    TH3I* Get3DHistogram(std::string, std::string);

    void FillHistDetector1DGamma(TH1F* hist1D, std::vector<Detector>* detector, std::string hist_name, std::string hist_dir);
    void FillHistDetector2DGammaGamma(TH2F* hist2D, std::vector<Detector>* detector, std::string hist_name, std::string hist_dir);

    void FillHistDetector1DGammaNR(TH1F* hist1D, std::vector<Detector>* detector, std::string hist_name, std::string hist_dir);
    void FillHistDetector2DGammaGammaNR(TH2F* hist2D, std::vector<Detector>* detector, std::string hist_name, std::string hist_dir);

    void FillHist2DGriffinSceptarHitPattern(TH2F* hist2D, std::vector<Detector>* detector1, std::vector<Detector>* detector2, std::string hist_name, std::string hist_dir);
    void FillHist2DGriffinHitPattern(TH2F* hist2D, std::vector<Detector>* detector, std::string hist_name, std::string hist_dir);

    TVector3 GriffinCrystalCenterPosition(int cry, int det);
    bool AreGriffinCrystalCenterPositionsWithinVectorLength(int cry1, int det1, int cry2, int det2);

    double transX(double x, double y, double z, double theta, double phi);
    double transY(double x, double y, double z, double theta, double phi);
    double transZ(double x, double y, double z, double theta, double phi);

    Settings* fSettings;
    TChain fChain;
    TFile* fOutput;
    TTree fTree;
    TRandom3 fRandom;

    Int_t LaBrGriffinNeighbours_det[8][3];
    Int_t LaBrGriffinNeighbours_cry[8][3];

    Int_t GriffinAncillaryBgoNeighbours_det[16][2];
    Int_t GriffinAncillaryBgoNeighbours_cry[16][2];

    Int_t GriffinSceptarSuppressors_det[16][4];

    Int_t GriffinNeighbours_counted[16];
    Int_t GriffinNeighbours_det[16][4];

    double GriffinDetCoords[16][5];

    double GriffinCryMap[64][64];
    double GriffinCryMapCombos[52][2];

    double GriffinDetMap[16][16];
    double GriffinDetMapCombos[7][2];

    TVector3 GriffinCrystalCenterVectors[64];

    //branches of input tree/chain
    Int_t fEventNumber;
    Int_t fTrackID;
    Int_t fParentID;
    Int_t fStepNumber;
    Int_t fParticleType;
    Int_t fProcessType;
    Int_t fSystemID;
    Int_t fCryNumber;
    Int_t fDetNumber;
    Double_t fDepEnergy;
    Double_t fPosx;
    Double_t fPosy;
    Double_t fPosz;
    Double_t fTime;

    double fSmearedEnergy;
    bool   fSceptarHit;

    //branches of output tree
    // GRIFFIN
    std::vector<Detector>* fGriffinCrystal;
    std::vector<Detector>* fGriffinDetector;
    std::vector<Detector>* fGriffinNeighbour;
    std::vector<Detector>* fGriffinNeighbourVector;
    std::vector<Detector>* fGriffinArray;
    std::vector<Detector>* fGriffinBgo;
    std::vector<Detector>* fGriffinBgoBack;

    // LaBr
    std::vector<Detector>* fLaBrArray;
    std::vector<Detector>* fLaBrDetector;

    // EightPi
    std::vector<Detector>* fEightPiArray;
    std::vector<Detector>* fEightPiDetector;
    std::vector<Detector>* fEightPiBgoDetector;

    // Ancillary BGO
    std::vector<Detector>* fAncillaryBgoArray;
    std::vector<Detector>* fAncillaryBgoCrystal;
    std::vector<Detector>* fAncillaryBgoDetector;

    // Sceptar
    std::vector<Detector>* fSceptarArray;
    std::vector<Detector>* fSceptarDetector;

    // Descant
    std::vector<Detector>* fDescantArray;
    std::vector<Detector>* fDescantBlueDetector;
    std::vector<Detector>* fDescantGreenDetector;
    std::vector<Detector>* fDescantRedDetector;
    std::vector<Detector>* fDescantWhiteDetector;
    std::vector<Detector>* fDescantYellowDetector;

    // Paces
    std::vector<Detector>* fPacesArray;
    std::vector<Detector>* fPacesDetector;

    //histograms
    std::map<std::string,TList*> fHistograms;
};

#endif
