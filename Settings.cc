#include "Settings.hh"

#include "TEnv.h"
#include "TString.h"

Settings::Settings(std::string fileName, int verbosityLevel)
    : fVerbosityLevel(verbosityLevel) {
    TEnv env;
    env.ReadFile(fileName.c_str(),kEnvLocal);

    //  env.PrintEnv();

    //fNtupleName = env.GetValue("NtupleName","/ntuple/ntuple");
    fNtupleName = env.GetValue("NtupleName","/ntuple");

    fBufferSize = env.GetValue("BufferSize",1024000);

    fSortNumberOfEvents = env.GetValue("SortNumberOfEvents",0);

    fWriteTree = env.GetValue("WriteTree",true);

    fWrite2DHist = env.GetValue("Write2DHist",false);

    //fWrite3DHist = env.GetValue("Write3DHist",false);
        
    fWriteNDHist = env.GetValue("WriteNDHist",false);

    fWrite2DSGGHist = env.GetValue("Write2DSGGHist",false);

    fWriteGriffinAddbackVector = env.GetValue("WriteGriffinAddbackVector",false);

    fGriffinAddbackVectorLengthmm = env.GetValue("GriffinAddbackVectorLengthmm",105.0);

    fGriffinAddbackVectorDepthmm = env.GetValue("GriffinAddbackVectorDepthmm",45.0);

    fGriffinAddbackVectorCrystalFaceDistancemm = env.GetValue("GriffinAddbackVectorCrystalFaceDistancemm",110.0);

    // Griffin
    fResolution[1000].resize(16);
    fThreshold[1000].resize(16,std::vector<double>(4));
    fThresholdWidth[1000].resize(16,std::vector<double>(4));
    fTimeWindow[1000].resize(16,std::vector<double>(4));

    fResolution[1010].resize(16);
    fThreshold[1010].resize(16,std::vector<double>(4));
    fThresholdWidth[1010].resize(16,std::vector<double>(4));
    fTimeWindow[1010].resize(16,std::vector<double>(4));

    fResolution[1020].resize(16);
    fThreshold[1020].resize(16,std::vector<double>(4));
    fThresholdWidth[1020].resize(16,std::vector<double>(4));
    fTimeWindow[1020].resize(16,std::vector<double>(4));

    fResolution[1030].resize(16);
    fThreshold[1030].resize(16,std::vector<double>(4));
    fThresholdWidth[1030].resize(16,std::vector<double>(4));
    fTimeWindow[1030].resize(16,std::vector<double>(4));

    fResolution[1040].resize(16);
    fThreshold[1040].resize(16,std::vector<double>(4));
    fThresholdWidth[1040].resize(16,std::vector<double>(4));
    fTimeWindow[1040].resize(16,std::vector<double>(4));

    fResolution[1050].resize(16);
    fThreshold[1050].resize(16,std::vector<double>(4));
    fThresholdWidth[1050].resize(16,std::vector<double>(4));
    fTimeWindow[1050].resize(16,std::vector<double>(4));

    // LaBr3
    fResolution[2000].resize(16);
    fThreshold[2000].resize(16,std::vector<double>(1));
    fThresholdWidth[2000].resize(16,std::vector<double>(1));
    fTimeWindow[2000].resize(16,std::vector<double>(1));

    // Sceptar
    fResolution[5000].resize(20);
    fThreshold[5000].resize(20,std::vector<double>(1));
    fThresholdWidth[5000].resize(20,std::vector<double>(1));
    fTimeWindow[5000].resize(20,std::vector<double>(1));

    // EightPi
    fResolution[6000].resize(20);
    fThreshold[6000].resize(20,std::vector<double>(4));
    fThresholdWidth[6000].resize(20,std::vector<double>(4));
    fTimeWindow[6000].resize(20,std::vector<double>(4));

    fResolution[6010].resize(20);
    fThreshold[6010].resize(20,std::vector<double>(4));
    fThresholdWidth[6010].resize(20,std::vector<double>(4));
    fTimeWindow[6010].resize(20,std::vector<double>(4));

    fResolution[6020].resize(20);
    fThreshold[6020].resize(20,std::vector<double>(4));
    fThresholdWidth[6020].resize(20,std::vector<double>(4));
    fTimeWindow[6020].resize(20,std::vector<double>(4));

    fResolution[6030].resize(20);
    fThreshold[6030].resize(20,std::vector<double>(4));
    fThresholdWidth[6030].resize(20,std::vector<double>(4));
    fTimeWindow[6030].resize(20,std::vector<double>(4));

    // Descant
    fResolution[8010].resize(15);
    fThreshold[8010].resize(15,std::vector<double>(1));
    fThresholdWidth[8010].resize(15,std::vector<double>(1));
    fTimeWindow[8010].resize(15,std::vector<double>(1));

    fResolution[8020].resize(10);
    fThreshold[8020].resize(10,std::vector<double>(1));
    fThresholdWidth[8020].resize(10,std::vector<double>(1));
    fTimeWindow[8020].resize(10,std::vector<double>(1));

    fResolution[8030].resize(15);
    fThreshold[8030].resize(15,std::vector<double>(1));
    fThresholdWidth[8030].resize(15,std::vector<double>(1));
    fTimeWindow[8030].resize(15,std::vector<double>(1));

    fResolution[8040].resize(20);
    fThreshold[8040].resize(20,std::vector<double>(1));
    fThresholdWidth[8040].resize(20,std::vector<double>(1));
    fTimeWindow[8040].resize(20,std::vector<double>(1));

    fResolution[8050].resize(10);
    fThreshold[8050].resize(10,std::vector<double>(1));
    fThresholdWidth[8050].resize(10,std::vector<double>(1));
    fTimeWindow[8050].resize(10,std::vector<double>(1));

	 //testcan
    fResolution[8500].resize(1);
    fThreshold[8500].resize(1,std::vector<double>(1));
    fThresholdWidth[8500].resize(1,std::vector<double>(1));
    fTimeWindow[8500].resize(1,std::vector<double>(1));

    // Daemon Bar, assuming 14 across, 18 total
    fResolution[8700].resize(18);
    fThreshold[8700].resize(18,std::vector<double>(1));
    fThresholdWidth[8700].resize(18,std::vector<double>(1));
    fTimeWindow[8700].resize(18,std::vector<double>(1));
    //ZDS
    fResolution[9000].resize(1);
    fThreshold[9000].resize(1,std::vector<double>(1));
    fThresholdWidth[9000].resize(1,std::vector<double>(1));
    fTimeWindow[9000].resize(1,std::vector<double>(1));
    
    // Daemon Tiles 
    fResolution[8710].resize(15);
    fThreshold[8710].resize(15,std::vector<double>(1));
    fThresholdWidth[8710].resize(15,std::vector<double>(1));
    fTimeWindow[8710].resize(15,std::vector<double>(1));

    fResolution[8720].resize(20);
    fThreshold[8720].resize(20,std::vector<double>(1));
    fThresholdWidth[8720].resize(20,std::vector<double>(1));
    fTimeWindow[8720].resize(20,std::vector<double>(1));

    fResolution[8730].resize(15);
    fThreshold[8730].resize(15,std::vector<double>(1));
    fThresholdWidth[8730].resize(15,std::vector<double>(1));
    fTimeWindow[8730].resize(15,std::vector<double>(1));

    fResolution[8740].resize(10);
    fThreshold[8740].resize(10,std::vector<double>(1));
    fThresholdWidth[8740].resize(10,std::vector<double>(1));
    fTimeWindow[8740].resize(10,std::vector<double>(1));

    fResolution[8750].resize(10);
    fThreshold[8750].resize(10,std::vector<double>(1));
    fThresholdWidth[8750].resize(10,std::vector<double>(1));
    fTimeWindow[8750].resize(10,std::vector<double>(1));
    
 /*   // Paces
    fResolution[9000].resize(5);
    fThreshold[9000].resize(5,std::vector<double>(1));
    fThresholdWidth[9000].resize(5,std::vector<double>(1));
    fTimeWindow[9000].resize(5,std::vector<double>(1));
*/
    double offset, linear, quadratic, cubic;

    // Griffin
    for(int detector = 0; detector < 16; ++detector) {
        for(int crystal = 0; crystal < 4; ++crystal) {
            offset = env.GetValue(Form("Griffin.%d.%d.Resolution.Offset",detector,crystal),1.100);
            linear = env.GetValue(Form("Griffin.%d.%d.Resolution.Linear",detector,crystal),0.00183744);
            quadratic = env.GetValue(Form("Griffin.%d.%d.Resolution.Quadratic",detector,crystal),0.0000007);
            cubic = env.GetValue(Form("Griffin.%d.%d.Resolution.Cubic",detector,crystal),0.);
            fResolution[1000][detector].push_back(TF1(Form("Griffin.%d.%d.Resolution",detector,crystal),
                                                      Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
            fThreshold[1000][detector][crystal] = env.GetValue(Form("Griffin.%d.%d.Threshold.keV",detector,crystal),10.);
            fThresholdWidth[1000][detector][crystal] = env.GetValue(Form("Griffin.%d.%d.ThresholdWidth.keV",detector,crystal),2.);
            fTimeWindow[1000][detector][crystal] = env.GetValue(Form("Griffin.%d.%d.TimeWindow.sec",detector,crystal),0.);

            offset = env.GetValue(Form("Griffin.BGO.Front.Left.%d.%d.Resolution.Offset",detector,crystal),1.100);
            linear = env.GetValue(Form("Griffin.BGO.Front.Left.%d.%d.Resolution.Linear",detector,crystal),0.00183744);
            quadratic = env.GetValue(Form("Griffin.BGO.Front.Left.%d.%d.Resolution.Quadratic",detector,crystal),0.0000007);
            cubic = env.GetValue(Form("Griffin.BGO.Front.Left.%d.%d.Resolution.Cubic",detector,crystal),0.);
            fResolution[1010][detector].push_back(TF1(Form("Griffin.BGO.Front.Left.%d.%d.Resolution",detector,crystal),
                                                      Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
            fThreshold[1010][detector][crystal] = env.GetValue(Form("Griffin.BGO.Front.Left.%d.%d.Threshold.keV",detector,crystal),10.);
            fThresholdWidth[1010][detector][crystal] = env.GetValue(Form("Griffin.BGO.Front.Left.%d.%d.ThresholdWidth.keV",detector,crystal),2.);
            fTimeWindow[1010][detector][crystal] = env.GetValue(Form("Griffin.BGO.Front.Left.%d.%d.TimeWindow.sec",detector,crystal),0.);

            offset = env.GetValue(Form("Griffin.BGO.Front.Right.%d.%d.Resolution.Offset",detector,crystal),1.100);
            linear = env.GetValue(Form("Griffin.BGO.Front.Right.%d.%d.Resolution.Linear",detector,crystal),0.00183744);
            quadratic = env.GetValue(Form("Griffin.BGO.Front.Right.%d.%d.Resolution.Quadratic",detector,crystal),0.0000007);
            cubic = env.GetValue(Form("Griffin.BGO.Front.Right.%d.%d.Resolution.Cubic",detector,crystal),0.);
            fResolution[1020][detector].push_back(TF1(Form("Griffin.BGO.Front.Right.%d.%d.Resolution",detector,crystal),
                                                      Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
            fThreshold[1020][detector][crystal] = env.GetValue(Form("Griffin.BGO.Front.Right.%d.%d.Threshold.keV",detector,crystal),10.);
            fThresholdWidth[1020][detector][crystal] = env.GetValue(Form("Griffin.BGO.Front.Right.%d.%d.ThresholdWidth.keV",detector,crystal),2.);
            fTimeWindow[1020][detector][crystal] = env.GetValue(Form("Griffin.BGO.Front.Right.%d.%d.TimeWindow.sec",detector,crystal),0.);

            offset = env.GetValue(Form("Griffin.BGO.Side.Left.%d.%d.Resolution.Offset",detector,crystal),1.100);
            linear = env.GetValue(Form("Griffin.BGO.Side.Left.%d.%d.Resolution.Linear",detector,crystal),0.00183744);
            quadratic = env.GetValue(Form("Griffin.BGO.Side.Left.%d.%d.Resolution.Quadratic",detector,crystal),0.0000007);
            cubic = env.GetValue(Form("Griffin.BGO.Side.Left.%d.%d.Resolution.Cubic",detector,crystal),0.);
            fResolution[1030][detector].push_back(TF1(Form("Griffin.BGO.Side.Left.%d.%d.Resolution",detector,crystal),
                                                      Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
            fThreshold[1030][detector][crystal] = env.GetValue(Form("Griffin.BGO.Side.Left.%d.%d.Threshold.keV",detector,crystal),10.);
            fThresholdWidth[1030][detector][crystal] = env.GetValue(Form("Griffin.BGO.Side.Left.%d.%d.ThresholdWidth.keV",detector,crystal),2.);
            fTimeWindow[1030][detector][crystal] = env.GetValue(Form("Griffin.BGO.Side.Left.%d.%d.TimeWindow.sec",detector,crystal),0.);

            offset = env.GetValue(Form("Griffin.BGO.Side.Right.%d.%d.Resolution.Offset",detector,crystal),1.100);
            linear = env.GetValue(Form("Griffin.BGO.Side.Right.%d.%d.Resolution.Linear",detector,crystal),0.00183744);
            quadratic = env.GetValue(Form("Griffin.BGO.Side.Right.%d.%d.Resolution.Quadratic",detector,crystal),0.0000007);
            cubic = env.GetValue(Form("Griffin.BGO.Side.Right.%d.%d.Resolution.Cubic",detector,crystal),0.);
            fResolution[1040][detector].push_back(TF1(Form("Griffin.BGO.Side.Right.%d.%d.Resolution",detector,crystal),
                                                      Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
            fThreshold[1040][detector][crystal] = env.GetValue(Form("Griffin.BGO.Side.Right.%d.%d.Threshold.keV",detector,crystal),10.);
            fThresholdWidth[1040][detector][crystal] = env.GetValue(Form("Griffin.BGO.Side.Right.%d.%d.ThresholdWidth.keV",detector,crystal),2.);
            fTimeWindow[1040][detector][crystal] = env.GetValue(Form("Griffin.BGO.Side.Right.%d.%d.TimeWindow.sec",detector,crystal),0.);

            offset = env.GetValue(Form("Griffin.BGO.Back.%d.%d.Resolution.Offset",detector,crystal),1.100);
            linear = env.GetValue(Form("Griffin.BGO.Back.%d.%d.Resolution.Linear",detector,crystal),0.00183744);
            quadratic = env.GetValue(Form("Griffin.BGO.Back.%d.%d.Resolution.Quadratic",detector,crystal),0.0000007);
            cubic = env.GetValue(Form("Griffin.BGO.Back.%d.%d.Resolution.Cubic",detector,crystal),0.);
            fResolution[1050][detector].push_back(TF1(Form("Griffin.BGO.Back.%d.%d.Resolution",detector,crystal),
                                                      Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
            fThreshold[1050][detector][crystal] = env.GetValue(Form("Griffin.BGO.Back.%d.%d.Threshold.keV",detector,crystal),10.);
            fThresholdWidth[1050][detector][crystal] = env.GetValue(Form("Griffin.BGO.Back.%d.%d.ThresholdWidth.keV",detector,crystal),2.);
            fTimeWindow[1050][detector][crystal] = env.GetValue(Form("Griffin.BGO.Back.%d.%d.TimeWindow.sec",detector,crystal),0.);
        }
    }

    // LaBr3
    for(int detector = 0; detector < 16; ++detector) {
        offset = env.GetValue(Form("LaBr3.%d.Resolution.Offset",detector),1.7006116);
        linear = env.GetValue(Form("LaBr3.%d.Resolution.Linear",detector),0.5009382);
        quadratic = env.GetValue(Form("LaBr3.%d.Resolution.Quadratic",detector),0.000065451219);
        cubic = env.GetValue(Form("LaBr3.%d.Resolution.Cubic",detector),0.);
        fResolution[2000][detector].push_back(TF1(Form("LaBr3.%d.Resolution",detector),
                                                  Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
        fThreshold[2000][detector][0] = env.GetValue(Form("LaBr3.%d.Threshold.keV",detector),10.);
        fThresholdWidth[2000][detector][0] = env.GetValue(Form("LaBr3.%d.ThresholdWidth.keV",detector),2.);
        fTimeWindow[2000][detector][0] = env.GetValue(Form("LaBr3.%d.TimeWindow.sec",detector),0.);
    }

    // Sceptar
    for(int detector = 0; detector < 20; ++detector) {
        offset = env.GetValue(Form("Sceptar.%d.Resolution.Offset",detector),0.0);
        linear = env.GetValue(Form("Sceptar.%d.Resolution.Linear",detector),0.0);
        quadratic = env.GetValue(Form("Sceptar.%d.Resolution.Quadratic",detector),0.0);
        cubic = env.GetValue(Form("Sceptar.%d.Resolution.Cubic",detector),0.0);
        fResolution[5000][detector].push_back(TF1(Form("Sceptar.%d.Resolution",detector),
                                                  Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
        fThreshold[5000][detector][0] = env.GetValue(Form("Sceptar.%d.Threshold.keV",detector),0.0);
        fThresholdWidth[5000][detector][0] = env.GetValue(Form("Sceptar.%d.ThresholdWidth.keV",detector),0.0);
        fTimeWindow[5000][detector][0] = env.GetValue(Form("Sceptar.%d.TimeWindow.sec",detector),0.0);
    }

    // EightPi
    for(int detector = 0; detector < 20; ++detector) {
        offset = env.GetValue(Form("EightPi.%d.Resolution.Offset",detector),1.100);
        linear = env.GetValue(Form("EightPi.%d.Resolution.Linear",detector),0.00183744);
        quadratic = env.GetValue(Form("EightPi.%d.Resolution.Quadratic",detector),0.0000007);
        cubic = env.GetValue(Form("EightPi.%d.Resolution.Cubic",detector),0.);
        fResolution[6000][detector].push_back(TF1(Form("EightPi.%d.Resolution",detector),
                                                  Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
        fThreshold[6000][detector][0] = env.GetValue(Form("EightPi.%d.Threshold.keV",detector),10.);
        fThresholdWidth[6000][detector][0] = env.GetValue(Form("EightPi.%d.ThresholdWidth.keV",detector),2.);
        fTimeWindow[6000][detector][0] = env.GetValue(Form("EightPi.%d.TimeWindow.sec",detector),0.);

        offset = env.GetValue(Form("EightPi.BGO.%d.Resolution.Offset",detector),1.100);
        linear = env.GetValue(Form("EightPi.BGO.%d.Resolution.Linear",detector),0.00183744);
        quadratic = env.GetValue(Form("EightPi.BGO.%d.Resolution.Quadratic",detector),0.0000007);
        cubic = env.GetValue(Form("EightPi.BGO.%d.Resolution.Cubic",detector),0.);
        fResolution[6010][detector].push_back(TF1(Form("EightPi.BGO.%d.Resolution",detector),
                                                  Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
        fThreshold[6010][detector][0] = env.GetValue(Form("EightPi.BGO.%d.Threshold.keV",detector),10.);
        fThresholdWidth[6010][detector][0] = env.GetValue(Form("EightPi.BGO.%d.ThresholdWidth.keV",detector),2.);
        fTimeWindow[6010][detector][0] = env.GetValue(Form("EightPi.BGO.%d.TimeWindow.sec",detector),0.);

        offset = env.GetValue(Form("EightPi.BGO.%d.Resolution.Offset",detector),1.100);
        linear = env.GetValue(Form("EightPi.BGO.%d.Resolution.Linear",detector),0.00183744);
        quadratic = env.GetValue(Form("EightPi.BGO.%d.Resolution.Quadratic",detector),0.0000007);
        cubic = env.GetValue(Form("EightPi.BGO.%d.Resolution.Cubic",detector),0.);
        fResolution[6020][detector].push_back(TF1(Form("EightPi.BGO.%d.Resolution",detector),
                                                  Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
        fThreshold[6020][detector][0] = env.GetValue(Form("EightPi.BGO.%d.Threshold.keV",detector),10.);
        fThresholdWidth[6020][detector][0] = env.GetValue(Form("EightPi.BGO.%d.ThresholdWidth.keV",detector),2.);
        fTimeWindow[6020][detector][0] = env.GetValue(Form("EightPi.BGO.%d.TimeWindow.sec",detector),0.);

        offset = env.GetValue(Form("EightPi.BGO.%d.Resolution.Offset",detector),1.100);
        linear = env.GetValue(Form("EightPi.BGO.%d.Resolution.Linear",detector),0.00183744);
        quadratic = env.GetValue(Form("EightPi.BGO.%d.Resolution.Quadratic",detector),0.0000007);
        cubic = env.GetValue(Form("EightPi.BGO.%d.Resolution.Cubic",detector),0.);
        fResolution[6030][detector].push_back(TF1(Form("EightPi.BGO.%d.Resolution",detector),
                                                  Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
        fThreshold[6030][detector][0] = env.GetValue(Form("EightPi.BGO.%d.Threshold.keV",detector),10.);
        fThresholdWidth[6030][detector][0] = env.GetValue(Form("EightPi.BGO.%d.ThresholdWidth.keV",detector),2.);
        fTimeWindow[6030][detector][0] = env.GetValue(Form("EightPi.BGO.%d.TimeWindow.sec",detector),0.);
    }

    // DESCANT
    for(int detector = 0; detector < 15; ++detector) {
        offset = env.GetValue(Form("Descant.Blue.%d.Resolution.Offset",detector),0.0);
        linear = env.GetValue(Form("Descant.Blue.%d.Resolution.Linear",detector),0.0);
        quadratic = env.GetValue(Form("Descant.Blue.%d.Resolution.Quadratic",detector),0.009);
        cubic = env.GetValue(Form("Descant.Blue.%d.Resolution.Cubic",detector),0.0);
        fResolution[8010][detector].push_back(TF1(Form("Descant.Blue.%d.Resolution",detector),
                                                  Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
        fThreshold[8010][detector][0] = env.GetValue(Form("Descant.Blue.%d.Threshold.keV",detector),0.);
        fThresholdWidth[8010][detector][0] = env.GetValue(Form("Descant.Blue.%d.ThresholdWidth.keV",detector),0.);
        fTimeWindow[8010][detector][0] = env.GetValue(Form("Descant.Blue.%d.TimeWindow.sec",detector),0.);
    }
    for(int detector = 0; detector < 10; ++detector) {
        offset = env.GetValue(Form("Descant.Green.%d.Resolution.Offset",detector),0.0);
        linear = env.GetValue(Form("Descant.Green.%d.Resolution.Linear",detector),0.0);
        quadratic = env.GetValue(Form("Descant.Green.%d.Resolution.Quadratic",detector),0.009);
        cubic = env.GetValue(Form("Descant.Green.%d.Resolution.Cubic",detector),0.0);
        fResolution[8020][detector].push_back(TF1(Form("Descant.Green.%d.Resolution",detector),
                                                  Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
        fThreshold[8020][detector][0] = env.GetValue(Form("Descant.Green.%d.Threshold.keV",detector),0.);
        fThresholdWidth[8020][detector][0] = env.GetValue(Form("Descant.Green.%d.ThresholdWidth.keV",detector),0.);
        fTimeWindow[8020][detector][0] = env.GetValue(Form("Descant.Green.%d.TimeWindow.sec",detector),0.);
    }
    for(int detector = 0; detector < 15; ++detector) {
        offset = env.GetValue(Form("Descant.Red.%d.Resolution.Offset",detector),0.0);
        linear = env.GetValue(Form("Descant.Red.%d.Resolution.Linear",detector),0.0);
        quadratic = env.GetValue(Form("Descant.Red.%d.Resolution.Quadratic",detector),0.009);
        cubic = env.GetValue(Form("Descant.Red.%d.Resolution.Cubic",detector),0.0);
        fResolution[8030][detector].push_back(TF1(Form("Descant.Red.%d.Resolution",detector),
                                                  Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
        fThreshold[8030][detector][0] = env.GetValue(Form("Descant.Red.%d.Threshold.keV",detector),0.);
        fThresholdWidth[8030][detector][0] = env.GetValue(Form("Descant.Red.%d.ThresholdWidth.keV",detector),0.);
        fTimeWindow[8030][detector][0] = env.GetValue(Form("Descant.Red.%d.TimeWindow.sec",detector),0.);
    }
    for(int detector = 0; detector < 20; ++detector) {
        offset = env.GetValue(Form("Descant.White.%d.Resolution.Offset",detector),0.0);
        linear = env.GetValue(Form("Descant.White.%d.Resolution.Linear",detector),0.0);
        quadratic = env.GetValue(Form("Descant.White.%d.Resolution.Quadratic",detector),0.009);
        cubic = env.GetValue(Form("Descant.White.%d.Resolution.Cubic",detector),0.0);
        fResolution[8040][detector].push_back(TF1(Form("Descant.White.%d.Resolution",detector),
                                                  Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
        fThreshold[8040][detector][0] = env.GetValue(Form("Descant.White.%d.Threshold.keV",detector),0.);
        fThresholdWidth[8040][detector][0] = env.GetValue(Form("Descant.White.%d.ThresholdWidth.keV",detector),0.);
        fTimeWindow[8040][detector][0] = env.GetValue(Form("Descant.White.%d.TimeWindow.sec",detector),0.);
    }
    for(int detector = 0; detector < 10; ++detector) {
        offset = env.GetValue(Form("Descant.Yellow.%d.Resolution.Offset",detector),0.0);
        linear = env.GetValue(Form("Descant.Yellow.%d.Resolution.Linear",detector),0.0);
        quadratic = env.GetValue(Form("Descant.Yellow.%d.Resolution.Quadratic",detector),0.009);
        cubic = env.GetValue(Form("Descant.Yellow.%d.Resolution.Cubic",detector),0.0);
        fResolution[8050][detector].push_back(TF1(Form("Descant.Yellow.%d.Resolution",detector),
                                                  Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
        fThreshold[8050][detector][0] = env.GetValue(Form("Descant.Yellow.%d.Threshold.keV",detector),0.);
        fThresholdWidth[8050][detector][0] = env.GetValue(Form("Descant.Yellow.%d.ThresholdWidth.keV",detector),0.);
        fTimeWindow[8050][detector][0] = env.GetValue(Form("Descant.Yellow.%d.TimeWindow.sec",detector),0.);
    }

    // Daemon Bars
	 //double fanoFactor1 = env.GetValue("DaemonBars.Resolution.FanoFactor",20.);
    for(int detector = 0; detector < 18; ++detector) {
        offset = env.GetValue(Form("DaemonBars.%d.Resolution.Offset",detector),0.0);
        linear = env.GetValue(Form("DaemonBars.%d.Resolution.Linear",detector),0.0);
        quadratic = env.GetValue(Form("DaemonBars.%d.Resolution.Quadratic",detector),0.000);
        cubic = env.GetValue(Form("DaemonBars.%d.Resolution.Cubic",detector),0.0);
        fResolution[8700][detector].push_back(TF1(Form("DaemonBars.%d.Resolution",detector),
                                                  Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
	//fResolution[8700][detector].push_back(TF1(Form("DaemonBars.%d.Resolution",detector),Form("%f*TMath::Sqrt(x)",fanoFactor1), 0., 100000.));
	//fResolution[8700][detector].push_back(TF1(Form("DaemonBars.%d.Resolution",detector), 0., 0., 100000.));
        fThreshold[8700][detector][0] = env.GetValue(Form("DaemonBars.%d.Threshold.keV",detector),0.);
        fThresholdWidth[8700][detector][0] = env.GetValue(Form("DaemonBars.%d.ThresholdWidth.keV",detector),0.);
        fTimeWindow[8700][detector][0] = env.GetValue(Form("DaemonBars.%d.TimeWindow.sec",detector),0.);
    }
	 
	//ZDS
    	//double fanoFactor2 = env.GetValue("ZDS.Resolution.FanoFactor",20.);
	 //fResolution[9000][0].push_back(TF1("ZDS.Resolution",Form("%f*TMath::Sqrt(x)",fanoFactor2), 0., 100000.));
	 //fResolution[9000][0].push_back(TF1("ZDS.Resolution", 0. , 0., 100000.));
        offset = env.GetValue("ZDS.Resolution.Offset",0.0);
        linear = env.GetValue("ZDS.Resolution.Linear",0.0);
        quadratic = env.GetValue("ZDS.Resolution.Quadratic",0.0);
        cubic = env.GetValue("ZDS.Resolution.Cubic",0.0);
        fResolution[9000][0].push_back(TF1("ZDS.Resolution",
                                                  Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
	 fThreshold[9000][0][0] = env.GetValue("ZDS.Threshold.keV",0.);
	 fThresholdWidth[9000][0][0] = env.GetValue("ZDS.ThresholdWidth.keV",0.);
	 fTimeWindow[9000][0][0] = env.GetValue("ZDS.TimeWindow.sec",0.);
    
    // Daemon Tiles
    for(int detector = 0; detector < 15; ++detector) {
        offset = env.GetValue(Form("DaemonTiles.Blue.%d.Resolution.Offset",detector),0.0);
        linear = env.GetValue(Form("DaemonTiles.Blue.%d.Resolution.Linear",detector),0.0);
        quadratic = env.GetValue(Form("DaemonTiles.Blue.%d.Resolution.Quadratic",detector),0.0);
        cubic = env.GetValue(Form("DaemonTiles.Blue.%d.Resolution.Cubic",detector),0.0);
        fResolution[8710][detector].push_back(TF1(Form("DaemonTiles.Blue.%d.Resolution",detector),
                                                  Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
        fThreshold[8710][detector][0] = env.GetValue(Form("DaemonTiles.Blue.%d.Threshold.keV",detector),0.);
        fThresholdWidth[8710][detector][0] = env.GetValue(Form("DaemonTiles.Blue.%d.ThresholdWidth.keV",detector),0.);
        fTimeWindow[8710][detector][0] = env.GetValue(Form("DaemonTiles.Blue.%d.TimeWindow.sec",detector),0.);
    }
    for(int detector = 0; detector < 20; ++detector) {
        offset = env.GetValue(Form("DaemonTiles.White.%d.Resolution.Offset",detector),0.0);
        linear = env.GetValue(Form("DaemonTiles.White.%d.Resolution.Linear",detector),0.0);
        quadratic = env.GetValue(Form("DaemonTiles.White.%d.Resolution.Quadratic",detector),0.0);
        cubic = env.GetValue(Form("DaemonTiles.White.%d.Resolution.Cubic",detector),0.0);
        fResolution[8720][detector].push_back(TF1(Form("DaemonTiles.White.%d.Resolution",detector),
                                                  Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
        fThreshold[8720][detector][0] = env.GetValue(Form("DaemonTiles.White.%d.Threshold.keV",detector),0.);
        fThresholdWidth[8720][detector][0] = env.GetValue(Form("DaemonTiles.White.%d.ThresholdWidth.keV",detector),0.);
        fTimeWindow[8720][detector][0] = env.GetValue(Form("DaemonTiles.White.%d.TimeWindow.sec",detector),0.);
    }
    for(int detector = 0; detector < 15; ++detector) {
        offset = env.GetValue(Form("DaemonTiles.Red.%d.Resolution.Offset",detector),0.0);
        linear = env.GetValue(Form("DaemonTiles.Red.%d.Resolution.Linear",detector),0.0);
        quadratic = env.GetValue(Form("DaemonTiles.Red.%d.Resolution.Quadratic",detector),0.0);
        cubic = env.GetValue(Form("DaemonTiles.Red.%d.Resolution.Cubic",detector),0.0);
        fResolution[8730][detector].push_back(TF1(Form("DaemonTiles.Red.%d.Resolution",detector),
                                                  Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
        fThreshold[8730][detector][0] = env.GetValue(Form("DaemonTiles.Red.%d.Threshold.keV",detector),0.);
        fThresholdWidth[8730][detector][0] = env.GetValue(Form("DaemonTiles.Red.%d.ThresholdWidth.keV",detector),0.);
        fTimeWindow[8730][detector][0] = env.GetValue(Form("DaemonTiles.Red.%d.TimeWindow.sec",detector),0.);
    }
    for(int detector = 0; detector < 10; ++detector) {
        offset = env.GetValue(Form("DaemonTiles.Green.%d.Resolution.Offset",detector),0.0);
        linear = env.GetValue(Form("DaemonTiles.Green.%d.Resolution.Linear",detector),0.0);
        quadratic = env.GetValue(Form("DaemonTiles.Green.%d.Resolution.Quadratic",detector),0.0);
        cubic = env.GetValue(Form("DaemonTiles.Green.%d.Resolution.Cubic",detector),0.0);
        fResolution[8740][detector].push_back(TF1(Form("DaemonTiles.Green.%d.Resolution",detector),
                                                  Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
        fThreshold[8740][detector][0] = env.GetValue(Form("DaemonTiles.Green.%d.Threshold.keV",detector),0.);
        fThresholdWidth[8740][detector][0] = env.GetValue(Form("DaemonTiles.Green.%d.ThresholdWidth.keV",detector),0.);
        fTimeWindow[8740][detector][0] = env.GetValue(Form("DaemonTiles.Green.%d.TimeWindow.sec",detector),0.);
    }
    for(int detector = 0; detector < 10; ++detector) {
        offset = env.GetValue(Form("DaemonTiles.Yellow.%d.Resolution.Offset",detector),0.0);
        linear = env.GetValue(Form("DaemonTiles.Yellow.%d.Resolution.Linear",detector),0.0);
        quadratic = env.GetValue(Form("DaemonTiles.Yellow.%d.Resolution.Quadratic",detector),0.0);
        cubic = env.GetValue(Form("DaemonTiles.Yellow.%d.Resolution.Cubic",detector),0.0);
        fResolution[8750][detector].push_back(TF1(Form("DaemonTiles.Yellow.%d.Resolution",detector),
                                                  Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
        fThreshold[8750][detector][0] = env.GetValue(Form("DaemonTiles.Yellow.%d.Threshold.keV",detector),0.);
        fThresholdWidth[8750][detector][0] = env.GetValue(Form("DaemonTiles.Yellow.%d.ThresholdWidth.keV",detector),0.);
        fTimeWindow[8750][detector][0] = env.GetValue(Form("DaemonTiles.Yellow.%d.TimeWindow.sec",detector),0.);
    }
	 //testcan
	 double fanoFactor = env.GetValue("Testcan.Resolution.FanoFactor",20.);
	 fResolution[8500][0].push_back(TF1("Testcan.Resolution",Form("%f*TMath::Sqrt(x)",fanoFactor), 0., 100000.));
	 fThreshold[8500][0][0] = env.GetValue("Testcan.Threshold.keV",0.);
	 fThresholdWidth[8500][0][0] = env.GetValue("Testcan.ThresholdWidth.keV",0.);
	 fTimeWindow[8500][0][0] = env.GetValue("Testcan.TimeWindow.sec",0.);


    // Paces
/*    for(int detector = 0; detector < 5; ++detector) {
        offset = env.GetValue(Form("Paces.%d.Resolution.Offset",detector),0.0);
        linear = env.GetValue(Form("Paces.%d.Resolution.Linear",detector),0.0);
        quadratic = env.GetValue(Form("Paces.%d.Resolution.Quadratic",detector),0.0);
        cubic = env.GetValue(Form("Paces.%d.Resolution.Cubic",detector),0.0);
        fResolution[9000][detector].push_back(TF1(Form("Paces.%d.Resolution",detector),
                                                  Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
        fThreshold[9000][detector][0] = env.GetValue(Form("Paces.%d.Threshold.keV",detector),0.0);
        fThresholdWidth[9000][detector][0] = env.GetValue(Form("Paces.%d.ThresholdWidth.keV",detector),0.0);
        fTimeWindow[9000][detector][0] = env.GetValue(Form("Paces.%d.TimeWindow.sec",detector),0.0);
    }
*/
    fNofBins["Statistics"] = env.GetValue("Histogram.Statistics.NofBins",64);
    fRangeLow["Statistics"] = env.GetValue("Histogram.Statistics.RangeLow.keV",0.);
    fRangeHigh["Statistics"] = env.GetValue("Histogram.Statistics.RangeHigh.keV",64.);

    fNofBins["Griffin1D"] = env.GetValue("Histogram.1D.Griffin.NofBins",4096);
    fRangeLow["Griffin1D"] = env.GetValue("Histogram.1D.Griffin.RangeLow.keV",0.5);
    fRangeHigh["Griffin1D"] = env.GetValue("Histogram.1D.Griffin.RangeHigh.keV",4096.5);
    
    fNofBins["Event1D"] = env.GetValue("Histogram.1D.Event.NofBins",1000000);
    fRangeLow["Event1D"] = env.GetValue("Histogram.1D.Event.RangeLow.s",0);
    fRangeHigh["Event1D"] = env.GetValue("Histogram.1D.Event.RangeHigh.s", 1000000);
    
    fNofBins["Daemon1D"] = env.GetValue("Histogram.1D.Daemon.NofBins",50000);
    fRangeLow["Daemon1D"] = env.GetValue("Histogram.1D.Daemon.RangeLow.s",0);
    fRangeHigh["Daemon1D"] = env.GetValue("Histogram.1D.Daemon.RangeHigh.s", 5000);
    
    fNofBins["Daemon1Dns"] = env.GetValue("Histogram.1D.Daemon.NofBins", 5100);
    fRangeLow["Daemon1Dns"] = env.GetValue("Histogram.1D.Daemon.RangeLow.ns", -10);
    fRangeHigh["Daemon1Dns"] = env.GetValue("Histogram.1D.Daemon.RangeHigh.ns", 500);
    
    fNofBins["Daemon1DEnergy"] = env.GetValue("Histogram.1D.DaemonEnergy.NofBins",5000);
    fRangeLow["Daemon1DEnergy"] = env.GetValue("Histogram.1D.DaemonEnergy.RangeLow.keV",0);
    fRangeHigh["Daemon1DEnergy"] = env.GetValue("Histogram.1D.DaemonEnergy.RangeHigh.keV", 5000);
    
    fNofBins["Daemon1DRand"] = env.GetValue("Histogram.1D.DaemonDelta.NofBins",10000);
    fRangeLow["Daemon1DRand"] = env.GetValue("Histogram.1D.DaemonDelta.RangeLow.ns", -5);
    fRangeHigh["Daemon1DRand"] = env.GetValue("Histogram.1D.DaemonDelta.RangeHigh.ns", 5);
    
    fNofBins["Daemon1DDelta"] = env.GetValue("Histogram.1D.DaemonDelta.NofBins",1000);
    fRangeLow["Daemon1DDelta"] = env.GetValue("Histogram.1D.DaemonDelta.RangeLow.ns", -50);
    fRangeHigh["Daemon1DDelta"] = env.GetValue("Histogram.1D.DaemonDelta.RangeHigh.ns", 50);
    
    fNofBins["Daemon1DCoin"] = env.GetValue("Histogram.1D.DaemonDelta.NofBins",10000);
    fRangeLow["Daemon1DCoin"] = env.GetValue("Histogram.1D.DaemonDelta.RangeLow.ns", -5);
    fRangeHigh["Daemon1DCoin"] = env.GetValue("Histogram.1D.DaemonDelta.RangeHigh.ns", 5);
    
    fNofBins["Daemon1DDeltaPos"] = env.GetValue("Histogram.1D.DaemonDeltaPos.NofBins",100);
    fRangeLow["Daemon1DDeltaPos"] = env.GetValue("Histogram.1D.DaemonDeltaPos.RangeLow.cm.deg", -50);
    fRangeHigh["Daemon1DDeltaPos"] = env.GetValue("Histogram.1D.DaemonDeltaPos.RangeHigh.cm.deg", 50);
    
    fNofBins["Daemon1DDeltaPos"] = env.GetValue("Histogram.1D.DaemonDeltaPos.NofBins",100);
    fRangeLow["Daemon1DDeltaPos"] = env.GetValue("Histogram.1D.DaemonDeltaPos.RangeLow.cm", -50);
    fRangeHigh["Daemon1DDeltaPos"] = env.GetValue("Histogram.1D.DaemonDeltaPos.RangeHigh.cm", 50);
    
    fNofBins["Daemon2D"] = env.GetValue("Histogram.2D.Daemon.NofBins",5000);
    fRangeLow["Daemon2D"] = env.GetValue("Histogram.2D.Daemon.RangeLow.keV",0);
    fRangeHigh["Daemon2D"] = env.GetValue("Histogram.2D.Daemon.RangeHigh.keV",1000);
    
    fNofBins["Daemon1DExtra"] = env.GetValue("Histogram.1D.DaemonExtra.NofBins",30);
    fRangeLow["Daemon1DExtra"] = env.GetValue("Histogram.1D.DaemonExtra.RangeLow.ns",0);
    fRangeHigh["Daemon1DExtra"] = env.GetValue("Histogram.1D.DaemonExtra.RangeHigh.ns", 30);
    
    fNofBins["ZDS1Dns"] = env.GetValue("Histogram.1D.ZDS.NofBins",2010);
    fRangeLow["ZDS1Dns"] = env.GetValue("Histogram.1D.ZDS.RangeLow.ns", -10);
    fRangeHigh["ZDS1Dns"] = env.GetValue("Histogram.1D.ZDS.RangeHigh.ns", 2000);

    fNofBins["0RES_Griffin1D"] = env.GetValue("Histogram.1D.Griffin.NofBins",4096);
    fRangeLow["0RES_Griffin1D"] = env.GetValue("Histogram.1D.Griffin.RangeLow.keV",0.5);
    fRangeHigh["0RES_Griffin1D"] = env.GetValue("Histogram.1D.Griffin.RangeHigh.keV",4096.5);

    fNofBins["Griffin2D"] = env.GetValue("Histogram.2D.Griffin.NofBins",4096);
    fRangeLow["Griffin2D"] = env.GetValue("Histogram.2D.Griffin.RangeLow.keV",0.5);
    fRangeHigh["Griffin2D"] = env.GetValue("Histogram.2D.Griffin.RangeHigh.keV",4096.5);

    fNofBins["0RES_Griffin2D"] = env.GetValue("Histogram.2D.Griffin.NofBins",4096);
    fRangeLow["0RES_Griffin2D"] = env.GetValue("Histogram.2D.Griffin.RangeLow.keV",0.5);
    fRangeHigh["0RES_Griffin2D"] = env.GetValue("Histogram.2D.Griffin.RangeHigh.keV",4096.5);

    //fNofBins["Griffin3D"] = env.GetValue("Histogram.3D.Griffin.NofBins",500);
    //fRangeLow["Griffin3D"] = env.GetValue("Histogram.3D.Griffin.RangeLow.keV",0.5);
   // fRangeHigh["Griffin3D"] = env.GetValue("Histogram.3D.Griffin.RangeHigh.keV",500.5);
        
    fNofBins["GriffinND"] = env.GetValue("Histogram.ND.Griffin.NofBins",500);
    fRangeLow["GriffinND"] = env.GetValue("Histogram.ND.Griffin.RangeLow.keV",0.5);
    fRangeHigh["GriffinND"] = env.GetValue("Histogram.ND.Griffin.RangeHigh.keV",500.5);

    fNofBins["Descant1D"] = env.GetValue("Histogram.1D.Descant.NofBins",4096);
    fRangeLow["Descant1D"] = env.GetValue("Histogram.1D.Descant.RangeLow.keV",0.5);
    fRangeHigh["Descant1D"] = env.GetValue("Histogram.1D.Descant.RangeHigh.keV",4096.5);

    fNofBins["0RES_Descant1D"] = env.GetValue("Histogram.1D.Descant.NofBins",4096);
    fRangeLow["0RES_Descant1D"] = env.GetValue("Histogram.1D.Descant.RangeLow.keV",0.5);
    fRangeHigh["0RES_Descant1D"] = env.GetValue("Histogram.1D.Descant.RangeHigh.keV",4096.5);

}
