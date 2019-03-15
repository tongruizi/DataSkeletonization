double EPS_compare = 0.0000001;

#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include "ExponentialDensity.h"
#include "LinearDensity.h"
#include "FunctionEvaluator.h"
#include <mlpack/core.hpp>
#include <mlpack/methods/neighbor_search/neighbor_search.hpp>
#include <mlpack/methods/emst/dtb.hpp>
#include "DensityComputator.h"
#include "GeneralConvertor.h"
#include "NaiveMethods.h"
#include "DensityEstimationRules.h"
#include "TreeExperements.h"
#include <mlpack/core/tree/statistic.hpp>
#include "AMSTComputator.h"
#include <ctime>
#include "TestPerformer.h"
#include <cstdlib>
#include "GradientDescendTester.h"
//! Mapper and alphareeb includes:
#include "AlphaReeb_Launcher.h"
#include "CorrectEndTypeMeasure.h"
#include "ExplicitMeasurer.h"
#include "AbstractMeasurer.h"
#include "Mapper_Launcher.h"

#include "SingleStar.h"
#include "ClassicDistanceMeasure.h"
#include "controller.h"
#include "PrintToFile.h"
#include "NumberOfVertexMeasure.h"
#include "CorrectTypeMeasure.h"
#include "AsKLauncher.h"
#include "DoubleStar.h"

#include <boost/filesystem.hpp>
#include "RealCloudCollection.h"
#include "FastMSTLauncher.h"
#include "DualTreeDistanceMeasure.h"
#include "MeanSquareDistanceMeasure.h"
#include "DumbAlgorithm.h"
#include "CloudTypePrinterAlgorithm.h"
#include "SophisticatedPrinter.h"
#include "AmstLauncher.h"
#include "SegmentDistance.h"

#include "MorseLauncher.h"
#include "MetricGraphRec/MetricRec.hpp"




// Convenience.
using namespace mlpack;
using namespace mlpack::neighbor;
using namespace mlpack::metric;
// Convenience.

using namespace std;


void Tests1()
{

}


void Tests2()
{
    arma::mat data;
    data::Load("data.csv", data, true);
    arma::colvec vector0(data.col(0));
    std::cout << vector0 << std::endl;
    arma::colvec vector1(data.col(1));
    std::cout << vector1 << std::endl;
    double sdd = metric::EuclideanDistance::Evaluate(data.col(0), data.col(1));
    std::cout << "Their Euclidean distance: " << sdd << std::endl;


}

void Tests3()
{
    std::cout << "Testing O(N^2) implementation of simple density estimation function: " << std::endl;
    arma::mat data;
    data::Load("data2.csv", data, true);
    std::cout << "ColSize: " << data.n_cols << std::endl;
    std::vector<double> SumVector(data.n_cols);
    for (int i = 0; i < data.n_cols; i++)
    {
        for (int j = 0; j < data.n_cols; j++)
        {
            SumVector[i] = SumVector[i] + ExponentialDensity::Evaluate(metric::EuclideanDistance::Evaluate(data.col(i), data.col(j)));
        }
    }
    std::cout << "The following results were obtained: " << std::endl;
    for (int i = 0; i < data.n_cols ; i++)
    {
        std::cout << "Element " << i << " : " << SumVector[i] << std::endl;
    }

}

void Tests4()
{
    arma::mat data;
    data.set_size(2,3);
    data(0,0) = 1;
    data(0,1) = 2;
    data(0,2) = 3;
    data(1,0) = 4;
    data(1,1) = 5;
    data(1,2) = 6;
    std::cout << data << std::endl;

}
void Tests5()
{
    arma::mat data;
    GeneralConvertor::XYZtoMAT("/home/yury/Dropbox/MlPackTraining/KernelDensityEstimation/worm.xyz",data);
    data.save("Output.csv",arma::csv_ascii);
//std::cout << data << std::endl;

}

void Tests6()
{
    arma::mat data;
    GeneralConvertor::XYZtoMAT("/home/yury/Dropbox/MlPackTraining/KernelDensityEstimation/branched.xyz",data);
    std::vector<double> results;
    NaiveMethods::ComputeDensityNaiveRow<ExponentialDensity>(results,data);
    GeneralConvertor::MatInfoToFile("/home/yury/Dropbox/MlPackTraining/KernelDensityEstimation/outputs/branchedColoring.csv", data, results);
}

