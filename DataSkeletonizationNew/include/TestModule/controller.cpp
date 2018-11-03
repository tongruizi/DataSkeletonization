#include "controller.h"
#include "generatable.h"
#include <thread>
#define THREADS 7;

controller::controller()
{
}

void letsmesure(MyGraphType & G)
{
    for (auto MR = measurers.begin(); MR != measurers.end(); MR++)
    {

        <unit>statistic.MR();


    }



}

//! THIS IS HOW IT IS SUPPOSED TO LOOK LIKE. NOW IMPLEMENT STEP 1 AND STEP 2
void BeginTestRun()
{
    for (auto Algorithmit = algorithms.begin(); Algoritmit != algorithms.end(); Algorithmit++)
    {
        for (auto Cloudit = ATC.begin(); Cloudit != ATC.end(); Cloudit++)
        {
            //! Step 1: Generate cloud
            //i presume this method can be used here
            Cloudit->GenerateCloud(std::list<Point> & p);
            //! Step 2: Run Algorithm
            Algorithmit->run(std::list<Point> & cloudlist, MyGraphType & out);
            //! Step 3: Do measurments: (I will add this later)
            letsmesure(MyGraphType & out);
        }

    }

}

void addAlgorithm(AbstractAlgorithm & k)
{
    algorithms.push_back(k);
}
void addCloud(generatable & k)
{
    ATC.push_back(k);
}


void runing(std::list<Point> & cloud)
{

//! We dont add threads before this $^&$ is running without them and when we add it,
//! Then THREADS WILL BE A VARIABLE DECLARED IN THE CLASS HEADER !!!!!!! !!!!!!! !!!!!!!!!


}




