#ifndef DUALTREECOMPUTATION_H
#define DUALTREECOMPUTATION_H

#include <mlpack/methods/emst/dtb.hpp>
#include "Graph.h"
#include "Definitions.h"
#include <mlpack/core.hpp>
#include <mlpack/methods/neighbor_search/neighbor_search.hpp>



class DualTreeComputation
{
    public:
        DualTreeComputation();
       // virtual ~DualTreeComputation();
        static void ComputeMST(std::list<Point> & p, MyGraphType & G);
        static void ComputeEpsilonNeighborhoodGraph(std::list<Point> & p , MyGraphType & G, double epsilon);
        static void NearestNeighborForTwoKDTrees(arma::Mat<size_t> & results,arma::mat & referenceset, arma::mat & queryset);

    protected:

    private:
};

#endif // DUALTREECOMPUTATION_H