//typedef tree::KDTree<metric::EuclideanDistance> superTreeType;

void Tests7()
{
    std::vector<double> ww{0,1};
// DensityEstimationRules< metric::EuclideanDistance, arma::mat, ExponentialDensity , superTreeType > rulePackage(ww);
// rulePackage.TestMethodAdditionToResults(0, 1337);
    std::cout << ww[0] << std::endl;
    std::cout << "Compiled Succefully" << std::endl;
}

void Tests8()
{
    arma::mat data;
    TreeExperements exper;
    GeneralConvertor::XYZtoMAT("/home/yury/Dropbox/MlPackTraining/KernelDensityEstimation/branched.xyz",data);
    arma::mat cordata = data.t();
    exper.Test_Cover_Tree(cordata);
}
// template<typename MetricType,
//         typename MatType,
//         typename FunctionType,
//         template<typename TreeMetricType,
//                  typename TreeStatType,
//                  typename TreeMatType> class TreeType>

typedef mlpack::tree::CoverTree<metric::EuclideanDistance, mlpack::tree::EmptyStatistic,arma::mat> Treep;
typedef mlpack::tree::KDTree<metric::EuclideanDistance, mlpack::tree::EmptyStatistic,arma::mat> KdDefault;




void Test9()
{
    std::cout << "Computing the result both ways:" << std::endl;
//! Here we test the method:
    arma::mat data;
    TreeExperements exper;
    GeneralConvertor::XYZtoMAT("/home/yury/Dropbox/MlPackTraining/KernelDensityEstimation/branched.xyz",data);
    arma::mat cordata = data.t();
//! Testing method bruteforce way:

    mlpack::Timer::Start("Debug1");
    std::vector<double> results;
    NaiveMethods::ComputeDensityNaiveRow<ExponentialDensity>(results,data);
    GeneralConvertor::MatInfoToFile("/home/yury/Dropbox/MlPackTraining/KernelDensityEstimation/outputs/debug/brute.csv", data, results);
    mlpack::Timer::Stop("Debug1");


//! Testing method harder way:
    DensityComputator< metric::EuclideanDistance, arma::mat, ExponentialDensity,mlpack::tree::KDTree> DC(cordata);
    std::vector<double> SumVector(data.n_cols);
    std::vector<int> visitNumber(data.n_cols);
    double epsilon = 0.001;
    DC.ComputeDensity(SumVector, visitNumber, epsilon);
    GeneralConvertor::MatInfoToFile("/home/yury/Dropbox/MlPackTraining/KernelDensityEstimation/outputs/debug/cover.csv", data, SumVector);
    GeneralConvertor::VectorToFile("/home/yury/Dropbox/MlPackTraining/KernelDensityEstimation/outputs/debug/coverDebug.csv", visitNumber );

    auto tt =  mlpack::Timer::Get("Debug1");
    std::cout << "Time for brute: " << tt.count() << std::endl;
    std::cout << "Time for effective computation: " << mlpack::Timer::Get("KDE/Computation").count() << std::endl;

}

void MSTTest()
{
    arma::mat data;
    GeneralConvertor::XYZtoMAT("/home/yury/Dropbox/MlPackTraining/KernelDensityEstimation/branched.xyz",data);
    arma::mat cordata = data.t();
    mlpack::emst::DualTreeBoruvka<> MSTOP(cordata);
    arma::mat results;
    MSTOP.ComputeMST(results);
    GeneralConvertor::MSTToVTK(cordata,results, "/home/yury/Dropbox/MlPackTraining/KernelDensityEstimation/outputs/emst/out.vtk");

}

