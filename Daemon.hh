#ifndef __DEAMON_HH
#define __DEAMON_HH

#include <iostream>
#include "TVector3.h"
#include "TMath.h"
#include <TRandom.h>

class DetectorDaemon : public TObject {
	public:
		static TRandom rand;
		DetectorDaemon(){};
		DetectorDaemon(int evNumber, int detNumber, int cryNumber, double simEnergy, double energy, TVector3 pos, double time, int particleType, int processType, int numCollectedPhotonsTop1, int numCollectedPhotonsTop2, int numCollectedPhotonsTop3, int numCollectedPhotonsBottom1, int numCollectedPhotonsBottom2, int numCollectedPhotonsBottom3, int numCollectedPhotonsFrontTop1, int numCollectedPhotonsFrontTop2, int numCollectedPhotonsFrontMid1, int numCollectedPhotonsFrontMid2, int numCollectedPhotonsFrontBottom1, int numCollectedPhotonsFrontBottom2, double timetop1, double timetop2, double timetop3, double timebottom1, double timebottom2, double timebottom3, double timefronttop1, double timefronttop2, double timefrontmid1, double timefrontmid2, double timefrontbottom1, double timefrontbottom2, int systemID)
			: fEventNumber(evNumber), fDetectorId(detNumber), fCrystalId(cryNumber), fSimulationEnergy(simEnergy), fEnergy(energy), fPosition(pos), fTime(time), fParticleType(particleType), fProcessType(processType), fCollectedTop1(numCollectedPhotonsTop1), fCollectedTop2(numCollectedPhotonsTop2), fCollectedTop3(numCollectedPhotonsTop3), fCollectedBottom1(numCollectedPhotonsBottom1), fCollectedBottom2(numCollectedPhotonsBottom2), fCollectedBottom3(numCollectedPhotonsBottom3), fCollectedFrontTop1(numCollectedPhotonsFrontTop1), fCollectedFrontTop2(numCollectedPhotonsFrontTop2), fCollectedFrontMid1(numCollectedPhotonsFrontMid1), fCollectedFrontMid2(numCollectedPhotonsFrontMid2), fCollectedFrontBottom1(numCollectedPhotonsFrontBottom1), fCollectedFrontBottom2(numCollectedPhotonsFrontBottom2), fCFDTimeTop1(timetop1), fCFDTimeTop2(timetop2), fCFDTimeTop3(timetop3), fCFDTimeBottom1(timebottom1), fCFDTimeBottom2(timebottom2), fCFDTimeBottom3(timebottom3), fCFDTimeFrontTop1(timefronttop1), fCFDTimeFrontTop2(timefronttop2),fCFDTimeFrontMid1(timefrontmid1), fCFDTimeFrontMid2(timefrontmid2), fCFDTimeFrontBottom1(timefrontbottom1), fCFDTimeFrontBottom2(timefrontbottom2), fSystemId(systemID){


				//			std::cout << "Begin of fEvent: " << fEventNumber << " and detNum: " << fDetectorId << std::endl;
				topHit = false;
				bottomHit = false;
				frontTopHit = false;
				frontMidHit = false;
				frontBottomHit = false;
				f2pmt = 20;
				fTOF = -2;
				fMaxTDiff = -2;
				fC_effective = -2;
				fTopMin = DBL_MAX;
				fBottomMin = DBL_MAX;
				fFrontTopMin = DBL_MAX;
				fFrontMidMin = DBL_MAX;
				fFrontBottomMin = DBL_MAX;
				fTopMin1 = DBL_MAX;
				fBottomMin1 = DBL_MAX;
				fFrontTopMin1 = DBL_MAX;
				fFrontMidMin1 = DBL_MAX;
				fFrontBottomMin1 = DBL_MAX;
				for(int i = 0 ; i<= detNum ; ++i){
					MaxDeltaT[i] = MaxDeltaTTop[i]+MaxDeltaTBot[i]+MaxDeltaTMid[i];
				}

				//Detector configuration: 1 is front bars, 2 is Unsegmented Tiles, 3 is Segmented Tiles, 0 is bars with no front
				int DetConfiguration = 1;
				//int DetConfiguration = 2;
				//int DetConfiguration = 3;
				//int DetConfiguration = 0;


	//			TRandom rand;

				fConversion2 = fConversion1 / (c*c);
				fTimingUncertainty = fTimingUncertaintyFWHM/2.355; //.6/2.35


				//Determine the earliest time for each pmt channel based on location
				std::vector<double> Across(5, -2);
				int AcrossCounter = 0;
				//std::cout << "dbl_max: " << DBL_MAX << std::endl;

				if (fCollectedTop1>=fThreshold) topCFD[0] = fCFDTimeTop1;
				if (fCollectedTop2>=fThreshold) topCFD[1] = fCFDTimeTop2;
				if (fCollectedTop3>=fThreshold) topCFD[2] = fCFDTimeTop3;
				fTopMin = std::min({topCFD[0], topCFD[1], topCFD[2]});
				//std::cout << "fTopMin: " << fTopMin << std::endl;
				if (fTopMin != DBL_MAX && fTopMin > 0.) {
					Across[AcrossCounter] = fTopMin;
					AcrossCounter++;
					topHit = true;
				}
				if (fCollectedBottom1>=fThreshold) bottomCFD[0] = fCFDTimeBottom1;
				if (fCollectedBottom2>=fThreshold) bottomCFD[1] = fCFDTimeBottom2;
				if (fCollectedBottom3>=fThreshold) bottomCFD[2] = fCFDTimeBottom3;
				fBottomMin = std::min({bottomCFD[0], bottomCFD[1], bottomCFD[2]});
				//std::cout << "fBottomMin: " << fBottomMin << std::endl;
				if (fBottomMin != DBL_MAX && fBottomMin>0.) {
					Across[AcrossCounter] = fBottomMin;
					AcrossCounter++;
					bottomHit = true;
				}
				if (fCollectedFrontTop1>=fThreshold) frontTopCFD[0] = fCFDTimeFrontTop1;
				if (fCollectedFrontTop2>=fThreshold) frontTopCFD[1] = fCFDTimeFrontTop2;
				fFrontTopMin = std::min({frontTopCFD[0], frontTopCFD[1]});
				//std::cout << "fFrontTopMin: " << fFrontTopMin << std::endl;
				if (fFrontTopMin != DBL_MAX && fFrontTopMin>0.) {
					Across[AcrossCounter] = fFrontTopMin;
					AcrossCounter++;
					frontTopHit = true;
				}
				if (fCollectedFrontMid1>=fThreshold) frontMidCFD[0] = fCFDTimeFrontMid1;
				if (fCollectedFrontMid2>=fThreshold) frontMidCFD[1] = fCFDTimeFrontMid2;
				fFrontMidMin = std::min({frontMidCFD[0], frontMidCFD[1]});
				//std::cout << "fFrontMidMin: " << fFrontMidMin << std::endl;
				if (fFrontMidMin != DBL_MAX && fFrontMidMin>0.) {
					Across[AcrossCounter] = fFrontMidMin;
					AcrossCounter++;
					frontMidHit = true;
				}
				if (fCollectedFrontBottom1>=fThreshold) frontBottomCFD[0] = fCFDTimeFrontBottom1;
				if (fCollectedFrontBottom2>=fThreshold) frontBottomCFD[1] = fCFDTimeFrontBottom2;
				fFrontBottomMin = std::min({frontBottomCFD[0], frontBottomCFD[1]});
				//std::cout << "fFrontBottomMin: " << fFrontBottomMin << std::endl;
				if (fFrontBottomMin != DBL_MAX && fFrontBottomMin > 0.) {
					Across[AcrossCounter] = fFrontBottomMin;
					AcrossCounter++;
					frontBottomHit = true;
				}


				if (DetConfiguration == 1 || DetConfiguration == 0) { // for no front just need to add the MaxDeltaTNoFront

					fDistance = 50.-fThickness/2.-.05; //cm - detector with input thickness (and uses middle), no lead, spacing (0.05cm for optical wrap).

					//Which PMTs have the 2 smallest times
					if (AcrossCounter == 0){
						f2pmt = 20;
						fTOF = -2;
						fC_effective = -2;
						fYDelta = -200;
						fThetaSim = -200; 
						fPhiSim = -200;
						fThetaCalc = -200;
						fPhiCalc = -200;
						fPhiDiff = -400;
						fThetaDiff = -400;
					}
					double smallest=-2, secondSmallest = -2;
					if (AcrossCounter == 1 && Across[0]>0){
						smallest = Across[0];
						secondSmallest = -2;
						f2pmt = 10;
						fTOF = smallest;
						fYPos = -150;
						fYDelta = -200;
						fXPos = XPos[fDetectorId];;
						fZPos = sqrt(fDistance*fDistance - fYPos*fYPos - XPos[fDetectorId]*XPos[fDetectorId]);
						fC_effective = -1;
						fArcDiff = -1.;
						fThetaSim = -200; 
						fPhiSim = -200;
						fThetaCalc = -200;
						fPhiCalc = -200;
						fPhiDiff = -400;
						fThetaDiff = -400;
					}
					if (AcrossCounter > 1) {
						if (Across[0] <= Across[1] && Across[0]>0 && Across[1]>0) {
							smallest = Across[0];
							secondSmallest = Across[1];
						} else if (Across[0] > Across[1] && Across[0]>0 && Across[1]>0) {
							smallest = Across[1];
							secondSmallest = Across[0];
						}
						for (int k = 2 ; k < AcrossCounter; ++k) {
							if(smallest >= Across[k] && Across[k]>0){
								secondSmallest = smallest;
								smallest = Across[k];
							} else if (secondSmallest > Across[k] && smallest < Across[k] && Across[k]>0) {
								secondSmallest = Across[k];
							}
						}
					}
					//	std::cout << "Smallest and second: " << smallest << " and " << secondSmallest << std::endl;
					//			fTOF = (smallest+secondSmallest)/2.;
					//	std::cout << "fTOF: " << fTOF << std::endl;

					//Only use the 2 earliest times, set all other pmt to false
					if(smallest == fTopMin || secondSmallest == fTopMin) topHit = true;
					else	topHit = false;
					if(smallest == fBottomMin || secondSmallest == fBottomMin) bottomHit = true;
					else	bottomHit = false;
					if(smallest == fFrontTopMin || secondSmallest == fFrontTopMin) frontTopHit = true;
					else frontTopHit = false;
					if(smallest == fFrontMidMin || secondSmallest == fFrontMidMin) frontMidHit = true;
					else frontMidHit = false;
					if(smallest == fFrontBottomMin || secondSmallest == fFrontBottomMin) frontBottomHit = true;
					else frontBottomHit = false;
					//	std::cout << "fTOF: " << fTOF << std::endl;

					//Make the correction for optical photon speed within bars based on the pmt's that fired and their corresponding delta T
					double arcLength;
					double R;
					double theta;
					//Top and Bottom
					if(bottomHit && topHit   && !frontTopHit && !frontMidHit && !frontBottomHit) {
						//std::cout << "Case 1" << std::endl;
						//std::cout << "Smallest and second and MaxDeltaT: " << fTopMin << " and " << fBottomMin << " and " << MaxDeltaT[fDetectorId] << std::endl;
						f2pmt = 1;
						fTopMin1 = rand.Gaus(fTopMin, fTimingUncertainty);
						fBottomMin1 = rand.Gaus(fBottomMin, fTimingUncertainty);
						fTOF = (fTopMin1+fBottomMin1)/2. - 0.5*MaxDeltaT[fDetectorId];
						fMaxTDiff = MaxDeltaT[fDetectorId];
						fRand11 = fTopMin1 - fTopMin;
						fRand12 = fBottomMin1 - fBottomMin;
					/*	if(fEventNumber == 89 || fEventNumber == 434){
								std::cout << "EventNumber: " << fEventNumber << std::endl;
								std::cout << "detNum: " << fDetectorId << std::endl;
								std::cout << "fTOF: " << fTOF << std::endl;
								std::cout << "top1: " << topCFD[0] << std::endl;
								std::cout << "top2: " << topCFD[1] << std::endl;
								std::cout << "top3: " << topCFD[2] << std::endl;
								std::cout << "bottom1: " << bottomCFD[0] << std::endl;
								std::cout << "bottom2: " << bottomCFD[1] << std::endl;
								std::cout << "bottom3: " << bottomCFD[2] << std::endl;
						}	
					*/	fC_effective = ArcLength[fDetectorId]/fMaxTDiff;
						//arcLength = 0.5 * 100. * 1.e-9 * fC_effective * (fBottomMin - fTopMin);
						arcLength = abs(0.5 * fC_effective * (fBottomMin1 - fTopMin1));
						R = sqrt(fDistance*fDistance - XPos[fDetectorId]*XPos[fDetectorId]); // cm
						theta = abs(arcLength / R);
						//fYPos = R * sin(theta); // cm
						fYPos = abs(R * sin(theta)); // cm
						//if (arcLength<0) fYPos = - fYPos;
						if ( fDetectorId >= 5 && fDetectorId <= 8){
							if(fTopMin <= fBottomMin) fYPos = 0.5*(YPos[fDetectorId] + fPMTSize + fBeamlineXY) + fYPos;
							if(fTopMin > fBottomMin) fYPos = 0.5*(YPos[fDetectorId] + fPMTSize + fBeamlineXY) - fYPos;
						}
						if ( fDetectorId >= 14){
							if(fTopMin <= fBottomMin) fYPos = -0.5*(YPos[fDetectorId] + fPMTSize + fBeamlineXY) + fYPos;
							if(fTopMin > fBottomMin) fYPos = -0.5*(YPos[fDetectorId] + fPMTSize + fBeamlineXY) - fYPos;
						} else {
							//if(fTopMin <= fBottomMin) fYPos = fYPos;
							if(fTopMin > fBottomMin) fYPos = - fYPos;
						}
						fYDelta = pos.Y()/10. - fYPos;
					} 
					// Top and Front Top
					if(!bottomHit && topHit  && frontTopHit  && !frontMidHit && !frontBottomHit) {
						//	std::cout << "Case 2" << std::endl;
						//	std::cout << "eventNum: " << fEventNumber << std::endl;
						//	std::cout << "Smallest and second and MaxDeltaT: " << fTopMin << " and " << fFrontTopMin << " and " << MaxDeltaTTop[fDetectorId] << std::endl;
						f2pmt = 2;
						fTopMin1 = rand.Gaus(fTopMin, fTimingUncertainty);
						fFrontTopMin1 = rand.Gaus(fFrontTopMin, fTimingUncertainty);
						fTOF = (fTopMin1+fFrontTopMin1)/2. - 0.5*MaxDeltaTTop[fDetectorId];
						fMaxTDiff = MaxDeltaTTop[fDetectorId];
						fRand21 = fTopMin1 - fTopMin;
						fRand22 = fFrontTopMin1 - fFrontTopMin;
					/*	if(fEventNumber == 89 || fEventNumber == 434){
								std::cout << "EventNumber: " << fEventNumber << std::endl;
								std::cout << "detNum: " << fDetectorId << std::endl;
								std::cout << "fTOF: " << fTOF << std::endl;
							std::cout << "top1: " << topCFD[0] << std::endl;
							std::cout << "top2: " << topCFD[1] << std::endl;
							std::cout << "top3: " << topCFD[2] << std::endl;
							std::cout << "frontTop1: " << frontTopCFD[0] << std::endl;
							std::cout << "frontTop2: " << frontTopCFD[1] << std::endl;
						}
					*/	fC_effective = ArcLength_FrontTopBot_Outside[fDetectorId]/fMaxTDiff;
						arcLength = abs(fC_effective * 0.5 * (fFrontTopMin1 - fTopMin1));
						R = sqrt(fDistance*fDistance - XPos[fDetectorId]*XPos[fDetectorId]); // cm
						theta = abs(arcLength / R);
						fYPos = abs(R * sin(theta)); // cm
						double offset = (YPos[fDetectorId] + frontPMT[fDetectorId])*0.5;
						if (fTopMin <= fFrontTopMin) fYPos = offset + fYPos;
						if (fTopMin > fFrontTopMin) fYPos = offset - fYPos;
						//std::cout << "fYPos3: " << fYPos << std::endl;
						fYDelta = pos.Y()/10. - fYPos;
						//std::cout << "SimPos: " << pos.Y()/10. << std::endl;
						//std::cout << "DeltaY: " << fYDelta << std::endl;

					} 
					//Bottom and Front Bottom
					if(bottomHit && !topHit  && !frontTopHit && !frontMidHit && frontBottomHit ) {
						//std::cout << "Case 3" << std::endl;
						//	std::cout << "Smallest and second and MaxDeltaT: " << fBottomMin << " and " << fFrontBottomMin << " and " << MaxDeltaTBot[fDetectorId] << std::endl;
						f2pmt = 3;
						fFrontBottomMin1 = rand.Gaus(fFrontBottomMin, fTimingUncertainty);
						fBottomMin1 = rand.Gaus(fBottomMin, fTimingUncertainty);
						fTOF = (fBottomMin1+fFrontBottomMin1)/2. - 0.5*MaxDeltaTBot[fDetectorId];
						fMaxTDiff = MaxDeltaTBot[fDetectorId];
						fRand31 = fFrontBottomMin1 - fFrontBottomMin;
						fRand32 = fBottomMin1 - fBottomMin;
					/*	if(fEventNumber == 89 || fEventNumber == 434){
								std::cout << "EventNumber: " << fEventNumber << std::endl;
								std::cout << "detNum: " << fDetectorId << std::endl;
								std::cout << "fTOF: " << fTOF << std::endl;
							std::cout << "bottom1: " << bottomCFD[0] << std::endl;
							std::cout << "bottom2: " << bottomCFD[1] << std::endl;
							std::cout << "bottom3: " << bottomCFD[2] << std::endl;
							std::cout << "frontBottom1: " << frontBottomCFD[0] << std::endl;
							std::cout << "frontBottom2: " << frontBottomCFD[1] << std::endl;
						}
					*/	fC_effective = ArcLength_FrontTopBot_Outside[fDetectorId]/fMaxTDiff;
						arcLength = abs(fC_effective * 0.5 * (fFrontBottomMin1 - fBottomMin1));
						R = sqrt(fDistance*fDistance - XPos[fDetectorId]*XPos[fDetectorId]); // cm
						theta = abs(arcLength / R);
						fYPos = abs(R * sin(theta)); // cm
						double offset = -1.*(YPos[fDetectorId] + frontPMT[fDetectorId])*0.5;
						if(fBottomMin <= fFrontBottomMin) fYPos = offset - fYPos;
						if(fBottomMin > fFrontBottomMin) fYPos = offset + fYPos;
						fYDelta = pos.Y()/10. - fYPos;
					} 
					// Top and Front Mid
					if(!bottomHit && topHit  && !frontTopHit && frontMidHit  && !frontBottomHit) {
						//std::cout << "Case 4" << std::endl;
						//	std::cout << "Smallest and second and MaxDeltaT: " << fTopMin << " and " << fFrontMidMin << " and " << MaxDeltaTTop[fDetectorId] << std::endl;
						f2pmt = 4;
						fTopMin1 = rand.Gaus(fTopMin, fTimingUncertainty);
						fFrontMidMin1 = rand.Gaus(fFrontMidMin, fTimingUncertainty);
						fTOF = (fTopMin1+fFrontMidMin1)/2. - 0.5*MaxDeltaTTop[fDetectorId];
						fMaxTDiff = MaxDeltaTTop[fDetectorId];
						fRand41 = fTopMin1 - fTopMin;
						fRand42 = fFrontMidMin1 - fFrontMidMin;
					/*	if(fEventNumber == 89 || fEventNumber == 434){
								std::cout << "EventNumber: " << fEventNumber << std::endl;
								std::cout << "detNum: " << fDetectorId << std::endl;
								std::cout << "fTOF: " << fTOF << std::endl;
							std::cout << "top1: " << topCFD[0] << std::endl;
							std::cout << "top2: " << topCFD[1] << std::endl;
							std::cout << "top3: " << topCFD[2] << std::endl;
							std::cout << "frontMid1: " << frontMidCFD[0] << std::endl;
							std::cout << "frontMid2: " << frontMidCFD[1] << std::endl;
							}						
					*/	fC_effective = ArcLength_FrontMid_Outside[fDetectorId]/fMaxTDiff;
						if ( fDetectorId >= 14) fC_effective = ArcLength_FrontMid_Inside[fDetectorId]/fMaxTDiff;

						arcLength = abs(fC_effective * 0.5 * (fFrontMidMin1 - fTopMin1));
						R = sqrt(fDistance*fDistance - XPos[fDetectorId]*XPos[fDetectorId]); // cm
						theta = abs(arcLength / R);
						fYPos = abs(R * sin(theta)); // cm
						if(fDetectorId >= 14){
							if(fTopMin <= fFrontMidMin) fYPos = -0.5*(fPMTSize + fBeamlineXY + midPMT[fDetectorId]) + fYPos;
							if(fTopMin > fFrontMidMin) fYPos = -0.5*(fPMTSize + fBeamlineXY + midPMT[fDetectorId]) - fYPos;
						} else{
							if(fTopMin <= fFrontMidMin) fYPos = 0.5*(YPos[fDetectorId] + midPMT[fDetectorId]) + fYPos;
							if(fTopMin > fFrontMidMin) fYPos = 0.5*(YPos[fDetectorId] + midPMT[fDetectorId]) - fYPos;
						} 
						fYDelta = pos.Y()/10. - fYPos;
					}
					// Bottom and Front Mid
					if(bottomHit && !topHit  && !frontTopHit && frontMidHit  && !frontBottomHit) {
						//std::cout << "Case 5" << std::endl;
						//	std::cout << "Smallest and second and MaxDeltaT: " << fBottomMin << " and " << fFrontMidMin << " and " << MaxDeltaTBot[fDetectorId] << std::endl;
						f2pmt = 5;
						fFrontMidMin1 = rand.Gaus(fFrontMidMin, fTimingUncertainty);
						fBottomMin1 = rand.Gaus(fBottomMin, fTimingUncertainty);
						fTOF = (fBottomMin1+fFrontMidMin1)/2. - 0.5*MaxDeltaTBot[fDetectorId];
						fMaxTDiff = MaxDeltaTBot[fDetectorId];
						fRand51 = fFrontMidMin1 - fFrontMidMin;
						fRand52 = fBottomMin1 - fBottomMin;
					/*	if(fEventNumber == 89 || fEventNumber == 434){
								std::cout << "EventNumber: " << fEventNumber << std::endl;
								std::cout << "detNum: " << fDetectorId << std::endl;
								std::cout << "fTOF: " << fTOF << std::endl;
							std::cout << "bottom1: " << bottomCFD[0] << std::endl;
							std::cout << "bottom2: " << bottomCFD[1] << std::endl;
							std::cout << "bottom3: " << bottomCFD[2] << std::endl;
							std::cout << "frontMid1: " << frontMidCFD[0] << std::endl;
							std::cout << "frontMid2: " << frontMidCFD[1] << std::endl;
						}	
					*/	fC_effective = ArcLength_FrontMid_Outside[fDetectorId]/fMaxTDiff;
						if ( fDetectorId >= 5 && fDetectorId <= 8 ) fC_effective = ArcLength_FrontMid_Inside[fDetectorId]/fMaxTDiff;

						arcLength = abs(fC_effective * 0.5 * (fFrontMidMin1 - fBottomMin1));
						R = sqrt(fDistance*fDistance - XPos[fDetectorId]*XPos[fDetectorId]); // cm
						theta = abs(arcLength / R);
						fYPos = abs(R * sin(theta)); // cm

						if ( fDetectorId >= 5 && fDetectorId <= 8){
							if(fBottomMin <= fFrontMidMin) fYPos = 0.5*(fPMTSize + fBeamlineXY + midPMT[fDetectorId]) - fYPos;
							if(fBottomMin > fFrontMidMin) fYPos = 0.5*(fPMTSize + fBeamlineXY + midPMT[fDetectorId]) + fYPos;

						} else {
							if(fBottomMin <= fFrontMidMin) fYPos = -0.5*(YPos[fDetectorId]+midPMT[fDetectorId]) - fYPos;
							if(fBottomMin > fFrontMidMin) fYPos =  -0.5*(YPos[fDetectorId]+midPMT[fDetectorId]) + fYPos;
						}
						fYDelta = pos.Y()/10. - fYPos;
					} 
					// Top and Front Bottom
					if(!bottomHit && topHit  && !frontTopHit && !frontMidHit && frontBottomHit ) {
						//std::cout << "Case 6" << std::endl;
						//	std::cout << "Smallest and second and MaxDeltaT: " << fTopMin << " and " << fFrontBottomMin << " and " << MaxDeltaTTop[fDetectorId]+ MaxDeltaTMid[fDetectorId]  << std::endl;
						f2pmt = 6;
						fTopMin1 = rand.Gaus(fTopMin, fTimingUncertainty);
						fFrontBottomMin1 = rand.Gaus(fFrontBottomMin, fTimingUncertainty);
						fTOF = (fTopMin1+fFrontBottomMin1)/2. - 0.5*(MaxDeltaTTop[fDetectorId]+ MaxDeltaTMid[fDetectorId]);
						fMaxTDiff = MaxDeltaTTop[fDetectorId] + MaxDeltaTMid[fDetectorId];
						fRand61 = fTopMin1 - fTopMin;
						fRand62 = fFrontBottomMin1 - fFrontBottomMin;
					/*	if(fEventNumber == 89 || fEventNumber == 434){
								std::cout << "EventNumber: " << fEventNumber << std::endl;
								std::cout << "detNum: " << fDetectorId << std::endl;
								std::cout << "fTOF: " << fTOF << std::endl;
							std::cout << "top1: " << topCFD[0] << std::endl;
							std::cout << "top2: " << topCFD[1] << std::endl;
							std::cout << "top3: " << topCFD[2] << std::endl;
							std::cout << "frontBottom1: " << frontBottomCFD[0] << std::endl;
							std::cout << "frontBottom2: " << frontBottomCFD[1] << std::endl;
						}
					*/	fC_effective = (ArcLength[fDetectorId] -  ArcLength_FrontTopBot_Outside[fDetectorId])/fMaxTDiff;
						arcLength = abs(fC_effective * 0.5 * (fFrontBottomMin1 - fTopMin1));
						R = sqrt(fDistance*fDistance - XPos[fDetectorId]*XPos[fDetectorId]); // cm
						theta = abs(arcLength / R);
						fYPos = abs(R * sin(theta)); // cm
						if(fTopMin <= fFrontBottomMin) fYPos = 0.5*(YPos[fDetectorId] - frontPMT[fDetectorId]) + fYPos;
						if(fTopMin > fFrontBottomMin) fYPos = 0.5*(YPos[fDetectorId] - frontPMT[fDetectorId]) - fYPos;

						fYDelta = pos.Y()/10. - fYPos;
					} 
					// Bottom and Front Top
					if(bottomHit && !topHit  && frontTopHit  && !frontMidHit && !frontBottomHit) {
						//std::cout << "Case 7" << std::endl;
						//	std::cout << "Smallest and second and MaxDeltaT: " << fBottomMin << " and " << fFrontTopMin << " and " << MaxDeltaTBot[fDetectorId]+ MaxDeltaTMid[fDetectorId]<< std::endl;
						f2pmt = 7;
						fFrontTopMin1 = rand.Gaus(fFrontTopMin, fTimingUncertainty);
						fBottomMin1 = rand.Gaus(fBottomMin, fTimingUncertainty);
						fTOF = (fBottomMin1+fFrontTopMin1)/2. - 0.5*(MaxDeltaTBot[fDetectorId]+ MaxDeltaTMid[fDetectorId]);
						fMaxTDiff = MaxDeltaTBot[fDetectorId] + MaxDeltaTMid[fDetectorId];
						fRand71 = fFrontTopMin1 - fFrontTopMin;
						fRand72 = fBottomMin1 - fBottomMin;
					/*	if(fEventNumber == 89 || fEventNumber == 434){
								std::cout << "EventNumber: " << fEventNumber << std::endl;
								std::cout << "detNum: " << fDetectorId << std::endl;
								std::cout << "fTOF: " << fTOF << std::endl;
							std::cout << "bottom1: " << bottomCFD[0] << std::endl;
							std::cout << "bottom2: " << bottomCFD[1] << std::endl;
							std::cout << "bottom3: " << bottomCFD[2] << std::endl;
							std::cout << "frontTop1: " << frontTopCFD[0] << std::endl;
							std::cout << "frontTop2: " << frontTopCFD[1] << std::endl;
						}
					*/	fC_effective = (ArcLength[fDetectorId] -  ArcLength_FrontTopBot_Outside[fDetectorId])/fMaxTDiff;
						arcLength = abs(fC_effective * 0.5 * (fBottomMin1 - fFrontTopMin1));
						R = sqrt(fDistance*fDistance - XPos[fDetectorId]*XPos[fDetectorId]); // cm
						theta = abs(arcLength / R);
						fYPos = abs(R * sin(theta)); // cm
						if(fBottomMin <= fFrontTopMin) fYPos = 0.5*(frontPMT[fDetectorId]-YPos[fDetectorId]) - fYPos;
						if(fBottomMin > fFrontTopMin) fYPos = 0.5*(frontPMT[fDetectorId]-YPos[fDetectorId]) + fYPos;

						fYDelta = pos.Y()/10. - fYPos;
					} 
					// Front Bottom and Front Top
					if(!bottomHit && !topHit  && frontTopHit  && !frontMidHit && frontBottomHit) {
						//std::cout << "Case 8" << std::endl;
						//	std::cout << "Smallest and second and MaxDeltaT: " << fFrontBottomMin << " and " << fFrontTopMin << " and " << MaxDeltaTMid[fDetectorId]<< std::endl;
						f2pmt = 8;
						fFrontTopMin1 = rand.Gaus(fFrontTopMin, fTimingUncertainty);
						fFrontBottomMin1 = rand.Gaus(fFrontBottomMin, fTimingUncertainty);
						fTOF = (fFrontBottomMin1+fFrontTopMin1)/2. - 0.5*MaxDeltaTMid[fDetectorId];
						fMaxTDiff = MaxDeltaTMid[fDetectorId];
						fRand81 = fFrontTopMin1 - fFrontTopMin;
						fRand82 = fFrontBottomMin1 - fFrontBottomMin;
					/*	if(fEventNumber == 89 || fEventNumber == 434){
								std::cout << "EventNumber: " << fEventNumber << std::endl;
								std::cout << "detNum: " << fDetectorId << std::endl;
								std::cout << "fTOF: " << fTOF << std::endl;
							std::cout << "frontTop1: " << frontTopCFD[0] << std::endl;
							std::cout << "frontTop2: " << frontTopCFD[1] << std::endl;
							std::cout << "frontBottom1: " << frontBottomCFD[0] << std::endl;
							std::cout << "frontBottom2: " << frontBottomCFD[1] << std::endl;
						}
					*/	fC_effective = (ArcLength_FrontTop_FrontBot[fDetectorId])/fMaxTDiff;
						arcLength = abs(fC_effective * 0.5 * (fFrontBottomMin1 - fFrontTopMin1));
						R = sqrt(fDistance*fDistance - XPos[fDetectorId]*XPos[fDetectorId]); // cm
						theta = abs(arcLength / R);
						fYPos = abs(R * sin(theta)); // cm
						if(fFrontBottomMin < fFrontTopMin) fYPos = -fYPos;
						//if(fFrontBottomMin > fFrontTopMin) fYPos = fYPos;

						fYDelta = pos.Y()/10. - fYPos;
					} 

					if(f2pmt < 10) {
						fXPos = XPos[fDetectorId];
						fZPos = sqrt(fDistance*fDistance - fYPos*fYPos - XPos[fDetectorId]*XPos[fDetectorId]);
						const TVector3 CalcPos(fXPos, fYPos, fZPos);
						double theta1 = pos.Angle(CalcPos); // Note this is in meters, Calc is in cm, Still works though
						fArcDiff = fDistance*theta1;
						fThetaSim = pos.Theta()*180./TMath::Pi();
						fPhiSim = pos.Phi()*180./TMath::Pi();
						fThetaCalc = CalcPos.Theta()*180./TMath::Pi();
						fPhiCalc = CalcPos.Phi()*180./TMath::Pi();
						fPhiDiff = fPhiSim - fPhiCalc;
						fThetaDiff = fThetaSim - fThetaCalc;
					}

				}
				if (DetConfiguration == 2  && topHit == true) { //Unsegmented
					fTOF = fTopMin;
					fTOF = rand.Gaus(fTOF, TMath::Sqrt(2)*fTimingUncertainty); // Only 1 Sipm, must correct from previous definition to maintain 600ps fwhm with ZDS
					f2pmt = 1; //Doesnt do much but allows for hist functions to remain unchanged with bar conditions
					if(fSystemId == 8710){
						fXPos = bluePosition[fDetectorId][0];
						fYPos = bluePosition[fDetectorId][1];
						fZPos = bluePosition[fDetectorId][2];
						fDistance =bluePosition[fDetectorId][3] ;				
					}
					if(fSystemId == 8720){
						fXPos = whitePosition[fDetectorId-15][0];
						fYPos = whitePosition[fDetectorId-15][1];
						fZPos = whitePosition[fDetectorId-15][2];
						fDistance = whitePosition[fDetectorId-15][3] ;				
					}
					if(fSystemId == 8730){
						fXPos = redPosition[fDetectorId-15-20][0];
						fYPos = redPosition[fDetectorId-15-20][1];
						fZPos = redPosition[fDetectorId-15-20][2];
						fDistance =redPosition[fDetectorId-15-20][3] ;				
					}
					if(fSystemId == 8740){
						fXPos = greenPosition[fDetectorId-15-20-15][0];
						fYPos = greenPosition[fDetectorId-15-20-15][1];
						fZPos = greenPosition[fDetectorId-15-20-15][2];
						fDistance = greenPosition[fDetectorId-15-20-15][3] ;				
					}
					if(fSystemId == 8750){
						fXPos = yellowPosition[fDetectorId-15-20-15-10][0];
						fYPos = yellowPosition[fDetectorId-15-20-15-10][1];
						fZPos = yellowPosition[fDetectorId-15-20-15-10][2];
						fDistance = yellowPosition[fDetectorId-15-20-15-10][3] ;				
					}
					const TVector3 CalcPos(fXPos, fYPos, fZPos);
					double theta1 = pos.Angle(CalcPos); // Note this is in meters, Calc is in cm, Still works though
					fArcDiff = pos.DeltaR(CalcPos);//Radial distance not arc
					fThetaSim = pos.Theta()*180./TMath::Pi();
					fPhiSim = pos.Phi()*180./TMath::Pi();
					fThetaCalc = CalcPos.Theta()*180./TMath::Pi();
					fPhiCalc = CalcPos.Phi()*180./TMath::Pi();
					fPhiDiff = fPhiSim - fPhiCalc;
					fThetaDiff = fThetaSim - fThetaCalc;
					fYDelta = pos.Y()/10. - fYPos;
				}
				if (DetConfiguration == 2  && topHit == false) { //Unsegmented
					f2pmt = 10;
					fTOF = -1;
					fYPos = -150;
					fYDelta = -200;
					fXPos = -200;
					fZPos = -200;
					fC_effective = -1;
					fArcDiff = -1.;
					fThetaSim = -200; 
					fPhiSim = -200;
					fThetaCalc = -200;
					fPhiCalc = -200;
					fPhiDiff = -400;
					fThetaDiff = -400;
				}

				if (DetConfiguration == 3) { //Segmented
					f2pmt = 1; //Doesnt do much but allows for hist functions to remain unchanged with bar conditions
					//What happens if multiple hits, only take earliest?
					bool hit = false;
					//Still have issues with simulation where if detNum is same for differenct systemIDs they stack -> Investigate further.
					if(fSystemId == 8710 && topHit ==true) {
						fTOF = fTopMin;
						fTOF = rand.Gaus(fTOF, TMath::Sqrt(2)*fTimingUncertainty); // Only 1 Sipm, must correct from previous definition to maintain 600ps fwhm with ZDS
						fXPos = bluePositionTop[fDetectorId][0];
						fYPos = bluePositionTop[fDetectorId][1];
						fZPos = bluePositionTop[fDetectorId][2];
						fDistance =bluePositionTop[fDetectorId][3] ;				
						hit = true;
					}
					if(fSystemId == 8710 && bottomHit ==true) {
						fTOF = fBottomMin;
						fTOF = rand.Gaus(fTOF, TMath::Sqrt(2)*fTimingUncertainty); // Only 1 Sipm, must correct from previous definition to maintain 600ps fwhm with ZDS
						fXPos = bluePositionBottom[fDetectorId][0];
						fYPos = bluePositionBottom[fDetectorId][1];
						fZPos = bluePositionBottom[fDetectorId][2];
						fDistance =bluePositionBottom[fDetectorId][3] ;				
						hit = true;
					}
					if(fSystemId == 8710 && frontTopHit ==true) {
						fTOF = fFrontTopMin;
						fTOF = rand.Gaus(fTOF, TMath::Sqrt(2)*fTimingUncertainty); // Only 1 Sipm, must correct from previous definition to maintain 600ps fwhm with ZDS
						fXPos = bluePositionFrontTop[fDetectorId][0];
						fYPos = bluePositionFrontTop[fDetectorId][1];
						fZPos = bluePositionFrontTop[fDetectorId][2];
						fDistance =bluePositionFrontTop[fDetectorId][3] ;				
						hit = true;
					}
					if(fSystemId == 8710 && frontBottomHit ==true) {
						fTOF = fFrontBottomMin;
						fTOF = rand.Gaus(fTOF, TMath::Sqrt(2)*fTimingUncertainty); // Only 1 Sipm, must correct from previous definition to maintain 600ps fwhm with ZDS
						fXPos = bluePositionFrontBottom[fDetectorId][0];
						fYPos = bluePositionFrontBottom[fDetectorId][1];
						fZPos = bluePositionFrontBottom[fDetectorId][2];
						fDistance =bluePositionFrontBottom[fDetectorId][3] ;				
						hit = true;
					}
					if(fSystemId == 8720 && topHit ==true) {
						fTOF = fTopMin;
						fTOF = rand.Gaus(fTOF, TMath::Sqrt(2)*fTimingUncertainty); // Only 1 Sipm, must correct from previous definition to maintain 600ps fwhm with ZDS
						fXPos = whitePositionTop[fDetectorId-15][0];
						fYPos = whitePositionTop[fDetectorId-15][1];
						fZPos = whitePositionTop[fDetectorId-15][2];
						fDistance =whitePositionTop[fDetectorId-15][3] ;				
						hit = true;
					}
					if(fSystemId == 8720 && bottomHit ==true) {
						fTOF = fBottomMin;
						fTOF = rand.Gaus(fTOF, TMath::Sqrt(2)*fTimingUncertainty); // Only 1 Sipm, must correct from previous definition to maintain 600ps fwhm with ZDS
						fXPos = whitePositionBottom[fDetectorId-15][0];
						fYPos = whitePositionBottom[fDetectorId-15][1];
						fZPos = whitePositionBottom[fDetectorId-15][2];
						fDistance =whitePositionBottom[fDetectorId-15][3] ;				
						hit = true;
					}
					if(fSystemId == 8720 && frontTopHit ==true) {
						fTOF = fFrontTopMin;
						fTOF = rand.Gaus(fTOF, TMath::Sqrt(2)*fTimingUncertainty); // Only 1 Sipm, must correct from previous definition to maintain 600ps fwhm with ZDS
						fXPos = whitePositionFrontTop[fDetectorId-15][0];
						fYPos = whitePositionFrontTop[fDetectorId-15][1];
						fZPos = whitePositionFrontTop[fDetectorId-15][2];
						fDistance =whitePositionFrontTop[fDetectorId-15][3] ;				
						hit = true;
					}
					if(fSystemId == 8720 && frontBottomHit ==true) {
						fTOF = fFrontBottomMin;
						fTOF = rand.Gaus(fTOF, TMath::Sqrt(2)*fTimingUncertainty); // Only 1 Sipm, must correct from previous definition to maintain 600ps fwhm with ZDS
						fXPos = whitePositionFrontBottom[fDetectorId-15][0];
						fYPos = whitePositionFrontBottom[fDetectorId-15][1];
						fZPos = whitePositionFrontBottom[fDetectorId-15][2];
						fDistance =whitePositionFrontBottom[fDetectorId-15][3] ;				
						hit = true;
					}
					if(fSystemId == 8730 && topHit ==true) {
						fTOF = fTopMin;
						fTOF = rand.Gaus(fTOF, TMath::Sqrt(2)*fTimingUncertainty); // Only 1 Sipm, must correct from previous definition to maintain 600ps fwhm with ZDS
						fXPos = redPositionTop[fDetectorId-15-20][0];
						fYPos = redPositionTop[fDetectorId-15-20][1];
						fZPos = redPositionTop[fDetectorId-15-20][2];
						fDistance =redPositionTop[fDetectorId-15-20][3] ;				
						hit = true;
					}
					if(fSystemId == 8730 && bottomHit ==true) {
						fTOF = fBottomMin;
						fTOF = rand.Gaus(fTOF, TMath::Sqrt(2)*fTimingUncertainty); // Only 1 Sipm, must correct from previous definition to maintain 600ps fwhm with ZDS
						fXPos = redPositionBottom[fDetectorId-15-20][0];
						fYPos = redPositionBottom[fDetectorId-15-20][1];
						fZPos = redPositionBottom[fDetectorId-15-20][2];
						fDistance =redPositionBottom[fDetectorId-15-20][3] ;				
						hit = true;
					}
					if(fSystemId == 8730 && frontTopHit ==true) {
						fTOF = fFrontTopMin;
						fTOF = rand.Gaus(fTOF, TMath::Sqrt(2)*fTimingUncertainty); // Only 1 Sipm, must correct from previous definition to maintain 600ps fwhm with ZDS
						fXPos = redPositionFrontTop[fDetectorId-15-20][0];
						fYPos = redPositionFrontTop[fDetectorId-15-20][1];
						fZPos = redPositionFrontTop[fDetectorId-15-20][2];
						fDistance =redPositionFrontTop[fDetectorId-15-20][3] ;				
						hit = true;
					}
					if(fSystemId == 8730 && frontBottomHit ==true) {
						fTOF = fFrontBottomMin;
						fTOF = rand.Gaus(fTOF, TMath::Sqrt(2)*fTimingUncertainty); // Only 1 Sipm, must correct from previous definition to maintain 600ps fwhm with ZDS
						fXPos = redPositionFrontBottom[fDetectorId-15-20][0];
						fYPos = redPositionFrontBottom[fDetectorId-15-20][1];
						fZPos = redPositionFrontBottom[fDetectorId-15-20][2];
						fDistance =redPositionFrontBottom[fDetectorId-15-20][3] ;				
						hit = true;
					}
					if(fSystemId == 8740 && topHit ==true) {
						fTOF = fTopMin;
						fTOF = rand.Gaus(fTOF, TMath::Sqrt(2)*fTimingUncertainty); // Only 1 Sipm, must correct from previous definition to maintain 600ps fwhm with ZDS
						fXPos = greenPositionTop[fDetectorId-15-20-15][0];
						fYPos = greenPositionTop[fDetectorId-15-20-15][1];
						fZPos = greenPositionTop[fDetectorId-15-20-15][2];
						fDistance =greenPositionTop[fDetectorId-15-20-15][3] ;				
						hit = true;
					}
					if(fSystemId == 8740 && bottomHit ==true) {
						fTOF = fBottomMin;
						fTOF = rand.Gaus(fTOF, TMath::Sqrt(2)*fTimingUncertainty); // Only 1 Sipm, must correct from previous definition to maintain 600ps fwhm with ZDS
						fXPos = greenPositionBottom[fDetectorId-15-20-15][0];
						fYPos = greenPositionBottom[fDetectorId-15-20-15][1];
						fZPos = greenPositionBottom[fDetectorId-15-20-15][2];
						fDistance =greenPositionBottom[fDetectorId-15-20-15][3] ;				
						hit = true;
					}
					if(fSystemId == 8740 && frontTopHit ==true) {
						fTOF = fFrontTopMin;
						fTOF = rand.Gaus(fTOF, TMath::Sqrt(2)*fTimingUncertainty); // Only 1 Sipm, must correct from previous definition to maintain 600ps fwhm with ZDS
						fXPos = greenPositionFrontTop[fDetectorId-15-20-15][0];
						fYPos = greenPositionFrontTop[fDetectorId-15-20-15][1];
						fZPos = greenPositionFrontTop[fDetectorId-15-20-15][2];
						fDistance =greenPositionFrontTop[fDetectorId-15-20-15][3] ;				
						hit = true;
					}
					if(fSystemId == 8740 && frontBottomHit ==true) {
						fTOF = fFrontBottomMin;
						fTOF = rand.Gaus(fTOF, TMath::Sqrt(2)*fTimingUncertainty); // Only 1 Sipm, must correct from previous definition to maintain 600ps fwhm with ZDS
						fXPos = greenPositionFrontBottom[fDetectorId-15-20-15][0];
						fYPos = greenPositionFrontBottom[fDetectorId-15-20-15][1];
						fZPos = greenPositionFrontBottom[fDetectorId-15-20-15][2];
						fDistance =greenPositionFrontBottom[fDetectorId-15-20-15][3] ;				
						hit = true;
					}
					if(fSystemId == 8750 && topHit ==true) {
						fTOF = fTopMin;
						fTOF = rand.Gaus(fTOF, TMath::Sqrt(2)*fTimingUncertainty); // Only 1 Sipm, must correct from previous definition to maintain 600ps fwhm with ZDS
						fXPos = yellowPositionTop[fDetectorId-15-20-15-10][0];
						fYPos = yellowPositionTop[fDetectorId-15-20-15-10][1];
						fZPos = yellowPositionTop[fDetectorId-15-20-15-10][2];
						fDistance =yellowPositionTop[fDetectorId-15-20-15-10][3] ;				
						hit = true;
					}
					if(fSystemId == 8750 && bottomHit ==true) {
						fTOF = fBottomMin;
						fTOF = rand.Gaus(fTOF, TMath::Sqrt(2)*fTimingUncertainty); // Only 1 Sipm, must correct from previous definition to maintain 600ps fwhm with ZDS
						fXPos = yellowPositionBottom[fDetectorId-15-20-15-10][0];
						fYPos = yellowPositionBottom[fDetectorId-15-20-15-10][1];
						fZPos = yellowPositionBottom[fDetectorId-15-20-15-10][2];
						fDistance =yellowPositionBottom[fDetectorId-15-20-15-10][3] ;				
						hit = true;
					}
					if(fSystemId == 8750 && frontTopHit ==true) {
						fTOF = fFrontTopMin;
						fTOF = rand.Gaus(fTOF, TMath::Sqrt(2)*fTimingUncertainty); // Only 1 Sipm, must correct from previous definition to maintain 600ps fwhm with ZDS
						fXPos = yellowPositionFrontTop[fDetectorId-15-20-15-10][0];
						fYPos = yellowPositionFrontTop[fDetectorId-15-20-15-10][1];
						fZPos = yellowPositionFrontTop[fDetectorId-15-20-15-10][2];
						fDistance =yellowPositionFrontTop[fDetectorId-15-20-15-10][3] ;				
						hit = true;
					}
					if(fSystemId == 8750 && frontBottomHit ==true) {
						fTOF = fFrontBottomMin;
						fTOF = rand.Gaus(fTOF, TMath::Sqrt(2)*fTimingUncertainty); // Only 1 Sipm, must correct from previous definition to maintain 600ps fwhm with ZDS
						fXPos = yellowPositionFrontBottom[fDetectorId-15-20-15-10][0];
						fYPos = yellowPositionFrontBottom[fDetectorId-15-20-15-10][1];
						fZPos = yellowPositionFrontBottom[fDetectorId-15-20-15-10][2];
						fDistance =yellowPositionFrontBottom[fDetectorId-15-20-15-10][3] ;				
						hit = true;
					}

					const TVector3 CalcPos(fXPos, fYPos, fZPos);
					double theta1 = pos.Angle(CalcPos); // Note this is in meters, Calc is in cm, Still works though
					fArcDiff = pos.DeltaR(CalcPos);//Radial distance not arc
					fThetaSim = pos.Theta()*180./TMath::Pi();
					fPhiSim = pos.Phi()*180./TMath::Pi();
					fThetaCalc = CalcPos.Theta()*180./TMath::Pi();
					fPhiCalc = CalcPos.Phi()*180./TMath::Pi();
					fPhiDiff = fPhiSim - fPhiCalc;
					fThetaDiff = fThetaSim - fThetaCalc;
					fYDelta = pos.Y()/10. - fYPos;
					if(hit==false) {
					f2pmt = 10;
					fTOF = -1;
					fYPos = -150;
					fYDelta = -200;
					fXPos = -200;
					fZPos = -200;
					fC_effective = -1;
					fArcDiff = -1.;
					fThetaSim = -200; 
					fPhiSim = -200;
					fThetaCalc = -200;
					fPhiCalc = -200;
					fPhiDiff = -400;
					fThetaDiff = -400;

					}
				}

				//std::cout << "fTOF1: " << fTOF << std::endl;
				/*	if (fTOF>0) {
					fTOF = rand.Gaus(fTOF, fTimingUncertainty);
					}
					*/	//	std::cout << "fEvent: " << fEventNumber << " and detNum: " << fDetectorId << " and 2PMTS: " << f2pmt << std::endl;
				//	std::cout << "fTOF: " << fTOF << std::endl;
			}
		~DetectorDaemon(){}

