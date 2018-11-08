#ifndef POSTRUNINTERFACE_H
#define POSTRUNINTERFACE_H

#include "Graph.h"
#include "Definitions.h"

class PostRunInterface
{
    public:
        PostRunInterface() {}
        virtual void run(MyGraphType & G, generatable* gen, int RunNumber, std::string AlgorithmName) = 0;

    protected:

    private:
};

#endif // POSTRUNINTERFACE_H