void AMSTTest()
{
    arma::mat data;
    GeneralConvertor::XYZtoMAT("/home/yury/Dropbox/Projects/BranchPointFind/Data/branched.xyz",data);
    arma::mat cordata = data.t();
    double epsilon = 0.01;
    double t = 2;
    double epsilon2 = 4;
    arma::mat results;

//! The method:
    AMSTComputator<metric::EuclideanDistance, arma::mat, ExponentialDensity,mlpack::tree::KDTree> comp;
//comp.PerformAMSTComputation(cordata,results,epsilon,t);
    comp.PerformRangeAMSTComputation(cordata,results,epsilon,t, epsilon2);
    GeneralConvertor::MSTToVTK(cordata,results, "/home/yury/Dropbox/MlPackTraining/KernelDensityEstimation/outputs/amst/ComplicatedData/BranchedAMSTl4Fast.vtk");

}

void AMSTTest2()
{
    arma::mat data;
    GeneralConvertor::XYZtoMAT("/home/yury/Dropbox/MlPackTraining/KernelDensityEstimation/branched.xyz",data);
    arma::mat cordata = data.t();
    double epsilon = 0.01;
    double t = 100;
    double epsilon2 = 2;
    arma::mat results;

//! The method:
    AMSTComputator<metric::EuclideanDistance, arma::mat, ExponentialDensity,mlpack::tree::KDTree> comp;
    comp.PerformAMSTComputation(cordata,results,epsilon,t);
//comp.PerformRangeAMSTComputation(cordata,results,epsilon,t, epsilon2);
//GeneralConvertor::MSTTakeymonkeyoVTK(cordata,results, "/home/yury/Dropbox/MlPackTraining/KernelDensityEstimation/outputs/amst/outAMST2.vtk");

}

void RunSeriousTests()
{
    std::string folder =  "/home/yury/Dropbox/Github/DataSkeletonizationNew/outputs/SyntheticalSkeletonization/SecondTest/";
    TestPerformer::RunTests(folder, 8, 50000, 100, M_PI/3,20,10,0.01,10);
}

void RunCyclicTests()
{
    std::string folder = "/home/yury/Dropbox/MlPackTraining/KernelDensityEstimation/outputs/amst/Cyclic3/";
    TestPerformer::RunCyclicTests(folder, 6000, 100, 20, 10, 0.01, 20);
}

void runGradientDescendTester()
{
    std::string folder = "/home/yury/Dropbox/Github/DataSkeletonizationNew/outputs/EdgeTest/First_Test/";
    GradientDescendTester::QuickTest(folder);
}

void TestNewAMSTTreeType()
{
    std::string folder = "/home/yury/Dropbox/Github/DataSkeletonizationNew/outputs/SyntheticalSkeletonization/TestNumberSix/";
    TestPerformer::RunTestsQuick(folder, 8, 20000, 100, M_PI/3,10,7,0.01,10);

}
//!
void MassiveConvertion()
{
    for (int i = 0; i <= 106; i++ )
    {
        std::string infolder = "/home/yury/Downloads/Cluster/";
        std::string outfolder = "/home/yury/Downloads/ClusterVTK/";
        infolder = infolder + "Cluster_Frame0000000.xyz";
        outfolder = outfolder + "out1.vtk";
        arma::mat data;
        GeneralConvertor::XYZtoMAT(infolder,data);
        arma::mat cordata = data.t();
        mlpack::emst::DualTreeBoruvka<> MSTOP(cordata);
        arma::mat results;
        MSTOP.ComputeMST(results);
        GeneralConvertor::MSTToVTK(cordata,results, outfolder);
    }
}

void TestAlphaReebAndMapperOnceAgain()
{
//GeneralConvertor::XYZtoMAT("/home/yury/Dropbox/MlPackTraining/KernelDensityEstimation/branched.xyz",data);
    Mapper_Parameters param(15, 0.5, "Distance", 3.0,3.0);
    AlphaReeb_Parameters AlphaParam(20, 1);

//! we are too lazy to actually test this at the moment, what could possibly go wrong?


}

void TestAbstractThings()
{
//    MyGraphType G;
//    CorrectEndTypeMeasure A(2);
//    std::cout << A.returnStatisticString() << std::endl;
//    std::vector<ExplicitMeasurer*> m1;
//    m1.push_back(&A);
//    std::cout << "The string is: " << m1[0] -> returnStatisticString() << std::endl;


}

