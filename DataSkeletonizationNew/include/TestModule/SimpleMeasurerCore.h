#ifndef SIMPLEMEASURERCORE_H
#define SIMPLEMEASURERCORE_H

#include "SimpleStatistic.h"


class SimpleMeasurerCore : public ExplicitMeasurer
{
public:
    SimpleMeasurerCore(std::string name, int precision):
        ExplicitMeasurer(name,precision) {}


    std::string returnStatisticString()
    {
        double avg = statistic.returnAvg();
        std::stringstream stream;
        stream << std::fixed << std::setprecision(precision) << avg;
        std::string s = stream.str();
        return s;
    }
    virtual bool CompleteMeasurments(MyGraphType & G,generatable* cloud, std::list<Point>* generatedCloud) =0;

    virtual void run(MyGraphType & G, generatable* cloud, std::list<Point>* generatedCloud)
    {
        bool ww = this->CompleteMeasurments(G,cloud,generatedCloud);
        statistic.append(ww);
    }


    virtual void resetStatistic()
    {
        statistic.reset();
    }
    virtual SimpleMeasurerCore* Clone() = 0;

protected:
    SimpleStatistic statistic;

private:

};

#endif // SIMPLEMEASURERCORE_H
