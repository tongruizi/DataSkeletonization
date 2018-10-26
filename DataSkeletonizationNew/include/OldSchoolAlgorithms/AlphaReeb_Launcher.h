#ifndef ALPHAREEB_LAUNCHER_H
#define ALPHAREEB_LAUNCHER_H

#include "Graph.h"
#include "Definitions.h"
#include "AlphaReeb_Parameters.h"
#include "AlphaReebComputation.h"
#include "Computation.h"

class AlphaReeb_Launcher
{
public:
    AlphaReeb_Launcher(AlphaReeb_Parameters & param,double epsilon):
    param(param),epsilon(epsilon) {}
    void Run(std::list<Point> & cloudlist, MyGraphType & out)
    {

        MyGraphType G;
        Computation::ComputeDeluanayTriangulation(G, cloudlist);
        Computation::EpsilonSimplification(G, epsilon);
        MyGraphType Intermediate;
        AlphaReebComputation::Compute(G, param, out, Intermediate);


    }
protected:

private:
    AlphaReeb_Parameters param;
    double epsilon;
};

#endif // ALPHAREEB_LAUNCHER_H