void MapperWorkingTest()
{
//    int k = 3;
//    int minangle = M_PI/3;
//    int scale = 100;
//    int n = 1500;
//    double epsilon = 5;
//    std::list<Point> cloud;
//    MyGraphType G;
//    GraphGeneration::RandomGraph1(k,minangle,scale,G);
//    CloudGenerator::generatePoints(n, G, epsilon, cloud);
//    double mappercluster = 1.75;
//    Mapper_Parameters param(15, 0.5, "Distance", mappercluster,mappercluster);
//    Mapper_Launcher thelaunch(param);
//    MyGraphType out;
//    thelaunch.Run(cloud,out);
//    std::string filepath = "/home/yury/Dropbox/Github/DataSkeletonizationNew/outputs/SyntheticalSkeletonization/MapperTest/out.vtk";
//    GeneralConvertor::GraphToVtk(filepath,out);
//
//    ClassicDistanceMeasure p(3);
//    p.resetStatistic(1);
//    std::cout << "Before run" << std::endl;
//
//    std::cout << "After run" << std::endl;
//    std::cout << "Error: " << p.returnStatisticString(0) << std::endl;

}


void PrecisionTest()
{
    double pi = 3.14159265359;
    stringstream stream;
    stream << fixed << setprecision(2) << pi;
    string s = stream.str();
    std::cout << s << std::endl;
}
void MlPackTimerTest()
{
    mlpack::Timer::Start("Debug1");
    std::vector<int> w;
    for (int i = 0; i < 100000; i++)
    {
        w.push_back(i);
    }
    mlpack::Timer::Stop("Debug1");
    mlpack::Timer::Start("Debug2");
    for (int i = 0; i < 100000; i++)
    {
        w.push_back(i);
    }
    mlpack::Timer::Stop("Debug2");
    auto sum = mlpack::Timer::Get("Debug1") + mlpack::Timer::Get("Debug2");
    long duration = sum.count();
    std::cout << duration << std::endl;

}
void ControllerTest()
{
    std::string qq = "/home/yury/LocalTests/Test1/data.csv";
    std::string folder = "/home/yury/LocalTests/Test1/Outputs/";
    double mappercluster = 1.75; // 1.75
    double alpha = 20;
//! We initilize a star:
    SingleStar star1(M_PI/3,3,1500,5,100,5,"Star3");
    SingleStar star2(M_PI/3,4,2000,5,100,5,"Star4");
    SingleStar star8(M_PI/6,8,4000,5,100,1,"Star8");
    DoubleStar dstar(M_PI/3,4,4,4000,5,100,10,"DoubleStar");

    // RealCloudCollection theRealClouds("Real","/home/yury/Dropbox/UnileverData/XYZ_Files/");
    //theRealClouds.SetCorrectnessOfGraphs("/home/yury/Dropbox/UnileverData/titles.txt");
//RealCloudCollection theRealClouds("Real","/home/yury/Dropbox/UnileverData/XYZ_Files/");
//SingleStar star2(M_PI/3,4,100,1500,5,100,10,"Star4");
//! We initilize filewriter:
    PrintToFile printer(folder);
//! We initilize mapper:
    Mapper_Parameters param(15, 0.5, "Distance", mappercluster,mappercluster);
    Mapper_Launcher thelaunch(param);
    AlphaReeb_Parameters AlphaParam(alpha, 1);
    AlphaReeb_Launcher alphaLaunch(AlphaParam,10);
    thelaunch.setTimePrecision(2);
    alphaLaunch.setTimePrecision(2);
    std::string setting = "sd";
    //  AsKLauncher AskAlgorithm(2.0,1.3,1.3,setting,"AsK");
    AsKLauncher AskAlgorithm(20.0,1.3,1.3,"MSTAVG","AsKMsTAvG");
    AskAlgorithm.setTimePrecision(3);

    //  AskAlgorithm.addPostRunner(&printer);
//  thelaunch.addPostRunner(&printer);
    //  alphaLaunch.addPostRunner(&printer);

    //! Add AMST:

    AmstLauncher lwp(0.01,1,4,15.0);
    lwp.setTimePrecision(3);
    lwp.addPostRunner(&printer);

//! Add MST

    FastMSTLauncher mstComputator;
    mstComputator.setTimePrecision(3);
    mstComputator.addPostRunner(&printer);

//! We initilize controller:
    controller control(qq);
//! We add algorithm, star to controller
//   void addAlgorithm(AbstractAlgorithm* k);
//   void addCloud(generatable* k);
    //control.addAlgorithm(&thelaunch);
    // control.addAlgorithm(&alphaLaunch);
    // control.addAlgorithm(&AskAlgorithm);
    control.addAlgorithm(&mstComputator);
// control.addAlgorithm(&lwp);
//control.addCloud(&star1);
//control.addCloud(&star2);
    control.addCloud(&star8);
//control.addCloud(&theRealClouds);
//control.addCloud(&dstar);
//control.addCloud(&star2);
//control.addCloud(&theRealClouds);
//! Initilize distance error measure:
    ClassicDistanceMeasure distanceMeasure(2);
    CorrectEndTypeMeasure endTypeMeasure(2);
    NumberOfVertexMeasure vertexMeasure(2);
    CorrectTypeMeasure TypeMeasure(2);
    DualTreeDistanceMeasure newDistanceMeasure(2);
    MeanSquareDistanceMeasure ndm(2);

    control.addMeasurer(distanceMeasure);
    control.addMeasurer(endTypeMeasure);
    control.addMeasurer(vertexMeasure);
    control.addMeasurer(TypeMeasure);
    control.addMeasurer(newDistanceMeasure);
    // control.addMeasurer(ndm);
    // control.addMeasurer(newDistanceMeasure);
    control.BeginTestRun();

}

