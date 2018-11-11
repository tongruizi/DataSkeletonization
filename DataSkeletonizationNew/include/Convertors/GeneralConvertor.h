#ifndef GENERALCONVERTOR_H
#define GENERALCONVERTOR_H

#include <string>
#include <mlpack/core.hpp>
#include <vector>
#include "Graph.h"


class GeneralConvertor
{
public:
    GeneralConvertor();
    static void XYZtoMAT(std::string fl, arma::mat & data);
    static void MatInfoToFile(std::string out, arma::mat & data, std::vector<double> scalar);
    static void VectorToFile(std::string out, std::vector<int> & s);
    static void MSTToVTK(arma::mat & originalData, arma::mat & edges, std::string out);
    static void GraphToVtk(std::string path, MyGraphType &G);
    static void ListToMat(std::list<Point> & lp, arma::mat & mtx);
    static void ArmaMatToGraph(MyGraphType & G, arma::mat & edges, arma::mat & originalData);
    //! Method to print data from measurers directly into latex table.
    static void DataToLatex(std::vector<std::vector<std::vector<std::string>>> & measurers,
                            std::vector<std::vector<std::string>> & timeMeasures,
                            std::vector<std::string> & GraphNames, std::vector<std::string> & AlgorithmNames,
                            std::vector<std::string> & MeasurerNames, std::string filename);
    static void DataToCSV(std::vector<std::vector<std::vector<std::string>>> & measurers,
                                     std::vector<std::vector<std::string>> & timeMeasures,
                                     std::vector<std::string> & GraphNames, std::vector<std::string> & AlgorithmNames,
                                     std::vector<std::string> & MeasureNames, std::string filename);

protected:

private:
};

#endif // GENERALCONVERTOR_H
