#include "GeneralConvertor.h"
#include <fstream>
#include "Graph.h"

GeneralConvertor::GeneralConvertor()
{
    //ctor
}

void GeneralConvertor::XYZtoMAT(std::string fl, arma::mat & data)
{
    // We make sure that the data-matrix is empy
    data.reset();
    std::ifstream infile(fl.c_str());
    double x;
    double y;
    double z;
    std::string w;
    int k;
    infile >> k;
    data.set_size(k,3);
    getline(infile,w);
    getline(infile,w);
    //  std::vector<std::vector<double>> toArma;
    int i = 0;
    while (infile >> w >> x >> y >> z)
    {
        data(i,0) = x;
        data(i,1) = y;
        data(i,2) = z;
        i++;
    }

}

void GeneralConvertor::MatInfoToFile(std::string out, arma::mat & data, std::vector<double> scalar)
{
    std::ofstream mystream;
    mystream.open(out);
    mystream << "x coord, y coord, z coord, scalar" << std::endl;
    for (int i = 0; i < scalar.size(); i++)
    {
        double v1 = data(i,0);
        double v2 = data(i,1);
        double v3 = data(i,2);
        mystream << v1;
        mystream << ", ";
        mystream << v2;
        mystream << ", ";
        mystream << v3;
        mystream << ", ";
        mystream << scalar[i];
        mystream << std::endl;
        // ", " << v2 ", " << v3 << ", " << scalar[i] << std::endl;
    }
    mystream.close();
}

void GeneralConvertor::VectorToFile(std::string out, std::vector<int> & s)
{

    std::ofstream mystream;
    mystream.open(out);
    for (int i = 0; i < s.size(); i++)
    {
        mystream << i << ", " << s[i] << std::endl;
    }
    mystream.close();

}

void GeneralConvertor::MSTToVTK(arma::mat & originalData, arma::mat & edges, std::string out)
{
    std::ofstream mystream;
    mystream.open(out);
    mystream << "# vtk DataFile Version 1.0" << std::endl;
    mystream << "3D triangulation data" << std::endl;
    mystream << "ASCII" << std::endl;
    mystream << std::endl;
    mystream << "DATASET POLYDATA" << std::endl;
    int vSize = originalData.n_cols;
    mystream << "POINTS " << vSize << " float" << std::endl;
    for (int i = 0; i < vSize; i++)
    {
        mystream << originalData(0,i) << " " << originalData(1,i) << " " << originalData(2,i) << std::endl;
    }
    int edgeSize = edges.n_cols;
    int tripledgeSize = 3 * edgeSize;
    mystream << "LINES " << edgeSize << " " << tripledgeSize << std::endl;
    for (int i = 0; i < edgeSize; i++)
    {
        mystream << "2 " << edges(0,i) << " " << edges(1,i) << std::endl;
    }
    mystream.close();
}

void GeneralConvertor::GraphToVtk(std::string path, MyGraphType &G)
{
    std::ofstream mystream;
    mystream.open(path);
    mystream << "# vtk DataFile Version 1.0\n";
    mystream << "3D triangulation data\n";
    mystream << "ASCII\n";
    mystream << std::endl;
    mystream << "DATASET POLYDATA\n";

    mystream << "POINTS " << num_vertices(G) << " float\n";
    for(int i=0; i<num_vertices(G); i++)
    {
        mystream << G[i].p << std::endl;
    }

    mystream << "LINES " << (num_edges(G)) << " " << (num_edges(G))*3 << std::endl;

    auto epair = edges(G);
    for(auto iter=epair.first; iter!=epair.second; iter++)
    {
        mystream  << "2 " << source(*iter, G) << " " << target(*iter, G) <<std::endl;
    }
}

void GeneralConvertor::ListToMat(std::list<Point> & points, arma::mat & data)
{
    int k = points.size();
    data.set_size(k,3);
    int j = 0;
    for (auto it = points.begin(); it != points.end(); it++)
    {
        data(j,0) = it->x();
        data(j,1) = it->y();
        data(j,2) = it->z();
        j++;
    }

}