void FileSystemTest()
{
//std::string p = "/home/yury/Dropbox/UnileverData/VTK_First_Files/";
    boost::filesystem::path p("/home/yury/Dropbox/UnileverData/XYZ_Files/");
    std::vector<boost::filesystem::directory_entry> v; // To save the file names in a vector.

    if(boost::filesystem::is_directory(p))
    {
        copy(boost::filesystem::directory_iterator(p), boost::filesystem::directory_iterator(), back_inserter(v));
        std::cout << p << " is a directory containing:\n";
        std::sort(v.begin(),v.end());
        for ( std::vector<boost::filesystem::directory_entry>::const_iterator it = v.begin(); it != v.end();  ++ it )
        {
            std::cout<< (*it).path().string()<<endl;
        }
    }

}

void ControllerTestRealDataSimple()
{
//! Defining main algorithm parameters:
    double mappercluster = 3.0; // 1.75
    double alpha = 20;

//! Defining all required file paths:
    std::string CSVFile = "/home/yury/Dropbox/UnileverData/FirstTestOfInterface/data2.csv";
    std::string Outputfolder = "/home/yury/Dropbox/UnileverData/FirstTestOfInterface/Outputs2/";
    std::string Inputfolder = "/home/yury/Dropbox/UnileverData/FirstTestOfInterface/SecondClusters/";
    std::string ManualGraphInfoFile = "/home/yury/Dropbox/UnileverData/FirstTestOfInterface/StarInfo2.txt";


//! Initilizing RealCloudCollection
    RealCloudCollection theRealClouds("Real",Inputfolder);
    std::cout << "Initilized RealCloudCollection" << std::endl;
    theRealClouds.SetCorrectnessOfGraphs(ManualGraphInfoFile);
    std::cout << "Succesfully imputed file " << std::endl;

    std::cout << "Initilization of RealCloudCollection succeful" << std::endl;

//! Initilizing printer:
    PrintToFile printer(Outputfolder);


//! Initilizing Mapper Algorithm
    Mapper_Parameters param(15, 0.5, "Distance", mappercluster,mappercluster);
    Mapper_Launcher MapperAlgorithm(param);
    MapperAlgorithm.setTimePrecision(2);
    MapperAlgorithm.addPostRunner(&printer);

//! Initilizing AsK Algorithm
    std::string setting = "pure";
    AsKLauncher AskAlgorithm(50.0,1.05,1.5,setting,"AsK");
    AskAlgorithm.setTimePrecision(2);
    AskAlgorithm.addPostRunner(&printer);

//! Initilize MST
    FastMSTLauncher mstComputator;
    mstComputator.setTimePrecision(2);
    mstComputator.addPostRunner(&printer);

//! Initilizing the controller:

    controller control(CSVFile);
    control.addCloud(&theRealClouds);
//    control.addAlgorithm(&MapperAlgorithm);
    control.addAlgorithm(&mstComputator);
    control.addAlgorithm(&AskAlgorithm);


//! Initilizing measurers:

    ClassicDistanceMeasure distanceMeasure(2);
    CorrectEndTypeMeasure endTypeMeasure(2);
    NumberOfVertexMeasure vertexMeasure(2);
    CorrectTypeMeasure TypeMeasure(2);

//! Adding measurers

    control.addMeasurer(distanceMeasure);
    control.addMeasurer(endTypeMeasure);
    control.addMeasurer(vertexMeasure);
    control.addMeasurer(TypeMeasure);

//! Run the boy
    control.BeginTestRun();

}

