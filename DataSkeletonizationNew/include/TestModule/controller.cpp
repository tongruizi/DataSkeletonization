#include "controller.h"
#include "generatable.h"
#include <thread>
#include "Definitions.h"
#define THREADS 7;

controller::controller()
{
}

void controller::LoopOverMeasurments(MyGraphType & G)
{

    for (auto MR = measurers.begin(); MR != measurers.end(); MR++)
    {
    //    std::string returnStatisticData();
    }



}

void controller::BeginTestRun()
{
    for (auto Algo = algorithms.begin(); Algo!= algorithms.end(); Algo++)
    {
        for (auto Cloudit = ACT.begin(); Cloudit != ACT.end(); Cloudit++)
        {

            //! Step 1: Generate cloud
            //i presume this method can be used here
            std::list<Point> points;
            (*Cloudit)->GenerateCloud(points);


            //! Step 2: Run Algorithm
            MyGraphType out;
            (*Algo)->Run(points, out);

            //! Step 3: Do measurments: (I will add this later)

            this->LoopOverMeasurments(out);
        }

    }

}

void controller::addAlgorithm(AbstractAlgorithm* k)
{
    algorithms.push_back(k);
}
void controller::addCloud(generatable* k)
{
    ACT.push_back(k);
}

//! For now does nothing...
void controller::WriteDownAndClear()
{

}






