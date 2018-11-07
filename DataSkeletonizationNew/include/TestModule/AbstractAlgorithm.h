#ifndef ABSTRACTALGORITHM_H
#define ABSTRACTALGORITHM_H

#include "Definitions.h"
#include "Graph.h"
#include "ExplicitMeasurer.h"


class AbstractAlgorithm
{
public:
    AbstractAlgorithm(std::string name):name(name) {}

    virtual void Run(std::list<Point> & cloudlist, MyGraphType & out) = 0;

    double ExplicitRun()
    {
    //! Something will be add here soon.

    //! This method will return the run time of the algorithm
    return 0;
    }

    std::string returnName()
    {
        return name;
    }
    int returnMeasurerSize()
    {
        return measurers.size();
    }
    void addMeasurer(ExplicitMeasurer* m)
    {
        measurers.push_back(m);
    }
    ExplicitMeasurer* returnMeasurer(int k)
    {
        return measurers[k];
    }
    void CycleOverMeasurers(MyGraphType & G, generatable* cloud, std::list<Point>* generatedCloud)
    {
        for (int k = 0; k < measurers.size(); k++)
        {
            (*measurers[k]).run(G,cloud,generatedCloud);

        }
    }
    void ResetAllMeasurers()
    {
        for (int k = 0; k < measurers.size(); k++)
        {
            measurers[k] ->resetStatistic();
        }
    }

    void WriteResults(std::vector<std::string> & rvector)
    {
        rvector.resize(measurers.size());
        for (int k = 0; k < measurers.size(); k++)
        {
            rvector[k] = measurers[k] ->returnStatisticString() ;
        }

    }

protected:
    std::vector<ExplicitMeasurer*> measurers;
    //! We will create also method for post processing
private:
    std::string name;
};

#endif // ABSTRACTALGORITHM_H