void DistanceBetweenLineSegments()
{
    Segment l(Point(0,0,10), Point(1,0,10));
    Segment q(Point(0,1,0), Point(0,1,0));
    std::cout << CGAL::squared_distance(l, q) << std::endl;

}

void PrintingStarCloudsTest()
{
    DumbAlgorithm pwee;
    SophisticatedPrinter p("/home/yury/LocalTests/TestOnSynthetical/");
    pwee.addPostRunner(&p);
    SingleStar star3(M_PI/3,3,1500,5,100,100,"Star3");
    SingleStar star4(M_PI/3,4,2000,5,100,100,"Star4");
    SingleStar star5(M_PI/3,5,2500,5,100,100,"Star5");
    SingleStar star6(M_PI/6,6,3000,5,100,100,"Star6");
    SingleStar star7(M_PI/3,7,3500,5,100,100,"Star7");
    SingleStar star8(M_PI/3,8,4000,5,100,100,"Star8");
    std::vector<CloudTypePrinterAlgorithm*> q;
    CloudTypePrinterAlgorithm n3("/home/yury/LocalTests/TestOnSynthetical/TheBosses/Star3Info.txt");
    CloudTypePrinterAlgorithm n4("/home/yury/LocalTests/TestOnSynthetical/TheBosses/Star4Info.txt");
    CloudTypePrinterAlgorithm n5("/home/yury/LocalTests/TestOnSynthetical/TheBosses/Star5Info.txt");
    CloudTypePrinterAlgorithm n6("/home/yury/LocalTests/TestOnSynthetical/TheBosses/Star6Info.txt");
    CloudTypePrinterAlgorithm n7("/home/yury/LocalTests/TestOnSynthetical/TheBosses/Star7Info.txt");
    CloudTypePrinterAlgorithm n8("/home/yury/LocalTests/TestOnSynthetical/TheBosses/Star8Info.txt");
    q.push_back(&n3);
    q.push_back(&n4);
    q.push_back(&n5);
    q.push_back(&n6);
    q.push_back(&n7);
    q.push_back(&n8);
    controller control("/home/yury/LocalTests/TestOnSynthetical/dummyfile.txt");
    control.addAlgorithm(&pwee);
    control.addCloud(&star3);
    control.addCloud(&star4);
    control.addCloud(&star5);
    control.addCloud(&star6);
    control.addCloud(&star7);
    control.addCloud(&star8);
    control.BeginTestRun();
    control.FlushClouds(q);

//#include "CloudTypePrinterAlgorithm.h"



}
//

