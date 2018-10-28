#ifndef ABSTRACTALGORITHM_H
#define ABSTRACTALGORITHM_H

#include "Definitions.h"
#include "Graph.h"


class AbstractAlgorithm
{
    public:
        AbstractAlgorithm() {}

        virtual void Run(std::list<Point> & cloudlist, MyGraphType & out) = 0;

    protected:

    private:
};

#endif // ABSTRACTALGORITHM_H
