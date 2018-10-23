#ifndef COMPUTATION_H
#define COMPUTATION_H

#include <cstdlib>
#include "Definitions.h"
#include "Graph.h"
#include <mlpack/core.hpp>


class Computation
{
public:
    Computation() {}
    static double unitRandom()
    {
        return ((double) rand() / (RAND_MAX));
    }
    static double distance(MyGraphType & G, vertex_descriptor v1, vertex_descriptor v2)
    {
        return sqrt(CGAL::squared_distance(G[v1].p,G[v2].p));
    }


    //! This method should be moved to convertor instead I think


    static void ArmaMatToGraph(MyGraphType & G, arma::mat & edges, arma::mat & originalData)
    {
        int vSize = originalData.n_cols;
        for (int i = 0; i < vSize; i++)
        {
            Point p(originalData(0,i),originalData(1,i),originalData(2,i));
            Graph::add_vertex(G,p);
        }

        int edgeSize = edges.n_cols;

        for (int i = 0; i < edgeSize; i++)
        {
            int one = (int) edges(0,i);
            int two = (int) edges(1,i);
            Graph::add_edge(G,one,two);

        }

    }

protected:

private:
};

#endif // COMPUTATION_H
