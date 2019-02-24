#include MetriRec.hpp
#include <mlpack/methods/range_search/range_search.hpp>
using namespace mlpack::range;

void run(std::vector<Point> & cloudlist, double r, MyGraphType & out)
{

}

void Labeling(MyGraphType & G, std::vector<Point> & cloudlist, double r)
{

    arma::mat cordata;
    GeneralConvertor::ListToMatTransposed(cloudlist,cordata);
    mlpack::range::RangeSearch<> a(cordata);
// The vector-of-vector objects we will store output in.
    std::vector<std::vector<size_t> > resultingNeighbors;
    std::vector<std::vector<double> > resultingDistances;
// The range we will use.
    math::Range t(r, 5r/3);
    a.Search(t, resultingNeighbors, resultingDistances);
    for (int i = 0; i < resultingNeighbors.size(); i++)
    {
        std::set<Point> branchPoint1;
        arma::mat cordata1;
        GeneralConvertor::ListToMatTransposed(resultingNeighbors[i],cordata1);
        mlpack::range::RangeSearch<> a(cordata1);
// The vector-of-vector objects we will store output in.
        std::vector<std::vector<size_t> > resultingNeighbors1;
        std::vector<std::vector<double> > resultingDistances1;
// The range we will use.
        math::Range p(0, 4/3r);
        a.Search(p, resultingNeighbors1, resultingDistances1);

        for (auto it = resultingNeighbors1[i].begin(); it != resultingNeighbors1[i].end(); it++)
        {
            Graph::add_vertex(G,*it);

            std::vector<int> componentMap(num_vertices(G));
            int num = boost::connected_components(G, componentMap.data());

            if(num = 2)
            {
                edgePoint.insert(it);

            }
            else
            {
                branchPoint1.insert(it);
            }
        }
    }
    arma::mat cordata2;
    GeneralConvertor::ListToMatTransposed(branchPoint1,cordata2);
    mlpack::range::RangeSearch<> a(cordata2);
// The vector-of-vector objects we will store output in.
    std::vector<std::vector<size_t> > resultingNeighbors2;
    std::vector<std::vector<double> > resultingDistances2;
// The range we will use.
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

void ReconstructGraph( MyGraphType & X, MyGraphType & H, std::set<Point> edgePoint, std::set<Point> branchPoint, double r)
{
    std::set<Point> edgePoint1;
    std::set<Point> branchPoint2;
    arma::mat cordata;
    GeneralConvertor::ListToMatTransposed(edgePoint,cordata);
    mlpack::range::RangeSearch<> a(cordata);
// The vector-of-vector objects we will store output in.
    std::vector<std::vector<size_t> > resultingNeighbors;
    std::vector<std::vector<double> > resultingDistances;
// The range we will use.
    math::Range t(0,2r);
    a.Search(t, resultingNeighbors, resultingDistances);
       for (int i = 0; i < resultingNeighbors.size(); i++)
    {
        for (int j = 0; j < resultingNeighbors[i].size(); j++)
        {
            if (i != resultingNeighbors[i][j])
            {
              edgePoint1.insert(resultingNeighbors[i][j]);
              Graph::add_edge(H,i,resultingNeighbors[i][j],resultingDistances[i][j]+4r);
            }
        }
    }
    arma::mat cordata1;
    GeneralConvertor::ListToMatTransposed(branchPoint,cordata1);
    mlpack::range::RangeSearch<> a(cordata1);
// The vector-of-vector objects we will store output in.
    std::vector<std::vector<size_t> > resultingNeighbors1;
    std::vector<std::vector<double> > resultingDistances1;
// The range we will use.
    math::Range q(0,2r);
    a.Search(q, resultingNeighbors1, resultingDistances1);
        for (int i = 0; i < resultingNeighbors1.size(); i++)
    {
        for (int j = 0; j < resultingNeighbors1[i].size(); j++)
        {
            if (i != resultingNeighbors1[i][j])
            {
               Graph::add_vertex(X,resultingNeighbors1[i][j]);
               double todistance = 0;
               for(it = edgePoint1.begin; it != edgePoint1.end; ++it){
               toDistance =  sqrt(CGAL::squared_distance(resultingNeighbors1[i][j],*it));
               if(todistance<2r){
               branchPoint2.insert(resultingNeighbors1[i][j]);

               }
               }

            }
        }
    }
    for (int i = 0; i < branchPoint2.size(); i++)
    {
        for (int j = i+1; j < branchPoint2.size(); j++)
        {
        Graph::add_edge(X,branchPoint2[i],branchPoint2[j]);
        }
        }
}










