#include "DualTreeComputation.h"
#include "GeneralConvertor.h"

DualTreeComputation::DualTreeComputation()
{
    //ctor
}
void DualTreeComputation::ComputeMST(std::list<Point> & p,MyGraphType & G)
{
    arma::mat cordata;
//    std::cout << "No fail 0" << std::endl;
    GeneralConvertor::ListToMatTransposed(p,cordata);
 //   std::cout << "No fail 1" << std::endl;
    mlpack::emst::DualTreeBoruvka<> MSTOP(cordata);
 //   std::cout << "No fail 2" << std::endl;
    arma::mat results;
 //   std::cout << "No fail 3" << std::endl;
    MSTOP.ComputeMST(results);
 //   std::cout << "No fail 4" << std::endl;
    GeneralConvertor::ArmaMatToGraph(G,results,cordata);
 //   std::cout << "No fail 5" << std::endl;

}
