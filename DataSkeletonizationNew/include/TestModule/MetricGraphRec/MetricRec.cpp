#include MetriRec.hpp
#include <mlpack/methods/range_search/range_search.hpp>
using namespace mlpack::range;

void run(std::vector<Point> & cloudlist, double r, MyGraphType & out)
{

}

void Labeling(std::vector<Point> & cloudlist, double r)
{
//get y←BY(y,5r/3)\BY(y,r)
    arma::mat cordata;
    GeneralConvertor::ListToMatTransposed(cloudlist,cordata);
    mlpack::range::RangeSearch<> a(cordata);

    std::vector<std::vector<size_t> > resultingNeighbors;
    std::vector<std::vector<double> > resultingDistances;

    math::Range t(r, 5r/3);
    a.Search(t, resultingNeighbors, resultingDistances);
    for (int i = 0; i < resultingNeighbors.size(); i++)
    {
        MyGraphType G;
        for (int k = 0; k<resultingNeighbors[i].size; k++)
        {
            Graph::add_vertex(G, resultingNeighbors[i]);

        }
        //connected components of Rips-Vietoris graphR4r/3(Sy)
        std::set<int> branchPoint1;
        arma::mat cordata1;
        GeneralConvertor::ListToMatTransposed(resultingNeighbors[i],cordata1);
        mlpack::range::RangeSearch<> b(cordata1);

        std::vector<std::vector<size_t> > resultingNeighbors1;
        std::vector<std::vector<double> > resultingDistances1;
        math::Range p(0, 4/3r);
        b.Search(p, resultingNeighbors1, resultingDistances1);
        //degr(y)←Number of connected components
        for (int k = 0; k<resultingNeighbors1.size; k++)
        {
            for (int q = 0; q<resultingNeighbors1[k].size; q++)
            {

                Graph::add_edge(G, k,resultingNeighbors1[k][q]);


            }
        }
        std::vector<int> componentMap(num_vertices(G));
        int num = boost::connected_components(G, componentMap.data());
        //first label points by dgr(y)
        if(num = 2)
        {
            edgePoint.insert(i);
        }
        else
        {
            branchPoint1.insert(i);
        }
    }
    //Label all points within distance 2rfrom a preliminary branch point as branch points

    arma::mat ReferenceData;
    GeneralConvertor::ListToMatTransposed(cloudlist,coredata2);
    mlpack::range::RangeSearch<> c(coredata2);
    std::vector<std::vector<size_t> > resultingNeighbors2;
    std::vector<std::vector<double> > resultingDistances2;
    math::Range q(0,2r);
    c.Search(q, resultingNeighbors2, resultingDistances2);

    for (auto it = branchPoint1.begin(); it != branchPoint1.end(); it++)
    {
        for (int q = 0; q<resultingNeighbors2[*it].size; q++)
        {
            if (branchPoint.find(q) != branchPoint.end())
            {

                branchPoint.insert(q);
            }
        }
    }
}

void ReconstructGraph(std::vector<std::vector<size_t> > &resultingNeighbors2, std::vector<Point> & cloudlist,  std::unordered_set<Point> branchPoint, double r)
{
//connected components of the Rips-Vietoris graphsR2r(V) and R2r(E)
    MyGraphType output;
    std::unordered_set<int> branchComponent;
    std::unordered_set<int> edgeComponent;
    for (auto it = branchPoint.begin(); it != branchPoint.end(); it++)
    {
        for (int q = 0; q<resultingNeighbors2[*it].size; q++)
        {
            if (branchPoint.find(q) != branchPoint.end())
            {

                branchComponent.insert(q);
            }
        }
    }
    for (int p = 0; p<resultingNeighbors2.size; p++)
    {
        edgeComponent.insert(p);
    }
    for (auto it = branchComponent.begin(); it != branchComponent.end(); it++)
    {

        edgeComponent.erase(edgeComponent.find(*it));

    }

    std::unordered_map<int, Point> pair1;

    for (auto it = branchComponent.begin(); it != branchComponent.end(); it++)
    {
        double x=0;
        double y=0;
        double z=0;
        for(int q = 0; q<resultingNeighbors2[*it].size; q++)
        {
            x = x + resultingNeighbors2[*it][q].x;
            y = y + resultingNeighbors2[*it][q].y;
            z = z + resultingNeighbors2[*it][q].z;

        }
        x=x/resultingNeighbors2[*it].size;
        y=y/resultingNeighbors2[*it].size;
        z=z/resultingNeighbors2[*it].size;

        pair1.insert(*it, (x,y,z));

    }
    std::unordered_map<int, Point> pair2;
    for (auto it = edgeComponent.begin(); it != edgeComponent.end(); it++)
    {
        double x=0;
        double y=0;
        double z=0;
        for(int q = 0; q<resultingNeighbors2[*it].size; q++)
        {
            x = x + resultingNeighbors2[*it][q].x;
            y = y + resultingNeighbors2[*it][q].y;
            z = z + resultingNeighbors2[*it][q].z;

        }
        x=x/resultingNeighbors2[*it].size;
        y=y/resultingNeighbors2[*it].size;
        z=z/resultingNeighbors2[*it].size;

        pair2.insert(*it, (x,y,z));

    }

    for (auto it = edgeComponent.begin(); it != edgeComponent.end(); it++)
    {
        std::vector<int> tempralVertex;
        for (auto him = branchComponent.begin(); him != branchComponent.end(); him++)
        {
            double Distance = sqrt(CGAL::squared_distance(pair2[*it],pair1[*him]);
        if (Distance<2r)
        {
            tempralVertex.push_back(*him);
            }
        }
        for (int t =0 ; t<tempralVertex.size()-1; t++)
        {
            for (int p =t+1; p<tempralVertex.size(); p++)
            {
                Graph::add_edge(output, Cloudlist[tempralVertex[t]], Cloudlist[tempralVertex[p]]);
            }
        }
    }




}