		void AddEnergy(double simEnergy, double energy) {
			fSimulationEnergy += simEnergy;
			fEnergy += energy;
		}
		void Set(int evNumber, int detNumber, int cryNumber, double simEnergy, double energy, TVector3 pos, double time, double tof, double Etof, double distance, double dY, double arc, double dtheta, double dphi) {
			fEventNumber = evNumber;
			fDetectorId = detNumber;
			fCrystalId = cryNumber;
			fSimulationEnergy = simEnergy;
			fEnergy = energy;
			fPosition = pos;
			fTime = time;
			fEnergyTOF = Etof;
			fTOF = tof;
			fDistance = distance;
			fArcDiff = arc;
			fPhiDiff = dphi;
			fThetaDiff = dtheta;
			fYDelta = dY;
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
			fCollectedTop1 = 0.;
			fCollectedTop2 = 0.;
			fCollectedTop3 = 0.;
			fCollectedBottom1 = 0.;
			fCollectedBottom2 = 0.;
			fCollectedBottom3 = 0.;
			fCollectedFrontTop1 = 0.;
			fCollectedFrontTop2 = 0.;
			fCollectedFrontBottom1 = 0.;
			fCollectedFrontBottom2 = 0.;
			fCollectedFrontMid1 = 0.;
			fCollectedFrontMid2 = 0.;
			fCFDTimeTop1 = -1;
			fCFDTimeTop2 = -1;
			fCFDTimeTop3 = -1;
			fCFDTimeBottom1 = -1;
			fCFDTimeBottom2 = -1;
			fCFDTimeBottom3 = -1;
			fCFDTimeFrontTop1 = -1;
			fCFDTimeFrontTop2 = -1;
			fCFDTimeFrontMid1 = -1;
			fCFDTimeFrontMid2 = -1;
			fCFDTimeFrontBottom1 = -1;
			fCFDTimeFrontBottom2 = -1;
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
		double particleType() {
			return fParticleType;
		}
		double processType() {
			return fProcessType;
		}

		int CollectedTop1() {
			return fCollectedTop1;
		}
		int CollectedTop2() {
			return fCollectedTop2;
		}
		int CollectedTop3() {
			return fCollectedTop3;
		}
		int CollectedBottom1() {
			return fCollectedBottom1;
		}
		int CollectedBottom2() {
			return fCollectedBottom2;
		}
		int CollectedBottom3() {
			return fCollectedBottom3;
		}
		int CollectedFrontTop1() {
			return fCollectedFrontTop1;
		}
		int CollectedFrontTop2() {
			return fCollectedFrontTop2;
		}
		int CollectedFrontMid1() {
			return fCollectedFrontMid1;
		}
		int CollectedFrontMid2() {
			return fCollectedFrontMid2;
		}
		int CollectedFrontBottom1() {
			return fCollectedFrontBottom1;
		}
		int CollectedFrontBottom2() {
			return fCollectedFrontBottom2;
		}
		double TOF() {
			return fTOF;
		}
		double EnergyTOF(double fTOFCorrected) {
			if (fTOFCorrected>0) {
				double velocity = (fDistance/100.)/(fTOFCorrected*1.e-9);
				double vel2 = velocity*velocity;
				fEnergyTOF = 0.5 * fMass * vel2 * fConversion2;
			}else fEnergyTOF = -1.;

			return fEnergyTOF;
		}
		int PMT() {
			return f2pmt;
		}
		double PulseHeight() {
			int top = fCollectedTop1+fCollectedTop2+fCollectedTop3;
			int bottom = fCollectedBottom1+fCollectedBottom2+fCollectedBottom3;
			int frontTop = fCollectedFrontTop1+fCollectedFrontTop2;
			int frontMid = fCollectedFrontMid1+fCollectedFrontMid2;
			int frontBottom = fCollectedFrontBottom1+fCollectedFrontBottom2;
			return top+bottom+frontTop+frontMid+frontBottom;
		}
		double YPosition() {
			return fYPos;
		}
		double DeltaPhi() {
			return fPhiDiff;
		}
		double DeltaTheta() {
			return fThetaDiff;
		}
		double Arc() {
			return fArcDiff;
		}
		double DeltaY() {
			return fYDelta;
		}
		std::vector<double> GetRand() {
			std::vector<double> Num(2, -10);
			if (f2pmt ==1){
			Num[0] = fRand11;
			Num[1] = fRand12;
			}
			if (f2pmt ==2){
			Num[0] = fRand21;
			Num[1] = fRand22;
			}
			if (f2pmt ==3){
			Num[0] = fRand31;
			Num[1] = fRand32;
			}
			if (f2pmt ==4){
			Num[0] = fRand41;
			Num[1] = fRand42;
			}
			if (f2pmt ==5){
			Num[0] = fRand51;
			Num[1] = fRand52;
			}
			if (f2pmt ==6){
			Num[0] = fRand61;
			Num[1] = fRand62;
			}
			if (f2pmt ==7){
			Num[0] = fRand71;
			Num[1] = fRand72;
			}
			if (f2pmt ==8){
			Num[0] = fRand81;
			Num[1] = fRand82;
			}
			return Num;
		}

	private:
		int fEventNumber;
		int fDetectorId;
		int fCrystalId;
		double fSimulationEnergy;
		double fEnergy;
		TVector3 fPosition;
		double fTime;
		double fTOF;
		double fEnergyTOF;
		int fParticleType;
		int fProcessType;
		int f2pmt;
		double fMaxTDiff;
		double fXPos;
		double fYPos;
		double fYDelta;
		double fZPos;
		double fArcDiff;
		double fThetaDiff;
		double fThetaSim;
		double fThetaCalc;
		double fPhiSim;
		double fPhiCalc;
		double fPhiDiff;
		double fThickness = 1.5;
		double fDistance;
		//double fTimingUncertaintyFWHM = 0.6; // 600 ps // For zds and SiPM combined
		double fTimingUncertaintyFWHM = 0.4; // 400 ps //For SiPM only
		double fTimingUncertainty;
		double fMass = 1008664.91595e-6; // u //Allison
		double c = 299792458.; // m/s
		double fConversion1 = 9.3149410242e5; // keV/u // Allison
		double fConversion2;
		double fC_effective;
		double fRand11;
		double fRand12;
		double fRand21;
		double fRand22;
		double fRand31;
		double fRand32;
		double fRand41;
		double fRand42;
		double fRand51;
		double fRand52;
		double fRand61;
		double fRand62;
		double fRand71;
		double fRand72;
		double fRand81;
		double fRand82;

		int fThreshold = 1;

		double fBeamlineXY = 6.5;
		double fPMTSize = 2.2;

		int  fCollectedTop1;
		int  fCollectedTop2;
		int  fCollectedTop3;
		int  fCollectedBottom1;
		int  fCollectedBottom2;
		int  fCollectedBottom3;
		int  fCollectedFrontTop1;
		int  fCollectedFrontTop2;
		int  fCollectedFrontMid1;
		int  fCollectedFrontMid2;
		int  fCollectedFrontBottom1;
		int  fCollectedFrontBottom2;
		double  fCFDTimeTop1;
		double  fCFDTimeTop2;
		double  fCFDTimeTop3;
		double  fCFDTimeBottom1;
		double  fCFDTimeBottom2;
		double  fCFDTimeBottom3;
		double  fCFDTimeFrontTop1;
		double  fCFDTimeFrontTop2;
		double  fCFDTimeFrontMid1;
		double  fCFDTimeFrontMid2;
		double  fCFDTimeFrontBottom1;
		double  fCFDTimeFrontBottom2;

		int fSystemId;

		bool topHit;
		bool bottomHit;
		bool frontTopHit;
		bool frontMidHit;
		bool frontBottomHit;

		double fTopMin;
		double fBottomMin;
		double fFrontTopMin;
		double fFrontMidMin;
		double fFrontBottomMin;
		double fTopMin1;
		double fBottomMin1;
		double fFrontTopMin1;
		double fFrontMidMin1;
		double fFrontBottomMin1;

		//REVIST
		double  topCFD[3] = {DBL_MAX, DBL_MAX, DBL_MAX};
		double  bottomCFD[3] = {DBL_MAX, DBL_MAX, DBL_MAX};
		double  frontTopCFD[2] = {DBL_MAX, DBL_MAX};
		double  frontMidCFD[2] = {DBL_MAX, DBL_MAX};
		double  frontBottomCFD[2] = {DBL_MAX, DBL_MAX};
		int detNum = 17;


		// BARS ////////////////////////////////////////////
		double MaxDeltaTMid[18] = {
			0.*2.,
			0.859164*2., 
			1.038666*2., 
			1.160220*2., 
			1.241251*2., 
			0.*2., 
			0.*2., 
			0.*2., 
			0.*2., 
			1.242036*2.,
			1.159888*2.,
			1.038523*2.,
			0.857048*2.,
			0.*2.,
			0.*2.,
			0.*2.,
			0.*2.,
			0.*2.
		};

		double MaxDeltaTTop[18] = {
			0.725331*2.,
			0.753469*2.,
			0.906666*2.,
			1.024646*2.,
			1.106288*2.,
			0.776535*2.,
			0.806076*2.,
			0.806619*2.,
			0.777500*2.,
			1.107092*2.,
			1.023034*2.,
			0.906251*2.,
			0.751052*2.,
			0.725358*2.,
			0.832477*2.,
			0.861897*2.,
			0.857937*2.,
			0.830120*2.
		};

		double MaxDeltaTBot[18] = {
			0.725331*2.,
			0.753469*2.,
			0.906666*2.,
			1.024646*2.,
			1.106288*2.,
			0.832242*2.,
			0.860514*2.,
			0.862236*2.,
			0.834923*2.,
			1.107092*2.,
			1.023034*2.,
			0.906251*2.,
			0.751052*2.,
			0.725358*2.,
			0.776137*2.,
			0.805877*2.,
			0.806533*2.,
			0.776236*2.
		};

		double XPos[18] = {
			37.142857,               
			31.428571,               
			25.714286,               
			20.000000,               
			14.285714,               
			8.571429,               
			2.857143,                
			-2.857143,               
			-8.571429,               
			-14.285714,              
			-20.000000,              
			-25.714286,              
			-31.428571,              
			-37.142857,              
			-8.571429,              
			-2.857143,               
			2.857143,                
			8.571429  
		};

		double YPos[18] = {
			18.002282,               
			27.349598,               
			33.265790,               
			37.415490,               
			40.347477,               
			42.315633,              
			43.451128,               
			43.451128,               
			42.315633,               
			40.347477,              
			37.415490,              
			33.265790,              
			27.349598,              
			18.002282,              
			42.315633,              
			43.451128,               
			43.451128,               
			42.315633
		};
		double frontPMT[18] = {
			6.354216,               
			10.138488,               
			12.713519,               
			14.604670,               
			15.994697,               
			16.971523,              
			17.581194,               
			17.581194,               
			16.971523,               
			15.994697,              
			14.604670,              
			12.713519,              
			10.138488,              
			6.354216,              
			16.971523,              
			17.581194,               
			17.581194,               
			16.971523
		};

		double midPMT[18] = {
			0.000000,               
			0.000000,               
			0.000000,               
			0.000000,               
			0.000000,               
			28.384188,              
			29.211472,               
			29.211472,               
			28.384188,               
			0.000000,              
			0.000000,              
			0.000000,              
			0.000000,              
			0.000000,              
			28.384188,              
			29.211472,               
			29.211472,               
			28.384188
		};

		double ArcLength[18] = {
			58.243810,	
			79.451057,
			90.118546,
			96.760423,
			101.29336,
			43.377136,
			44.657186,
			44.657186,
			43.377136,
			101.29336,
			96.760423,
			90.118546,
			79.451057,
			58.243810,
			43.377136,
			44.657186,
			44.657186,
			43.377136
		};
		double ArcLength_FrontTopBot_Outside[18] = {
			19.368871,	
			26.385176,
			29.908585,
			32.099732,
			33.592391,
			34.651824,
			35.407642,
			35.407642,
			34.651824,
			33.592391,
			32.099732,
			29.908585,
			26.385176,
			19.368871,
			34.651824,
			35.407642,
			35.407642,
			34.651824
		};
		double ArcLength_FrontTop_FrontBot[18] = {
			19.506067,	
			26.680705,
			30.301376,
			32.560959,
			34.108580,
			35.217220,
			36.020953,
			36.020953,
			35.217220,
			34.108580,
			32.560959,
			30.301376,
			26.680705,
			19.506067,
			35.217220,
			36.020953,
			36.020953,
			35.217220
		};
		double ArcLength_FrontMid_Outside[18] = {
			29.121905,	
			39.725529,
			45.059273,
			48.380212,
			50.646682,
			21.463302,
			22.081004,
			22.081004,
			21.463302,
			50.646682,
			48.380212,
			45.059273,
			39.725529,
			29.121905,
			21.463302,
			22.081004,
			22.081004,
			21.463302
		};
		double ArcLength_FrontMid_Inside[18] = {
			13.432528,	
			11.409812,
			10.279319,
			9.582730,
			9.144248,
			21.913834,
			22.576181,
			22.576181,
			21.913834,
			9.144248,
			9.582730,
			10.279319,
			11.409812,
			13.432528,
			21.913834,
			22.576181,
			22.576181,
			21.913834
		};

		double MaxDeltaT[18];
		//////////////////////////////////////////////
		// Tiles ////////////////////////////////////////////
		// Unsegmented ////////////////////////////////////////////
		double bluePosition[15][4] = { //x, y, z, R, based off mean scattering positions
			{-25.306397,			10.705084	,		40.897697,			49.271028},
			{-17.839331,			20.753911	,		40.963672,			49.264480},
			{-28.609760,			20.832270	,		34.275037,			49.267433},
			{2.313331,			27.336322	,		40.926051,			49.270353},
			{14.272579,			23.356495	,		40.966427,			49.269468},
			{10.949800,			33.647801	,		34.305185,			49.284058},
			{26.679173,			6.344734	,		40.933577,			49.270596},
			{26.650509,			-6.384069	,		40.949472,			49.273372},
			{35.347654,			0.076764	,		34.332092,			49.276314},
			{14.400733,			-23.266632	,		40.984961,			49.279654},
			{2.230552,			-27.262221	,		40.971890,			49.263575},
			{10.889463,			-33.588454	,		34.367255,			49.273450},
			{-17.887167,			-20.853218	,		40.927930,			49.294045},
			{-25.332621,			-10.518153	,		40.936247,			49.276257},
			{-28.718175,			-20.754158	,		34.238207,			49.271934}
		};

		double whitePosition[20][4] = { //x, y, z, R, based off mean scattering positions
			{-9.999466	,		0.011696	,		48.240748,			49.266208},
			{-20.845746	,		0.095279	,		44.647155,			49.273955},
			{-30.652418	,		-0.029834	,		38.555110,			49.255133},
			{-38.726360	,		0.108957	,		30.451488,			49.264956},
			{-3.007650	,		9.489043	,		48.240152,			49.256473},
			{-6.483167	,		19.736629	,		44.664848,			49.259665},
			{-9.448336	,		29.125867	,		38.608701,			49.276962},
			{-12.059788	,		36.834106	,		30.435116,			49.279673},
			{8.057425	,		5.914380	,		48.241980,			49.266526},
			{16.995364	,		12.250574	,		44.584453,			49.261470},
			{24.925574	,		17.947506	,		38.512568,			49.260685},
			{31.258048	,		22.774452	,		30.518943,			49.266085},
			{7.959441	,		-5.786081	,		48.289115,			49.281539},
			{16.794295	,		-12.158146	,		44.674170,			49.250891},
			{24.814162	,		-18.132232	,		38.514004,			49.273207},
			{31.325542	,		-22.813309	,		30.431366,			49.272758},
			{-3.127200	,		-9.480106	,		48.241614,			49.263629},
			{-6.419905	,		-19.823295	,		44.656036,			49.278188},
			{-9.514682	,		-29.152606	,		38.569834,			49.275103},
			{-12.041491	,		-36.787086	,		30.504756,			49.283134}
		};

		double redPosition[15][4] = { //x, y, z, R, based off mean scattering positions
			{-14.462591	,		10.473543	,		45.930874,			49.279883},
			{-34.597365	,		10.370102	,		33.522677,			49.277648},
			{-20.686286	,		29.637863	,		33.481148,			49.267764},
			{5.551847	,		16.979911	,		45.926688,			49.278810},
			{-0.691201	,		36.136936	,		33.492072,			49.275499},
			{21.862120	,		28.803318	,		33.478047,			49.278423},
			{17.974466	,		0.036997	,		45.862773,			49.259280},
			{34.159946	,		11.708158	,		33.540883,			49.284619},
			{34.071991	,		-11.900909	,		33.555157,			49.279618},
			{5.466565	,		-17.093422	,		45.901238,			49.284805},
			{21.779700	,		-28.820582	,		33.505564,			49.270722},
			{-0.647193	,		-36.127909	,		33.501121,			49.274434},
			{-14.440975	,		-10.783139	,		45.861549,			49.275749},
			{-20.780955	,		-29.689400	,		33.375298,			49.266815},
			{-34.569900	,		-10.604225	,		33.486394,			49.283528}
		};

		double greenPosition[10][4] = { //x, y, z, R, based off mean scattering positions
			{-41.515253	,		9.318995	,		24.856374	,		49.276762},
			{-36.745919	,		19.651235	,		26.282580	,		49.266699},
			{-3.675098	,		42.324892	,		24.926049	,		49.256580},
			{7.427243	,		41.080256	,		26.154961	,		49.262900},
			{39.061018	,		16.774935	,		24.953358	,		49.293322},
			{41.351589	,		5.662649	,		26.223007	,		49.291638},
			{27.919065	,		-32.050752	,		24.890472	,		49.257086},
			{18.132764	,		-37.555012	,		26.267427	,		49.286446},
			{-21.680607	,		-36.579689	,		24.873171	,		49.262531},
			{-30.024499	,		-28.791574	,		26.406303	,		49.271880}
		};

		double yellowPosition[10][4] = { //x, y, z, R, based off mean scattering positions
			{-30.025117	,		28.881809	,		26.316442	,		49.276989},
			{-21.588226	,		36.650629	,		24.869142	,		49.272653},
			{18.236872	,		37.500279	,		26.243441	,		49.270403},
			{28.044520	,		31.986827	,		24.871575	,		49.277251},
			{41.244715	,		-5.801289	,		26.323088	,		49.271558},
			{39.019300	,		-16.808337	,		24.942364	,		49.266089},
			{7.322973	,		-40.987496	,		26.374631	,		49.287137},
			{-4.014799	,		-42.286798	,		24.974515	,		49.274925},
			{-36.776004	,		-19.669148	,		26.258896	,		49.283664},
			{-41.525387	,		-9.383524	,		24.784104	,		49.261142}
		};
		//////////////////////////////////////////////
		// Segmented ////////////////////////////////////////////
		double bluePositionTop[15][4] = { //x, y, z, R, based off mean scattering positions
			{-22.779512	,		13.381858	,		41.810807	,		49.458304},
			{-21.200192	,		21.867553	,		38.967412	,		49.458035},
			{-28.718831	,		17.530611	,		36.276426	,		49.478002},
			{5.713206	,		25.589810	,		41.997256	,		49.510086},
			{14.337785	,		26.818976	,		39.015080	,		49.467221},
			{7.645939	,		32.662610	,		36.406445	,		49.504905},
			{26.137443	,		2.603773	,		41.921302	,		49.470608},
			{29.992698	,		-5.181648	,		39.008612	,		49.478108},
			{33.354819	,		2.707240	,		36.431688	,		49.468586},
			{10.507985	,		-24.232398	,		41.868345	,		49.503386},
			{4.082751	,		-30.231711	,		38.984144	,		49.501401},
			{12.995235	,		-30.976788	,		36.337678	,		49.486002},
			{-19.742340	,		-17.385687	,		41.893807	,		49.468305},
			{-27.436745	,		-13.152034	,		38.976240	,		49.445912},
			{-25.529472	,		-21.902265	,		36.339706	,		49.518051}
		};
		double bluePositionBottom[15][4] = { //x, y, z, R, based off mean scattering positions
			{-27.295523	,		13.587598	,		38.989982	,		49.496334},
			{-19.713367	,		17.412230	,		41.951818	,		49.515226},
			{-25.479215	,		21.804323	,		36.399013	,		49.492495},
			{4.121699	,		30.205315	,		39.016030	,		49.513635},
			{10.516396	,		24.191805	,		41.875273	,		49.491176},
			{13.002088	,		30.946725	,		36.351516	,		49.479155},
			{29.819946	,		5.401397	,		39.057389	,		49.435654},
			{26.047445	,		-2.596402	,		41.982663	,		49.474788},
			{33.369893	,		-2.690871	,		36.436839	,		49.481651},
			{14.345858	,		-26.865624	,		38.941273	,		49.436708},
			{5.671966	,		-25.689863	,		41.886466	,		49.463282},
			{7.977142	,		-32.595912	,		36.359844	,		49.478950},
			{-21.090724	,		-21.949655	,		38.997502	,		49.471317},
			{-22.694731	,		-13.367763	,		41.823954	,		49.426623},
			{-28.698814	,		-17.489749	,		36.409970	,		49.549967}
		};
		double bluePositionFrontTop[15][4] = { //x, y, z, R, based off mean scattering positions
			{-23.289321	,		7.856760	,		42.934417	,		49.472067},
			{-16.021409	,		24.139566	,		40.089287	,		49.462664},
			{-31.818502	,		19.943745	,		32.147797	,		49.433297},
			{0.052457	,		24.486616	,		42.969173	,		49.456516},
			{17.936883	,		22.705200	,		40.074991	,		49.429372},
			{9.166819	,		36.437140	,		32.159406	,		49.456275},
			{23.320264	,		7.475343	,		42.950733	,		49.441692},
			{27.250488	,		-10.170389	,		40.040454	,		49.490038},
			{37.467518	,		2.695141	,		32.264442	,		49.518410},
			{14.415874	,		-19.873816	,		42.942169	,		49.465300},
			{-1.361962	,		-29.043013	,		40.079859	,		49.515115},
			{14.063865	,		-34.849275	,		32.162066	,		49.463752},
			{-14.569485	,		-19.699241	,		42.978711	,		49.472211},
			{-27.908545	,		-7.602950	,		40.149857	,		49.484369},
			{-28.642626	,		-24.214003	,		32.186503	,		49.423566}
		};
		double bluePositionFrontBottom[15][4] = { //x, y, z, R, based off mean scattering positions
			{-28.048611	,		7.738100	,		40.014722	,		49.475052},
			{-14.517876	,		19.854412	,		42.902622	,		49.453022},
			{-28.819241	,		24.215370	,		32.115314	,		49.480563},
			{-1.467203	,		28.923138	,		40.056066	,		49.428626},
			{14.394444	,		19.894069	,		42.983014	,		49.502661},
			{14.068155	,		34.688549	,		32.339879	,		49.467931},
			{27.161608	,		10.295849	,		40.079513	,		49.498736},
			{23.409594	,		-7.590190	,		42.928420	,		49.482010},
			{37.392592	,		-2.852369	,		32.219369	,		49.441174},
			{18.074808	,		-22.682078	,		40.040138	,		49.440753},
			{0.061858	,		-24.538719	,		42.980572	,		49.492243},
			{9.064788	,		-36.441560	,		32.194436	,		49.463516},
			{-16.073265	,		-24.101888	,		40.035655	,		49.417654},
			{-23.482080	,		-7.646772	,		42.855214	,		49.461607},
			{-31.874761	,		-19.692071	,		32.261348	,		49.442619}
		};

		double whitePositionTop[20][4] = { //x, y, z, R, based off mean scattering positions
			{-12.499866	,		-2.480396	,		47.796532,			49.466226},
			{-23.124360	,		-2.831592	,		43.707178,			49.528491},
			{-28.805345	,		2.676749	,		40.136840,			49.476043},
			{-37.292677	,		2.709621	,		32.440178,			49.502030},
			{-6.312112	,		10.902631	,		47.830293,			49.461571},
			{-9.695625	,		21.202334	,		43.633519,			49.471488},
			{-6.330162	,		28.158530	,		40.112003,			49.416056},
			{-9.091595	,		36.206371	,		32.534903,			49.518464},
			{8.380541	,		9.295543	,		47.852036,			49.461682},
			{17.047352	,		15.841430	,		43.608582,			49.429460},
			{24.821196	,		14.605386	,		40.232855,			49.478194},
			{31.620389	,		19.767487	,		32.494833,			49.462276},
			{11.546003	,		-5.046787	,		47.813464,			49.446007},
			{20.177281	,		-11.507421	,		43.661749,			49.455957},
			{21.613098	,		-19.296356	,		40.158127,			49.519194},
			{28.652554	,		-24.116769	,		32.288212,			49.448114},
			{-1.314185	,		-12.573483	,		47.821691,			49.464469},
			{-4.582384	,		-22.761019	,		43.692703,			49.478425},
			{-11.426006	,		-26.484699	,		40.173781,			49.456300},
			{-14.065424	,		-34.641901	,		32.364177,			49.450353}
		};
		double whitePositionBottom[20][4] = { //x, y, z, R, based off mean scattering positions
			{-7.296537	,		-2.623379	,		48.826135,			49.437971},
			{-18.308645	,		-2.669749	,		45.852016,			49.444326},
			{-32.820645	,		2.739750	,		36.909900,			49.467582},
			{-40.392557	,		2.633839	,		28.440340,			49.470685},
			{-4.958790	,		6.293754	,		48.770540,			49.424351},
			{-8.192517	,		16.629238	,		45.814829,			49.423147},
			{-7.597977	,		31.827096	,		37.003856,			49.396140},
			{-9.970149	,		39.326743	,		28.309578,			49.471495},
			{4.288248	,		6.455795	,		48.827695,			49.438954},
			{13.431284	,		12.926389	,		45.828445,			49.474613},
			{28.099841	,		17.342342	,		36.874790,			49.498566},
			{34.225945	,		21.630767	,		28.381668,			49.445166},
			{7.511880	,		-2.214446	,		48.838900,			49.462817},
			{16.364732	,		-8.630178	,		45.837047,			49.429944},
			{24.881206	,		-21.281217	,		37.028234,			49.427267},
			{30.958644	,		-25.994259	,		28.456787,			49.436099},
			{0.342207	,		-7.801610	,		48.783865,			49.404936},
			{-3.025583	,		-18.387497	,		45.825197,			49.469212},
			{-12.674552	,		-30.287260	,		37.002749,			49.468837},
			{-15.016365	,		-37.639730	,		28.382477,			49.475302}
		};
		double whitePositionFrontTop[20][4] = { //x, y, z, R, based off mean scattering positions
			{-12.409191	,		2.702027	,		47.804330,			49.462541},
			{-22.871466	,		2.747913	,		43.807769,			49.495208},
			{-28.728446	,		-2.713807	,		40.190460,			49.476877},
			{-37.395547	,		-2.719590	,		32.225686,			49.440044},
			{-1.223134	,		12.589155	,		47.814599,			49.459264},
			{-4.422956	,		22.694747	,		43.753825,			49.487486},
			{-11.481737	,		26.597376	,		40.137127,			49.499896},
			{-14.223367	,		34.640119	,		32.301686,			49.453422},
			{11.578607	,		5.130691	,		47.850820,			49.498375},
			{20.197180	,		11.311752	,		43.750436,			49.497297},
			{21.724032	,		19.192154	,		40.080476,			49.464299},
			{28.571862	,		24.193445	,		32.408157,			49.517297},
			{8.365921	,		-9.405535	,		47.873906,			49.501148},
			{17.107335	,		-15.731186	,		43.658267,			49.458825},
			{25.067482	,		-14.638347	,		40.097303,			49.502056},
			{31.676869	,		-19.637518	,		32.481739,			49.438037},
			{-6.392443	,		-11.033806	,		47.782409,			49.454694},
			{-9.736155	,		-21.076860	,		43.671029,			49.458928},
			{-6.270751	,		-28.175987	,		40.149679,			49.449017},
			{-9.032716	,		-36.265546	,		32.496062,			49.525487}
		};
		double whitePositionFrontBottom[20][4] = { //x, y, z, R, based off mean scattering positions
			{-7.454698	,		2.640586	,		48.779344,			49.416289},
			{-18.343513	,		2.590871	,		45.813075,			49.416950},
			{-32.699850	,		-2.741206	,		36.997351,			49.452991},
			{-40.427781	,		-2.586669	,		28.377542,			49.460906},
			{0.397515	,		7.814401	,		48.834361,			49.457231},
			{-3.119551	,		18.288350	,		45.815211,			49.429029},
			{-12.798464	,		30.281725	,		36.924876,			49.439154},
			{-14.988955	,		37.631758	,		28.352466,			49.443709},
			{7.646607	,		2.044547	,		48.822517,			49.459973},
			{16.488379	,		8.718878	,		45.788695,			49.441785},
			{25.010098	,		21.405348	,		36.888976,			49.441789},
			{31.149959	,		25.875205	,		28.334435,			49.423541},
			{4.431107	,		-6.671915	,		48.821682,			49.474294},
			{13.353541	,		-13.084727	,		45.804078,			49.472626},
			{28.146798	,		-16.897242	,		37.013043,			49.474482},
			{34.190444	,		-21.648773	,		28.398136,			49.437941},
			{-4.986598	,		-6.232824	,		48.808965,			49.457349},
			{-8.180495	,		-16.615446	,		45.879877,			49.476829},
			{-7.502180	,		-31.990622	,		36.969673,			49.461493},
			{-9.990442	,		-39.148259	,		28.465576,			49.423518}
		};

		double redPositionTop[15][4] = { //x, y, z, R, based off mean scattering positions
			{-14.005403	,		6.720917	,		46.932684,			49.436817},
			{-37.269521	,		11.188804	,		30.497672,			49.440010},
			{-17.176673	,		31.935179	,		33.575499,			49.418700},
			{1.847542	,		15.290505	,		46.997600,			49.456924},
			{-0.858390	,		38.982089	,		30.394188,			49.438313},
			{25.232067	,		26.308412	,		33.429806,			49.460507},
			{15.143330	,		2.883720	,		46.969000,			49.434029},
			{36.917839	,		12.732573	,		30.335230,			49.449686},
			{32.764827	,		-15.778365	,		33.465103,			49.420682},
			{7.424233	,		-13.509273	,		47.008717,			49.471599},
			{23.605407	,		-31.039915	,		30.381043,			49.433787},
			{-4.963474	,		-35.971860	,		33.589938,			49.466096},
			{-10.609382	,		-11.437977	,		46.908594,			49.434831},
			{-22.195644	,		-32.032684	,		30.440331,			49.450513},
			{-35.719177	,		-6.667587	,		33.460299,			49.395424}
		};
		double redPositionBottom[15][4] = { //x, y, z, R, based off mean scattering positions
			{-10.475839	,		11.425865	,		46.983140,			49.474327},
			{-35.796722	,		6.434065	,		33.535648,			49.471630},
			{-22.144804	,		31.933036	,		30.570869,			49.443798},
			{7.321392	,		13.470638	,		46.993515,			49.431279},
			{-4.805944	,		36.180793	,		33.412745,			49.482911},
			{23.395350	,		31.153185	,		30.422152,			49.430463},
			{15.235472	,		-2.937221	,		46.978744,			49.474734},
			{32.867435	,		15.732773	,		33.434217,			49.453365},
			{36.693085	,		-12.893230	,		30.472202,			49.408228},
			{1.929280	,		-15.229011	,		47.012918,			49.455630},
			{25.104581	,		-26.221168	,		33.604533,			49.467710},
			{-0.570173	,		-38.869851	,		30.583344,			49.462424},
			{-14.025119	,		-6.375498	,		46.982327,			49.443806},
			{-17.414297	,		-32.088269	,		33.357443,			49.453349},
			{-37.242557	,		-11.122927	,		30.596746,			49.466033}
		};
		double redPositionFrontTop[15][4] = { //x, y, z, R, based off mean scattering positions
			{-17.806875	,		9.337391	,		45.206648,			49.476385},
			{-33.974310	,		14.102090	,		33.108139,			49.490116},
			{-19.005682	,		27.901342	,		36.091673,			49.419730},
			{3.337237	,		19.982032	,		45.183606,			49.517442},
			{2.988355	,		36.597187	,		33.189089,			49.495454},
			{20.719932	,		26.695051	,		36.205209,			49.525332},
			{19.909280	,		2.887549	,		45.221209,			49.494193},
			{35.833714	,		8.517559	,		33.080566,			49.506845},
			{31.809435	,		-11.343799	,		36.179190,			49.491976},
			{8.879478	,		-18.097426	,		45.186322,			49.478941},
			{19.212698	,		-31.427912	,		33.068576,			49.501233},
			{-1.336090	,		-33.721110	,		36.251883,			49.528754},
			{-14.359989	,		-14.170431	,		45.211291,			49.508295},
			{-23.877723	,		-27.916997	,		33.153074,			49.483641},
			{-32.375624	,		-9.433814	,		36.182803,			49.460824}
		};
		double redPositionFrontBottom[15][4] = { //x, y, z, R, based off mean scattering positions
			{-14.420330	,		14.121538	,		45.202460,			49.503799},
			{-32.527526	,		9.218481	,		36.107750,			49.465038},
			{-24.017796	,		27.955173	,		33.054570,			49.507079},
			{8.930976	,		18.103811	,		45.167434,			49.473300},
			{-1.202797	,		33.767902	,		36.221881,			49.535266},
			{19.183380	,		31.465596	,		33.055614,			49.505145},
			{20.126470	,		-2.937280	,		45.141671,			49.512351},
			{31.705572	,		11.461608	,		36.224277,			49.485453},
			{35.819046	,		-8.572351	,		33.052537,			49.486963},
			{3.392044	,		-19.828723	,		45.218701,			49.491566},
			{20.791095	,		-26.652558	,		36.156359,			49.496573},
			{2.978517	,		-36.638918	,		33.152953,			49.501517},
			{-18.054716	,		-9.236527	,		45.166838,			49.510902},
			{-19.078133	,		-27.909023	,		36.118078,			49.471247},
			{-33.981603	,		-14.014443	,		33.130866,			49.485434}
		};

		double greenPositionTop[10][4] = { //x, y, z, R, based off mean scattering positions
			{-41.927731	,		12.779135	,		22.916717,			49.461266},
			{-36.712926	,		22.704053	,		24.149388,			49.462167},
			{-0.997317	,		43.744808	,		22.969859,			49.418795},
			{10.490263	,		41.964942	,		24.012447,			49.474232},
			{41.336063	,		14.473389	,		23.009291,			49.472988},
			{43.118030	,		3.314680	,		23.949683,			49.434188},
			{26.308335	,		-34.923993	,		23.109219,			49.455533},
			{16.282108	,		-39.949110	,		24.161297,			49.444987},
			{-24.991104	,		-35.884342	,		22.998069,			49.408020},
			{-32.871081	,		-28.013043	,		24.103441,			49.459220}
		};
		double greenPositionBottom[10][4] = { //x, y, z, R, based off mean scattering positions
			{-43.516864	,		7.128837	,		22.287052,			49.409012},
			{-39.431324	,		17.827358	,		23.886944,			49.429041},
			{-6.325567	,		43.648361	,		22.168606,			49.362327},
			{4.842715	,		42.921586	,		23.965776,			49.397094},
			{39.443377	,		19.791398	,		22.216285,			49.406910},
			{42.385323	,		8.586588	,		23.866842,			49.395053},
			{30.972225	,		-31.473355	,		22.209464,			49.427838},
			{21.296054	,		-37.581756	,		23.974285,			49.403205},
			{-20.256766	,		-39.230013	,		22.180944,			49.409764},
			{-29.119622	,		-31.945110	,		23.925990,			49.405419}
		};
		double greenPositionFrontTop[10][4] = { //x, y, z, R, based off mean scattering positions
			{-39.904792	,		10.968201	,		27.095771,			49.465894},
			{-34.754930	,		21.092941	,		28.155751,			49.452640},
			{-2.107750	,		41.338244	,		27.072698,			49.459317},
			{9.150063	,		39.480396	,		28.336055,			49.450555},
			{38.724533	,		14.502186	,		27.116688,			49.449142},
			{40.556353	,		3.468882	,		28.035772,			49.425251},
			{25.925856	,		-32.284572	,		26.981801,			49.421263},
			{15.859987	,		-37.482611	,		28.149466,			49.486137},
			{-22.727722	,		-34.678142	,		26.977033,			49.465980},
			{-30.942686	,		-26.473861	,		28.093284,			49.472697}
		};
		double greenPositionFrontBottom[10][4] = { //x, y, z, R, based off mean scattering positions
			{-41.554743	,		6.067589	,		26.075556,			49.432246},
			{-37.348599	,		16.746168	,		27.792614,			49.475058},
			{-6.877203	,		41.387390	,		26.153839,			49.439208},
			{4.282652	,		40.574291	,		27.923133,			49.440020},
			{37.113100	,		19.485642	,		26.231073,			49.448374},
			{39.953318	,		8.360873	,		27.890432,			49.437313},
			{29.903400	,		-29.365518	,		26.201641,			49.427452},
			{20.325254	,		-35.383995	,		27.946574,			49.458609},
			{-18.799637	,		-37.405342	,		26.326759,			49.453859},
			{-27.253734	,		-30.470207	,		27.819039,			49.447937}
		};

		double yellowPositionTop[10][4] = { //x, y, z, R, based off mean scattering positions
			{-30.653467	,		26.565183	,		28.292485,			49.455118},
			{-22.606205	,		34.760217	,		27.020262,			49.491492},
			{15.827527	,		37.409879	,		28.219252,			49.460447},
			{26.046881	,		32.173852	,		27.029988,			49.439023},
			{40.520953	,		-3.352034	,		28.080342,			49.413453},
			{38.822410	,		-14.534648	,		26.998047,			49.470497},
			{9.427127	,		-39.547889	,		28.129572,			49.438640},
			{-1.950205	,		-41.321050	,		27.087060,			49.446348},
			{-34.781806	,		-20.928514	,		28.214470,			49.435140},
			{-39.971077	,		-10.931015	,		27.086279,			49.505965}
		};
		double yellowPositionBottom[10][4] = { //x, y, z, R, based off mean scattering positions
			{-27.298371	,		30.420363	,		27.863787,			49.467062},
			{-18.613427	,		37.550531	,		26.176476,			49.413662},
			{20.589338	,		35.336282	,		27.805441,			49.454183},
			{30.048892	,		29.421311	,		26.080674,			49.484856},
			{39.968406	,		-8.439274	,		27.925204,			49.482440},
			{37.129441	,		-19.312758	,		26.298876,			49.428827},
			{4.301341	,		-40.750321	,		27.690228,			49.455424},
			{-7.171872	,		-41.424380	,		26.007054,			49.434622},
			{-37.297706	,		-16.748138	,		27.871315,			49.481604},
			{-41.597326	,		-6.134195	,		26.020648,			49.447346}
		};
		double yellowPositionFrontTop[10][4] = { //x, y, z, R, based off mean scattering positions
			{-33.066353	,		27.914521	,		23.944482,			49.456469},
			{-24.951732	,		35.922105	,		23.012541,			49.422298},
			{16.376627	,		39.914360	,		24.116772,			49.426397},
			{26.503538	,		34.939331	,		22.924978,			49.484836},
			{43.075090	,		-3.051919	,		24.065057,			49.435863},
			{41.374776	,		-14.423583	,		22.951519,			49.463967},
			{10.313560	,		-42.009695	,		24.002250,			49.470112},
			{-0.796204	,		-43.750546	,		23.020185,			49.443636},
			{-36.585514	,		-22.881259	,		24.027403,			49.389958},
			{-41.907544	,		-12.670490	,		22.969185,			49.440540}
		};
		double yellowPositionFrontBottom[10][4] = { //x, y, z, R, based off mean scattering positions
			{-29.153471	,		32.013571	,		23.854535,			49.435133},
			{-20.383484	,		39.140030	,		22.267830,			49.429592},
			{21.255217	,		37.626625	,		23.948089,			49.407066},
			{31.019162	,		31.462210	,		22.218533,			49.454244},
			{42.359941	,		-8.755362	,		23.902660,			49.420219},
			{39.530304	,		-19.622295	,		22.299362,			49.446344},
			{5.014469	,		-42.854635	,		23.938405,			49.342799},
			{-6.605938	,		-43.775787	,		22.083225,			49.473496},
			{-39.438754	,		-17.765248	,		23.932967,			49.434869},
			{-43.560162	,		-7.431755	,		22.208150,			49.456249}
		};
		//////////////////////////////////////////////
		ClassDef(DetectorDaemon,1);
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
