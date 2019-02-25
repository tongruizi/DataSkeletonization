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
        //connected components of Rips-Vietoris graphR4r/3(Sy)
        std::set<Point> branchPoint1;
        arma::mat cordata1;
        GeneralConvertor::ListToMatTransposed(resultingNeighbors[i],cordata1);
        mlpack::range::RangeSearch<> a(cordata1);

        std::vector<std::vector<size_t> > resultingNeighbors1;
        std::vector<std::vector<double> > resultingDistances1;
        math::Range p(0, 4/3r);
        a.Search(p, resultingNeighbors1, resultingDistances1);
        //degr(y)←Number of connected components
        MyGraphType & G;
        for (int k = 0; k<resultingNeighbors1.size; k++)
        {
            for (int q = 0; q<resultingDistances1[k].size; q++)
            {
                Graph::add_vertex(G,resultingDistances1[k][q]);

                Graph::add_edge(k,resultingNeighbors1[k][q],G);

            }
        }
        std::vector<int> componentMap(num_vertices(G));
        int num = boost::connected_components(G, componentMap.data());
        //first label points by dgr(y)
        if(num = 2)
        {
            edgePoint.insert(it);

        }
        else
        {
            branchPoint1.insert(it);
        }
    }
    //Label all points within distance 2rfrom a preliminary branch point as branch points
    arma::mat cordata2;
    GeneralConvertor::ListToMatTransposed(branchPoint1,cordata2);
    mlpack::range::RangeSearch<> a(cordata2);
    std::vector<std::vector<size_t> > resultingNeighbors2;
    std::vector<std::vector<double> > resultingDistances2;
    math::Range q(0, 2r);
    a.Search(q, resultingNeighbors2, resultingDistances2);
    for (int i = 0; i < resultingNeighbors2.size(); i++)
    {
        for (int j = 0; j < resultingNeighbors2[i].size(); j++)
        {
            if (i != resultingNeighbors[i][j])
            {
                branchPoint.insert(resultingNeighbors[i][j]);
            }
        }
    }
}

void ReconstructGraph(std::unordered_set<Point> edgePoint, std::unordered_set<Point> branchPoint, double r)
{
//connected components of the Rips-Vietoris graphsR2r(E)
    std::unordered_set<Point> edgePoint1;
    std::unordered_set<Point> branchPoint2;
    arma::mat cordata;
    GeneralConvertor::ListToMatTransposed(edgePoint,cordata);
    mlpack::range::RangeSearch<> a(cordata);
    std::vector<std::vector<size_t> > resultingNeighbors;
    std::vector<std::vector<double> > resultingDistances;
    math::Range t(0,2r);
    a.Search(t, resultingNeighbors, resultingDistances);

    //get R2r(E)
    for (int i = 0; i < resultingNeighbors.size(); i++)
    {
        for (int j = 0; j < resultingNeighbors[i].size(); j++)
        {
            if (i != resultingNeighbors[i][j])
            {
                edgePoint1.insert(resultingNeighbors[i][j]);
            }
        }
    }
    //new graph
    MyGraphType & X;
////connected components of the Rips-Vietoris graphsR2r(V)
    arma::mat cordata1;
    GeneralConvertor::ListToMatTransposed(branchPoint,cordata1);
    mlpack::range::RangeSearch<> a(cordata1);
    std::vector<std::vector<size_t> > resultingNeighbors1;
    std::vector<std::vector<double> > resultingDistances1;
    math::Range q(0,2r);
    a.Search(q, resultingNeighbors1, resultingDistances1);
//get R2r(V)
    for (int i = 0; i < resultingNeighbors1.size(); i++)
    {
        for (int j = 0; j < resultingNeighbors1[i].size(); j++)
        {
            if (i != resultingNeighbors1[i][j])
            {
                Graph::add_vertex(X,resultingNeighbors1[i][j]);
                branchPoint2.insert(resultingNeighbors1[i][j]);
            }
        }
    }
    //step line17 :Let there be an edge between vertices ofˆXif their corresponding connected components inR2r(V)containpoints at distance less than 2rfrom the same connected component ofR2r(E)

    arma::mat ReferenceData;
    GeneralConvertor::ListToMatTransposed(branchPoint2,ReferenceData);
    mlpack::range::RangeSearch<> a(ReferenceData);
    std::vector<std::vector<size_t> > resultingNeighbors2;
    std::vector<std::vector<double> > resultingDistances2;
    math::Range q(0,2r);
    a.Search(edgePoint1, q, resultingNeighbors2, resultingDistances2);
    for (int k = 0; k<resultingNeighbors2.size; k++)
    {
        for (int q = 0; q<resultingDistances2[k].size; q++)
        {
            //add the aege to new graph
            Graph::add_edge(k,resultingNeighbors1[k][q],X);

        }
    }


}