void ControllerTest1337()
{
    std::string qq = "/home/yury/LocalTests/ControllerTest0/data.csv";
    std::string folder = "/home/yury/LocalTests/ControllerTest0/Outputs/";
//! We initilize a star:
    SingleStar star8(M_PI/6,8,4000,5,100,1,"Star8");


//! We initilize filewriter:
    PrintToFile printer(folder);

// int proportion, double densityE, double parC
    MorseLauncher morseAlgorithm(10,0.01, 0.10);
    morseAlgorithm.setTimePrecision(3);
    morseAlgorithm.addPostRunner(&printer);



//! Add MST
//! Initilize MST
    FastMSTLauncher mstComputator;
    mstComputator.setTimePrecision(2);
    mstComputator.addPostRunner(&printer);

//! We initilize controller:
    controller control(qq);
//! We add algorithm, star to controller
//   void addAlgorithm(AbstractAlgorithm* k);
//   void addCloud(generatable* k);
    //control.addAlgorithm(&thelaunch);
    // control.addAlgorithm(&alphaLaunch);
    // control.addAlgorithm(&AskAlgorithm);
    control.addAlgorithm(&morseAlgorithm);
    control.addAlgorithm(&mstComputator);
// control.addAlgorithm(&lwp);
//control.addCloud(&star1);
//control.addCloud(&star2);
    control.addCloud(&star8);
//control.addCloud(&theRealClouds);
//control.addCloud(&dstar);
//control.addCloud(&star2);
//control.addCloud(&theRealClouds);
//! Initilize distance error measure:
    ClassicDistanceMeasure distanceMeasure(2);
    CorrectEndTypeMeasure endTypeMeasure(2);
    NumberOfVertexMeasure vertexMeasure(2);
    CorrectTypeMeasure TypeMeasure(2);
    DualTreeDistanceMeasure newDistanceMeasure(2);
    MeanSquareDistanceMeasure ndm(2);

    control.addMeasurer(distanceMeasure);
    control.addMeasurer(endTypeMeasure);
    control.addMeasurer(vertexMeasure);
    control.addMeasurer(TypeMeasure);
    // control.addMeasurer(ndm);
    // control.addMeasurer(newDistanceMeasure);
    control.BeginTestRun();




}

void NewCoverTreeTree()
{
    using namespace mlpack;
    using namespace mlpack::neighbor; // NeighborSearch and NearestNeighborSort
    using namespace mlpack::metric;
    // Load the data from data.csv (hard-coded).  Use CLI for simple command-line
    // parameter handling.
    arma::mat referencedata;
    std::vector<Segment> segments;
    for (int i = 0; i < 10000; i++)
    {
        segments.push_back(Segment(Point(0,0,i),Point(0,0,i+1)));
    }

    GeneralConvertor::SegmentsToMat(segments,referencedata);
    arma::mat querydata;
    std::vector<Segment> segmentPoints;
    for (int j = 0; j < 10001; j++)
    {
        segmentPoints.push_back(Segment(Point(0,0,j),Point(0,0,j)));
    }

    GeneralConvertor::SegmentsToMat(segmentPoints,querydata);
//   data::Load("data.csv", data, true);
    // Use templates to specify that we want a NeighborSearch object which uses
    // the Manhattan distance.
    //  NeighborSearch<NearestNeighborSort, ManhattanDistance> nn(data);
    mlpack::neighbor::NeighborSearch<NearestNeighborSort,SegmentDistance,arma::mat,mlpack::tree::StandardCoverTree > nn(referencedata);

    // Create the object we will store the nearest neighbors in.
    arma::Mat<size_t> neighbors;
    arma::mat distances; // We need to store the distance too.
    // Compute the neighbors.
    nn.Search(querydata,1, neighbors, distances);
    // Write each neighbor and distance using Log.
    for (size_t i = 0; i < neighbors.n_elem; ++i)
    {
        if (distances[i] != 0)
        {
            std::cout << "Nearest neighbor of point " << i << " is segment"
                      << neighbors[i] << " and the distance is " << distances[i] << ".\n";
        }
    }
    //  std::cout << "Distancedebug: " << sqrt(CGAL::squared_distance(Segment[2],Point(0,10,10))) << std::endl;
//   double d = sqrt(CGAL::squared_distance(segments[2],Point(0,10,10))) ;
//   std::cout << d << std::endl;
//  std::cout << "Extra point" << std::endl;
}


void DebugMetricRec()
{
    std::string pathin = "/home/yury/Dropbox/Skeletonization Project/OldFolders/unileverdata/XYZ_Files/Cluster_Frame00000000.xyz";
    std::list<Point> points;
    GeneralConvertor::XYZtoPoint(pathin,points);
    MetricRec rec(8);
    MyGraphType G;
    rec.Run(points,G);
    std::string pathout = "/home/yury/LocalTests/OutputMetricGraphRec/out.vtk";
    GeneralConvertor::GraphToVtk(pathout,G);





}

