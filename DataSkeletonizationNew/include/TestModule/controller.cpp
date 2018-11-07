#include "controller.h"
#include "generatable.h"
#include <thread>
#include "Definitions.h"
//#define THREADS 7;

controller::controller(int msize):msize(msize)
{
}

void controller::InitilizeResultsCube()
{
    results = std::vector<std::vector<std::vector<std::string>>>(ACT.size(), std::vector<std::vector<std::string>>(algorithms.size(), std::vector<std::string>(msize,"")));
}
//
//void controller::LoopOverMeasurers(MyGraphType & G, int i, int j, std::list<Point> & cloud)
//{
//
//    //! set size of Information vector
//    for (int k = 0; k < measurers.size(); k++)
//    {
//
//      (*measurers[k]).run(j, G ,ACT[i],&cloud);
//
//    }
//
//}

//void controller::InitilizeAllMeasurments()
//{
//
//    for (int k = 0; k < measurers.size(); k++)
//    {
//    measurers[k] ->resetStatistic(algorithms.size());
//    }
//
////    for (auto MR = measurers.begin(); MR != measurers.end(); MR++)
////    {
////        (*MR)->resetStatistic(algorithms.size());
////        // (*MR)->setCloud(cloud);
////        //   std::string returnStatisticData();
////    }
//
//}

void controller::InsideCloudListLoop(int i, int clit)
{
    std::list<Point> points;
    ACT[i]->GenerateCloud(points);

    for (int j = 0; j < algorithms.size(); j++)
    {
        //! Step 2: Run Algorithm
        MyGraphType out;
        algorithms[j]->Run(points, out);

        //! Step 3: Do measurments:

        algorithms[j]->CycleOverMeasurers(out,ACT[i], &points);
    }

}

void controller::LoopOverCloudList(int i)
{
//! Section below will be rewritten for multi threading application. Idea would be that we would allocate

    for (int clit = 0; clit < (*ACT[i]).returnNumberOfRuns(); clit++ )
    {

        //i presume this method can be used here
        //! The inside function is written as separate instance, so we can launch threads involving this
        this->InsideCloudListLoop(i,clit);



    }
    //! If this will be threading application, then we will wait here for all proccesses to halt and then write down the results.
    //! Step 4 Write down results. Reset each measurer
    for (int j = 0; j < algorithms.size(); j++)
    {
        std::vector<std::string> rvector;
        algorithms[j] -> WriteResults(rvector);
        results[i][j] = rvector;

        //! Here we reset it
        algorithms[j] -> ResetAllMeasurers();
    }

}

void controller::BeginTestRun()
{
    this->InitilizeResultsCube();
    for (int i = 0; i < ACT.size(); i++)
    {
        //this->InitilizeAllMeasurments();
        this->LoopOverCloudList(i);
    }
    //! We will write everything into files

}

void controller::addAlgorithm(AbstractAlgorithm* k)
{
    algorithms.push_back(k);
}
void controller::addCloud(generatable* k)
{
    ACT.push_back(k);
}








