#ifndef MEANSQUAREDISTANCEMEASURE_H
#define MEANSQUAREDISTANCEMEASURE_H

#include "AbstractMeasurer.h"

class MeanSquareDistanceMeasure : public AbstractMeasurer<double>
{
public:
    MeanSquareDistanceMeasure(int precision);
    double CompleteMeasurments(MyGraphType & G,AbstractCloudType* cloud, std::list<Point>* generatedCloud, int cloudit);
    std::string returnStatisticString();
    ClassicDistanceMeasure* Clone() override
    {
        return new ClassicDistanceMeasure(*this);
    }


protected:

private:
};

#endif // MEANSQUAREDISTANCEMEASURE_H
