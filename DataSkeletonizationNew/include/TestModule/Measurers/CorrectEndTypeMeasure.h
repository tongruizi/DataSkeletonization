#ifndef CORRECTENDTYPEMEASURE_H
#define CORRECTENDTYPEMEASURE_H

#include "Graph.h"
#include "ExplicitMeasurer.h"
#include "SimpleStatistic.h"
#include "SimpleMeasurerCore.h"

class CorrectEndTypeMeasure : public SimpleMeasurerCore
{
    public:
        CorrectEndTypeMeasure(int precision);
        bool CompleteMeasurments(MyGraphType & G,generatable* cloud, std::list<Point>* generatedCloud);
        CorrectEndTypeMeasure* Clone() override
        {
        return new CorrectEndTypeMeasure(*this);
        }
    protected:

    private:
};

#endif // CORRECTENDTYPEMEASURE_H
