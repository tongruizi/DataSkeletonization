#ifndef TESTPERFORMER_H
#define TESTPERFORMER_H

#include "AMSTComputator.h"
#include <mlpack/core.hpp>
#include "CloudGenerator.h"
#include "Computation.h"
#include "BranchDetection.h"
#include "GraphGeneration.h"


class TestPerformer
{
public:
    TestPerformer() {}

    static void RunTests(std::string & outFolder, int gn, int n, double scale, double minangle, int k, double epc, double epd, double epmst)
    {
        double t = 2;
        double timesumm = 0;
        //! The method:
        AMSTComputator<mlpack::metric::EuclideanDistance, arma::mat, ExponentialDensity,mlpack::tree::KDTree> comp;
        for (int i = 0; i < k; i++)
        {
            std::string numberI =  std::to_string(i);
            std::string outputName = "output" + numberI + ".vtk";
            std::string outputPath = outFolder + outputName;
            arma::mat cloud;
            arma::mat outputGraph;
            CloudGenerator::generatePointsStandartInArmaMat(gn, n,minangle,scale,epc,cloud);
            arma::mat trcloud = cloud.t();
            mlpack::Timer::Start("test/Computation1" + numberI);
            comp.PerformRangeAMSTComputation(trcloud,outputGraph,epd,t,epmst);
            mlpack::Timer::Stop("test/Computation1" + numberI);

            GeneralConvertor::MSTToVTK(trcloud,outputGraph, outputPath);
            auto gtm = mlpack::Timer::Get("test/Computation1" + numberI);
            long tmtm = gtm.count();
            timesumm = timesumm + tmtm;
            MyGraphType G;
            MyGraphType K;
            Computation::ArmaMatToGraph(G,outputGraph,trcloud);
            BranchDetection::SimplifyIt(G,K,50.0,"","pure");

            std::string ww = outFolder + "finaloutput" + numberI + ".vtk";
            GeneralConvertor::GraphToVtk(ww,K);

            std::cout << "Time for test " << i << " : " << tmtm << std::endl;

        }
        std::cout << "On AVERAGE: " << timesumm/k << std::endl;
    }
    static void RunCyclicTests(std::string & outFolder, int n, double scale, int k, double epc, double epd, double epmst)
    {
        double t = 2;
        double timesumm = 0;
                AMSTComputator<mlpack::metric::EuclideanDistance, arma::mat, ExponentialDensity,mlpack::tree::KDTree> comp;

        for (int i = 0; i < k; i++)
        {
            arma::mat cloud;
            MyGraphType A;
            std::list<Point> pointList;
            std::string numberI =  std::to_string(i);
            std::string outputName = "output" + numberI + ".vtk";
            std::string outputPath = outFolder + outputName;
            std::string outputPath2 = outFolder + "FinalOutput" + numberI + ".vtk";
            GraphGeneration::TriangleGraph(A, scale);
            CloudGenerator::generatePoints(n,A,epc,pointList);
            GeneralConvertor::ListToMat(pointList, cloud);

            arma::mat outputGraph;
            arma::mat trcloud = cloud.t();
            mlpack::Timer::Start("test/Computation1" + numberI);
            comp.PerformRangeAMSTComputation(trcloud,outputGraph,epd,t,epmst);
            mlpack::Timer::Stop("test/Computation1" + numberI);

            GeneralConvertor::MSTToVTK(trcloud,outputGraph, outputPath);
            auto gtm = mlpack::Timer::Get("test/Computation1" + numberI);
            long tmtm = gtm.count();
            timesumm = timesumm + tmtm;
            MyGraphType G;
            MyGraphType K;
            Computation::ArmaMatToGraph(G,outputGraph,trcloud);
            BranchDetection::SimplifyIt(G,K,50.0,"","pure");
            GeneralConvertor::GraphToVtk(outputPath2,K);

            std::cout << "Time for test " << i << " : " << tmtm << std::endl;

        }
        std::cout << "On AVERAGE: " << timesumm/k << std::endl;

    }

protected:

private:
};

#endif // TESTPERFORMER_H
