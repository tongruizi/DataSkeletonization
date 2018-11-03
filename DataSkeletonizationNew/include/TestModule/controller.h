#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "AbstractAlgorithm.h"
#include "generatable.h"
#include "AbstractMeasurer.h"
#include "ExplicitMeasurer.h"

class controller
{
public:
    controller();

    void BeginTestRun();


    void addAlgorithm(AbstractAlgorithm & k);
    void addCloud(generatable & k);
   // void addMeasurer()
    void letsmesure(MyGraphType & G );
protected:

private:
    //! Vector for cloudtypes:
    std::vector<generatable> ACT;
    //! Vector for algorithmtypes:
    std::vector<AbstractAlgorithm> algorithms;
    std::vector<ExplicitMeasurer*> measurers ;

   // StatisticInfo<int> correctRecognition;
   // StatisticInfo<double> MinMaxError;
   // std::vector<Measurer> measures;
};

#endif // CONTROLLER_H