////! Try out Deluanay triangulation:
//
//void TryOutDeluanay()
//{
//Gudhi::Simplex_tree<> st;
//std::string in = "/home/yury/Dropbox/Skeletonization Project/OldFolders/UnileverData/XYZ_Files/Cluster_Frame00000001.xyz";
//std::string out = "/home/yury/LocalTests/Test2Deluanay/product.vtk";
//std::string coloringout = "/home/yury/LocalTests/Test2Deluanay/productColoring2.csv";
//std::list<Point> listpoints;
//GeneralConvertor::XYZtoPoint(in,listpoints);
//std::cout << "Size of listpoints: " << listpoints.size() << std::endl;
//std::vector<Point>  points(listpoints.begin(),listpoints.end());
//double clusterEpsilon = 2;
//double fepsilon = 0.001;
//MyGraphType G;
//ClusterPersistence<ExponentialDensity> UltimateComputator;
////     void Run(std::vector<Point> & points, double fEpsilon, double clusterEpsilon, MyGraphType & G, std::string colorout)
//
//UltimateComputator.Run(points,fepsilon,clusterEpsilon, G,coloringout,st);
//
//HomologyComputator::ComputeOriginal(st,2);
////! Add this if you want printing on
////GeneralConvertor::GraphToVtk(out,G);
//}
//
//void TryOutDeluanayCyclicTriangle()
//{
//std::string coloringout = "/home/yury/LocalTests/Test2Deluanay/productColoring1337.csv";
//Gudhi::Simplex_tree<> st;
//MyGraphType T;
//GraphGeneration::TriangleGraph(T, 100);
//std::list<Point> listpoints;
//CloudGenerator::generatePoints(10000,T,5.0,listpoints);
//std::vector<Point>  points(listpoints.begin(),listpoints.end());
//double clusterEpsilon = 7;
//double fepsilon = 0.001;
//MyGraphType G;
//ClusterPersistence<ExponentialDensity> UltimateComputator;
//UltimateComputator.Run(points,fepsilon,clusterEpsilon, G,coloringout,st);
//HomologyComputator::ComputeOriginal(st,2);
//

//}

//}
//void Run(std::list<Point> & p, MyGraphType & G)

int main()
{
//Tests8();
//Test9();
//MSTTest();
//AMSTTest();
//AMSTTest();

//! This is required, to get proper random number sequence
//   srand( time( NULL ) );
    //  ControllerTest();

//NewCoverTreeTree();
///! We use this number sequence to debug the code:
//srand(128);
//std::cout <<rand()::numeric_limit<unit>::min(); << std::endl;ComputeDeluanayTriangulation(MyGraphType & G, std::list<Point> & Vector)
//! Here we test:ControllerTest()
//runGradientDescendTester();
//RunSeriousTests();
//RunCyclicTests();
//TestNewAMSTTreeType();
//  MassiveConvertion();
// TestNewAMSTTreeType();
//    TestAbstractThings();
//MapperWorkingTest();
//PrecisionTest();
//   MlPackTimerTest();
//ControllerTest();
//ControllerTest();
    // std::cout << "Compilation succeful" << std::endl;
    // std::cout << "one more thing" << std::endl;
    //  std::cout << "Bug fixed, actually" << std::endl;
    //  FileSystemTest();
// ControllerTestRealDataSimple();
//  ControllerTest();
    // std::cout << "Succeful compilation xD" << std::endl;
//ControllerTestRealDataSimple();

    // ControllerTest();
//   TryOutDeluanay();
    //  TryOutDeluanayCyclicTriangle();
// ControllerTest1337();
    DebugMetricRec();
    std::cout << "Mlpackversion: " << mlpack::util::GetVersion() << std::endl;
    std::cout << "Compilation succeful" << std::endl;
    //  std::cout << "Compilation succeful" << std::endl;
//  PrintingStarCloudsTest();
//  PrintingStarCloudsTest();
    //  DistanceBetweenLineSegments();
//  ControllerTestRealDataSimple();
}
