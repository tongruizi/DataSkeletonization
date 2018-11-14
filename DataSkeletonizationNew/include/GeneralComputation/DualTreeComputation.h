#ifndef DUALTREECOMPUTATION_H
#define DUALTREECOMPUTATION_H

#include <mlpack/methods/emst/dtb.hpp>
#include "Graph.h"
#include "Definitions.h"
#include <mlpack/core.hpp>

class DualTreeComputation
{
    public:
        DualTreeComputation();
       // virtual ~DualTreeComputation();
        static void ComputeMST(std::list<Point> & p, MyGraphType & G);

    protected:

    private:
};

#endif // DUALTREECOMPUTATION_H
