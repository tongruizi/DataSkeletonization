#ifndef ABSTRACTALGORITHM_H
#define ABSTRACTALGORITHM_H

#include "Definitions.h"
#include "Graph.h"

//! THIS IS WHAT WAS ASKED FOR !!!!!!

class AbstractAlgorithm
{
    public:
        AbstractAlgorithm() {}
        //! THIS WAS THE ONLY METHOD THAT WAS REQUIRED FOR YOU XD
        virtual void Run(std::list<Point> & cloudlist, MyGraphType & out) = 0;

    protected:

    private:
};

#endif // ABSTRACTALGORITHM_H
