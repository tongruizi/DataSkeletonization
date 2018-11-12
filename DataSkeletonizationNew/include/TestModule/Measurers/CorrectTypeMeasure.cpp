#include "CorrectTypeMeasure.h"

CorrectTypeMeasure::CorrectTypeMeasure(int precision):
SimpleMeasurerCore("Correct type",precision)
{
    //ctor
}

bool CorrectTypeMeasure::CompleteMeasurments(MyGraphType & G,AbstractCloudType* cloud, std::list<Point>* generatedCloud)
{
return cloud->DoesGraphHaveCorrectForm(G);
}

