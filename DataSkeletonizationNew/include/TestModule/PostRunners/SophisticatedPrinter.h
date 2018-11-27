#ifndef SOPHISTICATEDPRINTER_H
#define SOPHISTICATEDPRINTER_H

#include "PostRunInterface.h"
#include "GeneralConvertor.h"

class SophisticatedPrinter : public PostRunInterface
{
public:
    SophisticatedPrinter(std::string folder): folder(folder) {}
    void run(MyGraphType & G, std::list<Point> & cloud, AbstractCloudType* gen, int RunNumber, std::string AlgorithmName) override
    {
        std::string finalpath = folder + "File" + std::to_string(RunNumber) + ".xyz";
        GeneralConvertor::CloudToXYZ(cloud,finalpath,RunNumber);
       // GeneralConvertor::GraphToVtk(finalpath,G);
    }

protected:

private:
    std::string folder;
};

#endif // SOPHISTICATEDPRINTER_H
