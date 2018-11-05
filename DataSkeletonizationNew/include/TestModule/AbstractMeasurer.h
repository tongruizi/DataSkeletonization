#ifndef ABSTRACTMEASURER_H
#define ABSTRACTMEASURER_H

#include "StatisticInfo.h"

template <class T>
class AbstractMeasurer
{
public:
    virtual T CompleteMeasurments(MyGraphType & G) =0;
    void Append(MyGraphType & G)
    {
        T InMeasure=CompleteMeasurments(G);
        mystatistic.add(InMeasure);
    }
    T getStatistic_instance()
    {
        return mystatistic;
    }
    std::string returnStatisticData()
    {
    return mystatistic.returnInfo();
    }
private:

    StatisticInfo<T> mystatistic;
};




#endif // ABSTRACTMEASURER_H
