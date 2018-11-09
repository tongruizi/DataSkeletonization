#include "CorrectEndTypeMeasure.h"
#include "Graph.h"


CorrectEndTypeMeasure::CorrectEndTypeMeasure(int precision):SimpleMeasurerCore("Endpoints",precision)
{
    //ctor
}


bool CorrectEndTypeMeasure::CompleteMeasurments(MyGraphType & G,generatable* cloud, std::list<Point>* generatedCloud)
{
    return cloud->DoesGraphHaveCorrectForm(G);
}





