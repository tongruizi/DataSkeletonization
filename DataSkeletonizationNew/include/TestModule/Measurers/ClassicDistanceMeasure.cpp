#include "ClassicDistanceMeasure.h"
#include "Computation.h"
#include <iostream>
#include <iomanip>

ClassicDistanceMeasure::ClassicDistanceMeasure(int precision):
    AbstractMeasurer("Distance",precision)
{
    //ctor
}

double ClassicDistanceMeasure::CompleteMeasurments(MyGraphType & G,generatable* cloud, std::list<Point>* generatedCloud)
{
    return Computation::AABBError(G,*generatedCloud);
}

std::string ClassicDistanceMeasure::returnStatisticString()
{
    double avg = mystatistic.returnAvg();
    std::stringstream stream;
    stream << std::fixed << std::setprecision(precision) << avg;
    std::string s = stream.str();
    return s;
}

