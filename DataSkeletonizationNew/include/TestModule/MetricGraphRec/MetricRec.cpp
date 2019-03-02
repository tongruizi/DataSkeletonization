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
        MyGraphType & G;
        for (int k = 0; k<resultingNeighbors[i].size; k++)
        {
            Graph::add_vertex(G, resultingNeighbors[i]);

        }
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
        for (int k = 0; k<resultingNeighbors1.size; k++)
        {
            for (int q = 0; q<resultingDistances1[k].size; q++)
            {
                if ( k!= resultingNeighbors1[k][q])
                {
                    Graph::add_edge(G, k,resultingNeighbors1[k][q]);
                }

            }
        }
        std::vector<int> componentMap(num_vertices(G));
        int num = boost::connected_components(G, componentMap.data());
        //first label points by dgr(y)
        if(num = 2)
        {
            edgePoint.insert(resultingNeighbors[i][0]);
        }
        else
        {
            branchPoint1.insert(resultingNeighbors[i][0]);
        }
    }
    //Label all points within distance 2rfrom a preliminary branch point as branch points
    arma::mat ReferenceData;
    GeneralConvertor::ListToMatTransposed(branchPoint1,ReferenceData);
    mlpack::range::RangeSearch<> a(ReferenceData);
    std::vector<std::vector<size_t> > resultingNeighbors2;
    std::vector<std::vector<double> > resultingDistances2;
    math::Range q(0,2r);
    a.Search(cloudlist, q, resultingNeighbors2, resultingDistances2);

    for (int i = 0; i < resultingNeighbors2.size(); i++)
    {
        for (int j = 0; j < resultingNeighbors2[i].size(); j++)
        {

            branchPoint.insert(resultingNeighbors[i][j]);

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
            edgePoint1.insert(resultingNeighbors[i][j]);
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
            branchPoint2.insert(resultingNeighbors1[i][j]);
        }
    }

    for(it=branchPoint2.begin(); it<branchPoint2.end(); it++)
    {
        Graph::add_vertex(X, *it);
    }
    //step line17 :Let there be an edge between vertices ofˆXif their corresponding connected components inR2r(V)containpoints at distance less than 2rfrom the same connected component ofR2r(E)

    //this part codes are stupid, but i don't know the fast way to find the minimum distance between two sets of points

    for (int p = 0; p < resultingNeighbors.size(); p++)
    {
        std::unordered_set<int> componentsOrder;
        double mindistance = 1000r;
        double maxdistance = 0;
        for (int i = 0; i < resultingNeighbors1.size(); i++)
        {
            for (int q = 0; q < resultingNeighbors[p].size(); q++)
            {
                for (int j = 0; j < resultingNeighbors1[i].size(); j++)
                {
                    int distance = sqrt(CGAL::squared_distance(resultingNeighbors[p][q],resultingNeighbors1[i][j]));
                    if(distance<mindistance)
                    {
                        mindistance = distance;
                    }
                }
                if(mindistace<2r)
                {
                    //we can know which components in V is less 2r distance from same component in E
                    componentsOrder.insert(i);
                }
            }
        }
        //find the diameter of the corresponding connected component in E
        for (int q = 0; q < resultingNeighbors[p].size(); q++)
        {
            for (int f = q+1; f < resultingNeighbors[p].size(); f++)
            {
                int distance = sqrt(CGAL::squared_distance(resultingNeighbors[p][q],resultingNeighbors[p][f]));
                if(distance>maxdistance)
                {
                    maxdistance = distance;
                }
            }
            //connect these components in V with length
            for(it=componentsOrder.begin(); it<componentsOrder.end(); it++)
            {
                for(she = componentsOrder.begin()+it; she<compnentsOrder.end(); she++)
                {
                    for(Point1 =resulting1[it].begin(); Point1 =resulting1[it].end(); Point1++)
                    {
                        for(Point2 = resulting[she].begin(); Point2 = resulting[she].end(); Point2++)
                        {
                            Graph::add_edge(X, Point1, Point2, Weight(maxdistance+4r));
                        }
                    }
                }
            }
        }
    }















