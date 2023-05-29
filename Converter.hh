#ifndef __CONVERTER_HH
#define __CONVERTER_HH

#include <vector>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TRandom3.h"
//#include <TRandom.h>
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
//#include "TH3I.h"
#include "THnSparse.h"
#include "TVector3.h"

#include "Settings.hh"
#include "Griffin.hh"
#include "Daemon.hh"

class Converter {
	public:
		Converter(std::vector<std::string>&, const std::string&, Settings*);
		~Converter();

		bool Run();

	private:
		bool AboveThreshold(double, int);
		bool InsideTimeWindow();
		bool DescantNeutronDiscrimination();

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
		//Daemon
		void AddDaemonTiles();

		void PrintStatistics();


		// CFD algorithm for daemon
		double CalculateCFD(TH1F * TimeHist);
		double GetTime(std::vector<double>*  fTime);
		bool GetLeadingEdge(std::vector<double>*  fTime);


		TH1F* Get1DHistogram(std::string, std::string);
		TH2F* Get2DHistogram(std::string, std::string);
		//TH3I* Get3DHistogram(std::string, std::string);
		TH3F* Get3DHistogram(std::string, std::string);
		THnSparseF* GetNDHistogram(std::string, std::string);

		void FillHistDetector1DCFDTime(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DCFDMonitor(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DPulseHeightBar1(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DPulseHeightBar2(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DPulseHeightBarCal1(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DPulseHeightBarCal2(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DPulseHeight(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DPulseHeightSum1(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DPulseHeightSum2(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DPulseHeightSum3(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DPulseHeightSum4(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DPulseHeightCalibrated(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DPulseHeightCalSum1(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DPulseHeightCalSum2(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DPulseHeightCalSum3(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DPulseHeightCalSum4(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DProcess(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DPMT(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DParticle(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DDeltaT(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DTOF(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DZDS(TH1F* hist1D, std::vector<Detector>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DTOFZDS(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::vector<Detector>* detectorZDS, std::string hist_name, std::string hist_dir);
		void FillHistDetector2DPmtDeltaT(TH2F* hist2D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector2DDetDeltaT(TH2F* hist2D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector2DParDeltaT(TH2F* hist2D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector2DPulseTOF(TH2F* hist2D, std::vector<DetectorDaemon>* detector, std::vector<Detector>* detectorZDS, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DEvent(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector2DEnergyTOF(TH2F* hist2D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DEnergyTOFZDS(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::vector<Detector>* detectorZDS, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DEnergyTOF(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DEnergy(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DDeltaY(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector2DPmtDeltaY(TH2F* hist2D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector2DDetDeltaY(TH2F* hist2D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector2DDetDeltaX(TH2F* hist2D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector2DDetDeltaPhi(TH2F* hist2D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector2DDetDeltaThetaPhi(TH2F* hist2D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector2DDetDeltaTheta(TH2F* hist2D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector2DPmtDeltaTheta(TH2F* hist2D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DArc(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector2DGammaTOF(TH2F* hist2D, std::vector<DetectorDaemon>* detector, std::vector<Detector>* detectorGriffin, std::vector<Detector>* detectorZDS, std::string hist_name, std::string hist_dir);
		void FillHistDetector2DGammaEnergy(TH2F* hist2D, std::vector<DetectorDaemon>* detector, std::vector<Detector>* detectorGriffin, std::vector<Detector>* detectorZDS, std::string hist_name, std::string hist_dir);
		void FillHistDetector3DGammaETOF(TH3F* hist3D, std::vector<DetectorDaemon>* detector, std::vector<Detector>* detectorGriffin, std::vector<Detector>* detectorZDS, std::string hist_name, std::string hist_dir);

		void FillHistDetector1DTOFDescantZDS(TH1F* hist1D, std::vector<Detector>* detector, std::vector<Detector>* detectorZDS, std::string hist_name, std::string hist_dir);
		void FillHistDetector2DGammaDescantTOF(TH2F* hist2D, std::vector<Detector>* detector, std::vector<Detector>* detectorGriffin, std::vector<Detector>* detectorZDS, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DEnergyTOFDescantZDS(TH1F* hist1D, std::vector<Detector>* detector, std::vector<Detector>* detectorZDS, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DEnergyRand1(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DEnergyRand2(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DCoinTOFZDS(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::vector<Detector>* detectorZDS, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DOpTime(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DOpEnergy(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DOpTotal(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector1DPulseHeightRatio(TH1F* hist1D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector2DPulseHeightRatioEDep(TH2F* hist2D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector2DPulseHeightRatioEDepBars(TH2F* hist2D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector2DPulseHeightRatioScaledEDepN(TH2F* hist2D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector2DPulseHeightRatioScaledEDepG(TH2F* hist2D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector2DPulseHeightEDep(TH2F* hist2D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector2DDepEDeltaT(TH2F* hist2D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector2DPulseHeightDeltaT(TH2F* hist2D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		void FillHistDetector2DTvTREcon(TH2F* hist2D, std::vector<DetectorDaemon>* detector, std::string hist_name, std::string hist_dir);
		
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
		//TRandom fRandom;

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

		Double_t fNumScintPhotons;
		Double_t fCollectedTop1;
		Double_t fCollectedTop2;
		Double_t fCollectedTop3;
		Double_t fCollectedBottom1;
		Double_t fCollectedBottom2;
		Double_t fCollectedBottom3;
		Double_t fCollectedFrontTop1;
		Double_t fCollectedFrontTop2;
		Double_t fCollectedFrontMid1;
		Double_t fCollectedFrontMid2;
		Double_t fCollectedFrontBottom1;
		Double_t fCollectedFrontBottom2;
		std::vector<double>*  fTimeTop1 = NULL;
		std::vector<double>*  fTimeTop2 = NULL;
		std::vector<double>*  fTimeTop3 = NULL;
		std::vector<double>*  fTimeTopTotal = NULL;
		std::vector<double>*  fTimeBottom1 = NULL;
		std::vector<double>*  fTimeBottom2 = NULL;
		std::vector<double>*  fTimeBottom3 = NULL;
		std::vector<double>*  fTimeBottomTotal = NULL;
		std::vector<double>*  fTimeFrontTop1 = NULL;
		std::vector<double>*  fTimeFrontTop2 = NULL;
		std::vector<double>*  fTimeFrontTopTotal = NULL;
		std::vector<double>*  fTimeFrontMid1 = NULL;
		std::vector<double>*  fTimeFrontMid2 = NULL;
		std::vector<double>*  fTimeFrontMidTotal = NULL;
		std::vector<double>*  fTimeFrontBottom1 = NULL;
		std::vector<double>*  fTimeFrontBottom2 = NULL;
		std::vector<double>*  fTimeFrontBottomTotal = NULL;
		std::vector<double>*  fOpTime = NULL;
		std::vector<double>*  fOpEnergy = NULL;
		Double_t fDepEnergy;
		Double_t fPosx;
		Double_t fPosy;
		Double_t fPosz;
		Double_t fTime;
		//To look at the output of CFD function
		TH1F * fTimeHist;
		//TH1F * fTimeHistTop;
		//TH1F * fTimeHistTop1;
		//TH1F * fTimeHistTop2;
		//TH1F * fTimeHistTop3;
		Double_t fCFDTimeTop1;
		Double_t fCFDTimeTop2;
		Double_t fCFDTimeTop3;
		Double_t fCFDTimeTopTotal;
		Double_t fCFDTimeBottom1;
		Double_t fCFDTimeBottom2;
		Double_t fCFDTimeBottom3;
		Double_t fCFDTimeBottomTotal;
		Double_t fCFDTimeFrontTop1;
		Double_t fCFDTimeFrontTop2;
		Double_t fCFDTimeFrontTopTotal;
		Double_t fCFDTimeFrontMid1;
		Double_t fCFDTimeFrontMid2;
		Double_t fCFDTimeFrontMidTotal;
		Double_t fCFDTimeFrontBottom1;
		Double_t fCFDTimeFrontBottom2;
		Double_t fCFDTimeFrontBottomTotal;

		bool   fSceptarHit;
		bool   fZDSHit;
		bool   fDescantHit;
		bool   fDescantHitNeutron;
		bool   fDaemonHit;
		bool   fDaemonBarsConfig;

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

		//Daemon Bars
		std::vector<DetectorDaemon>* fDaemonBarsArray;
		//Daemon Tiles
		std::vector<DetectorDaemon>* fDaemonTilesArray;
		std::vector<DetectorDaemon>* fDaemonBlueTiles;
		std::vector<DetectorDaemon>* fDaemonWhiteTiles;
		std::vector<DetectorDaemon>* fDaemonRedTiles;
		std::vector<DetectorDaemon>* fDaemonGreenTiles;
		std::vector<DetectorDaemon>* fDaemonYellowTiles;

		// ZDS
		std::vector<Detector>* fZDSDetector;

		// Paces
		std::vector<Detector>* fPacesArray;
		std::vector<Detector>* fPacesDetector;

		//histograms
		std::map<std::string,TList*> fHistograms;
};

#endif
