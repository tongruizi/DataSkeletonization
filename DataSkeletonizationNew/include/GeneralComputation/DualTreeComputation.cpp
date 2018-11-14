#include "DualTreeComputation.h"
#include "GeneralConvertor.h"
#include <mlpack/methods/range_search/range_search.hpp>

DualTreeComputation::DualTreeComputation()
{
    //ctor
}

void DualTreeComputation::ComputeEpsilonNeighborhoodGraph(std::list<Point> & p, MyGraphType & G, double epsilon)
{
    arma::mat cordata;
    GeneralConvertor::ListToMatTransposed(p,cordata);
    mlpack::range::RangeSearch<> a(cordata);
// The vector-of-vector objects we will store output in.
    std::vector<std::vector<size_t> > resultingNeighbors;
    std::vector<std::vector<double> > resultingDistances;
// The range we will use.
    mlpack::math::Range r(0.0, epsilon); // [0.0, 2.0].
    a.Search(r, resultingNeighbors, resultingDistances);
    for (auto it = p.begin(); it != p.end(); it++)
    {
        Graph::add_vertex(G,*it);
    }
    for (int i = 0; i < resultingNeighbors.size(); i++)
    {
        for (int j = 0; j < resultingNeighbors[i].size(); j++)
        {
            if (i != resultingNeighbors[i][j])
            {
                Graph::add_edge(G,i,resultingNeighbors[i][j]);
            }
        }
    }
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
