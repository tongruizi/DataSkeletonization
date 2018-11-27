#include "DualTreeDistanceMeasure.h"
#include "GeneralConvertor.h"
#include "DualTreeComputation.h"

DualTreeDistanceMeasure::DualTreeDistanceMeasure(int precision):
    AbstractMeasurer("DualTreeDistance",precision)
{
    //ctor
}

double DualTreeDistanceMeasure::CompleteMeasurments(MyGraphType & G,AbstractCloudType* cloud, std::list<Point>* generatedCloud, int cloudit)
{
//! Program this please tomorrow:
    std::vector<Segment> segments;
    GeneralConvertor::GraphToPaths(G,segments);
    arma::Mat<size_t> results;
    DualTreeComputation::NearestNeighborsForLineSegments(segments,*generatedCloud,results);
    double maxD = 0;
    int counter = 0;
    for (auto it = (*generatedCloud).begin(); it != (*generatedCloud).end(); it++)
    {
        double tmpD = sqrt(CGAL::squared_distance(*it,segments[results(0,counter)]));
        counter++;
        maxD = std::max(maxD, tmpD);
    }
    return maxD;
}
std::string DualTreeDistanceMeasure::returnStatisticString()
{
    double avg = mystatistic.returnAvg();
    //  std::cout << "Returned: " << avg << std::endl;
    //  std::cout << "Data contained: " << mystatistic.returnNumber() << std::endl;
    std::stringstream stream;
    stream << std::fixed << std::setprecision(precision) << avg;
    std::string s = stream.str();
    return s;

}
