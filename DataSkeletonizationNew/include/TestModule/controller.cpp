#include "controller.h"
#include "generatable.h"
#include <thread>
#define THREADS 7;

controller::controller()
{
}

void letsmesure(MyGraphType & G,std::vector<ExplicitMeasurer*> measurers )
{

    for (auto MR = measurers.begin(); MR != measurers.end(); MR++)
    {

        std::string returnStatisticData();


    }



}

//! THIS IS HOW IT IS SUPPOSED TO LOOK LIKE. NOW IMPLEMENT STEP 1 AND STEP 2
void BeginTestRun(std::vector<AbstractAlgorithm> algorithms,std::vector<generatable> ACT)
{
    for (auto Algo = algorithms.begin(); Algo!= algorithms.end(); Algo++)
    {
        for (auto Cloudit = ACT.begin(); Cloudit != ACT.end(); Cloudit++)
        {

            //! Step 1: Generate cloud
            //i presume this method can be used here
            std::list<Point> & points;
            Cloudit->GenerateCloud(points);

            //! Step 2: Run Algorithm
            MyGraphType out;
            Algo->Run(points, out);

            //! Step 3: Do measurments: (I will add this later)
            std::vector<ExplicitMeasurer*> measurers;



            letsmesure(out, measurers);
        }

    }

}

void addAlgorithm(AbstractAlgorithm & k,std::vector<AbstractAlgorithm> algorithms)
{
    algorithms.push_back(k);
}
void addCloud(generatable & k,std::vector<generatable> ACT)
{
    ACT.push_back(k);
}


void runing(std::list<Point> & cloud)
{

//! We dont add threads before this $^&$ is running without them and when we add it,
//! Then THREADS WILL BE A VARIABLE DECLARED IN THE CLASS HEADER !!!!!!! !!!!!!! !!!!!!!!!


}




