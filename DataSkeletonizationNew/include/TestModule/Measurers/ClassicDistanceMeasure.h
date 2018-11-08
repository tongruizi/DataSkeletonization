#ifndef CLASSICDISTANCEMEASURE_H
#define CLASSICDISTANCEMEASURE_H

#include "AbstractMeasurer.h"

class ClassicDistanceMeasure : public AbstractMeasurer<double>
{
public:
    ClassicDistanceMeasure(int precision);
    double CompleteMeasurments(MyGraphType & G,generatable* cloud, std::list<Point>* generatedCloud);
    std::string returnStatisticString();
    ClassicDistanceMeasure* Clone() override
    {
        return new ClassicDistanceMeasure(*this);
    }



protected:

private:
};

#endif // CLASSICDISTANCEMEASURE_H
