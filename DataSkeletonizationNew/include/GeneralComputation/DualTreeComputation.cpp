#include "DualTreeComputation.h"
#include "GeneralConvertor.h"
#include <mlpack/methods/range_search/range_search.hpp>
#include "SegmentDistance.h"
#include <mlpack/core/tree/cover_tree.hpp>
#include <mlpack/methods/neighbor_search/neighbor_search.hpp>

DualTreeComputation::DualTreeComputation()
{
    //ctor
}

void DualTreeComputation::ComputeEpsilonNeighborhoodGraph(std::list<Point> & p, MyGraphType & G, double epsilon)
{
    arma::mat cordata;
    GeneralConvertor::ListToMatTransposed(p,cordata);
    mlpack::range::RangeSearch<> a(cordata);
// The vector-of-vector objects we will store output in.
    std::vector<std::vector<size_t> > resultingNeighbors;
    std::vector<std::vector<double> > resultingDistances;
// The range we will use.
    mlpack::math::Range r(0.0, epsilon); // [0.0, 2.0].
    a.Search(r, resultingNeighbors, resultingDistances);
    for (auto it = p.begin(); it != p.end(); it++)
    {
        Graph::add_vertex(G,*it);
    }
    for (int i = 0; i < resultingNeighbors.size(); i++)
    {
        for (int j = 0; j < resultingNeighbors[i].size(); j++)
        {
            if (i != resultingNeighbors[i][j])
            {
                Graph::add_edge(G,i,resultingNeighbors[i][j]);
            }
        }
    }
}


void DualTreeComputation::ComputeMST(std::list<Point> & p,MyGraphType & G)
{
    arma::mat cordata;
//    std::cout << "No fail 0" << std::endl;
    GeneralConvertor::ListToMatTransposed(p,cordata);
//   std::cout << "No fail 1" << std::endl;
    mlpack::emst::DualTreeBoruvka<> MSTOP(cordata);
//   std::cout << "No fail 2" << std::endl;
    arma::mat results;
//   std::cout << "No fail 3" << std::endl;
    MSTOP.ComputeMST(results);
//   std::cout << "No fail 4" << std::endl;
    GeneralConvertor::ArmaMatToGraph(G,results,cordata);
//   std::cout << "No fail 5" << std::endl;
}
//using namespace mlpack::neighbor;
void DualTreeComputation::NearestNeighborForTwoKDTrees(arma::Mat<size_t> & results,arma::mat & referenceData, arma::mat & queryData)
{

    mlpack::neighbor::KNN a(referenceData);
    arma::mat resultingDistances;
    a.Search(queryData, 1, results, resultingDistances);

}

void DualTreeComputation::NearestNeighborsForLineSegments(std::vector<Segment> & segments, std::list<Point> & pointcloud,arma::Mat<size_t> & results)
{
//! We convert segments into tree.
    arma::mat referencedata(6,segments.size());
    int indx = 0;
    for (int i = 0; i < segments.size(); i++)
    {
        Point p = (segments[i]).source();
        Point q = (segments[i]).target();
        referencedata(0,i) = p.x();
        referencedata(1,i) = p.y();
        referencedata(2,i) = p.z();
        referencedata(3,i) = q.x();
        referencedata(4,i) = q.y();
        referencedata(5,i) = q.z();
    }


//! We convert pointcloud into tree
    arma::mat querydata(6, pointcloud.size());
    indx = 0;
    for (auto it = pointcloud.begin(); it != pointcloud.end(); it++)
    {
        Point p = (*it);
        Point q = (*it);
        querydata(0,indx) = p.x();
        querydata(1,indx) = p.y();
        querydata(2,indx) = p.z();
        querydata(3,indx) = q.x();
        querydata(4,indx) = q.y();
        querydata(5,indx) = q.z();
        indx++;
    }
    //  GeneralConvertor::ListToMatTransposed(pointcloud,querydata);

//! We define two cover trees...


    typedef mlpack::neighbor::NearestNeighborSort WWW;
    typedef mlpack::neighbor::NeighborSearchStat<WWW> NST;

    mlpack::neighbor::NeighborSearch<WWW,SegmentDistance,arma::mat,mlpack::tree::StandardCoverTree > a(referencedata);
//    mlpack::neighbor::Neighbo
    arma::mat resultingDistances;
    a.Search(querydata, 1, results, resultingDistances);
    //std::cout << resultingDistances << std::endl;
    //std::cout << "Col size:" << resultingDistances.n_cols << std::endl;
   // std::cout << "Row size:" << resultingDistances.n_rows << std::endl;


}

// Stupid junk:

//  mlpack::neighbor::NeighborSearch<mlpack::tree::StandardCoverTree> a(referencedata);

//   mlpack::tree::CoverTree<mlpack::metric::EuclideanDistance> queryTree(querydata);
//   OurCoverTree referenceTree(referencedata);
// mlpack::neighbor::NearestNeighborSort, SegmentDistance, arma::mat,
//   mlpack::neighbor::NeighborSearch<OurCoverTree> a(referenceTree);

//typedef NeighborSearch<NearestNeighborSort, metric::EuclideanDistance> KNN;


//  mlpack::neighbor::NeighborSearch<WWW, SegmentDistance,arma::mat,OurCoverTree> a(referencedata);

//mlpack::neighbor::KNN
//FirstPointIsRoot
//  mlpack::tree::StandardCoverTree<mlpack::metric::EuclideanDistance,NST,arma::mat>
//mlpack::tree::KD
// BinarySpaceTree<MetricType,
//    StatisticType,
//    MatType,

// <mlpack::metric::EuclideanDistance, mlpack::tree::EmptyStatistic, arma::mat>

//typedef mlpack::neighbor::NearestNeighborSort WWW;
//typedef mlpack::neighbor::NeighborSearchStat<WWW> NST;



