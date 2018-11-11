#ifndef CORRECTTYPEMEASURE_H
#define CORRECTTYPEMEASURE_H

#include "Graph.h"
#include "SimpleMeasurerCore.h"

class CorrectTypeMeasure : public SimpleMeasurerCore
{
public:
    CorrectTypeMeasure(int precision);
    bool CompleteMeasurments(MyGraphType & G,generatable* cloud, std::list<Point>* generatedCloud);
    CorrectTypeMeasure* Clone() override
    {
        return new CorrectTypeMeasure(*this);
    }
    //virtual ~CorrectTypeMeasure();

protected:

private:
};

#endif // CORRECTTYPEMEASURE_H
