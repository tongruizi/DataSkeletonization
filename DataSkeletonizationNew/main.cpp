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
#include "Mapper_Launcher.h"
#include "CorrectEndTypeMeasure.h"
#include "ExplicitMeasurer.h"
#include "AbstractMeasurer.h"
#include "Mapper_Launcher.h"

#include "SingleStar.h"
#include "ClassicDistanceMeasure.h"
#include "controller.h"
#include "PrintToFile.h"

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
std::string qq = "/home/liudi/gitHub/DataSkeletonization/DataSkeletonizationNew/outputs/ModuleTest/table.txt";
std::string folder = "/home/liudi/gitHub/DataSkeletonization/DataSkeletonizationNew/outputs/ModuleTest/outputs/";
double mappercluster = 1.75;
//! We initilize a star:
SingleStar star1(M_PI/3,3,100,1500,5,100,10,"Star3");
//SingleStar star2(M_PI/3,4,100,1500,5,100,10,"Star4");
//! We initilize filewriter:
PrintToFile printer(folder);
//! We initilize mapper:
Mapper_Parameters param(15, 0.5, "Distance", mappercluster,mappercluster);
Mapper_Launcher thelaunch(param);
thelaunch.addPostRunner(&printer);
//! We initilize controller:
controller control(qq);
//! We add algorithm, star to controller
//   void addAlgorithm(AbstractAlgorithm* k);
 //   void addCloud(generatable* k);
control.addAlgorithm(&thelaunch);
control.addCloud(&star1);
//control.addCloud(&star2);
//! Initilize distance error measure:
ClassicDistanceMeasure distanceMeasure(1);
control.addMeasurer(distanceMeasure);
control.BeginTestRun();

}


//void Run(std::list<Point> & p, MyGraphType & G)

int main()
{
//Tests8();
//Test9();
//MSTTest();
//AMSTTest();
//AMSTTest();

//! This is required, to get proper random number sequence
    srand( time( NULL ) );
//! We use this number sequence to debug the code:
//srand(20);
//std::cout <<rand()::numeric_limit<unit>::min(); << std::endl;ComputeDeluanayTriangulation(MyGraphType & G, std::list<Point> & Vector)
//! Here we test:
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
    std::cout << "Compilation succeful" << std::endl;
    //  std::cout << "Bug fixed, actually" << std::endl;
}
