#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "AbstractAlgorithm.h"
#include "generatable.h"
#include "AbstractMeasurer.h"
#include "ExplicitMeasurer.h"

//void controller::InsideCloudListLoop(int i, int clit)

//void controller::LoopOverCloudList(int i)

class controller
{
public:
    controller(int msize);
    void InitilizeResultsCube();
  //  void LoopOverMeasurers(MyGraphType & G, int i, int j, std::list<Point> & cloud);
  //  void InitilizeAllMeasurments();
    void InsideCloudListLoop(int i, int clit);
    void LoopOverCloudList(int i);
    void BeginTestRun();

    void addAlgorithm(AbstractAlgorithm* k);
    void addCloud(generatable* k);
    //void addMeasurer()
protected:

private:
    int msize;
    //! Vector for cloudtypes:
    std::vector<generatable*> ACT;
    //! Vector for algorithmtypes:
    std::vector<AbstractAlgorithm*> algorithms;
    //! Vector for measurers:

    //! Table of results in std::string format
    std::vector<std::vector<std::vector<std::string>>> results;
    //! Coordinate (i, j, k) represents Cloudtype i, Algorithm j and results from measure k.


   // StatisticInfo<int> correctRecognition;
   // StatisticInfo<double> MinMaxError;
   // std::vector<Measurer> measures;
};

#endif // CONTROLLER_H
