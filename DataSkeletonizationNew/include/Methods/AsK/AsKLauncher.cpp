#include "AsKLauncher.h"
#include "Computation.h"
#include "BranchSimplification.h"
#include "StraighteningMethods.h"
#include "DualTreeComputation.h"
#include "GeneralConvertor.h"

AsKLauncher::AsKLauncher(double a, double b, double c, std::string settings, std::string name = "AsK"):
    AbstractAlgorithm(name),branch_detection(a),approxError(b),simplificationError(c),settings(settings),numberOfRuns(0)
{
}
void AsKLauncher::Run(std::list<Point> & cloudlist, MyGraphType & out)
{
    //! DebugPrinting
    arma::Mat<size_t> theNeighbors;
    MyGraphType mst;
    MyGraphType optiout;
   // std::string tmpfolder = "/home/yury/LocalTests/FourthTest/ColoredPoints/";
    // Computation::computeMST(cloudlist,mst);
    DualTreeComputation::ComputeMST(cloudlist,mst);
    BranchDetection::SimplifyIt(mst,optiout,this->branch_detection,"",this->settings);
    std::list<std::list<Point>> optipath;
    std::list<std::list<Point>> branchsimplified;

    //double CurrentError = StraighteningMethods::ClassicStraightening(optiout, cloudlist, optipath, this->approxError);
    double CurrentError = StraighteningMethods::UpgradedStraightening(optiout,cloudlist,optipath,this->approxError,theNeighbors);

    double valuev = CurrentError*(this->simplificationError);
    BranchSimplification::SimplifyIt(optipath, branchsimplified,valuev);

    //std::string fn  = tmpfolder + "BranchedColoring" + std::to_string(this->numberOfRuns) + ".csv";
    //GeneralConvertor::ClusteringInfoToFile(cloudlist,theNeighbors, fn,boost::num_vertices(optiout));

    //  BranchSimplification::PathToGraphProper(out, branchsimplified);
    BranchSimplification::PathToGraphProper(out, branchsimplified);
    this->numberOfRuns++;
}

//void ClassicUIHandle::CorrectCalculationToGraphIntermediate(MyGraphType & FG, std::list<std::list<Point>> & optipath,
//std::list<std::list<Point>> & branchsimplified, std::list<Point> & cloud, double & mstlength, std::string settings)
//{
//MyGraphType tree = Computation::computeMST(cloud);
//MyGraphType optiout;
//mstlength = Computation::AverageEdgelength(tree);
//double param1 = ClassicUIHandle::branchDetect*mstlength;
//BranchDetection::SimplifyIt(tree,optiout,param1,"",settings);
//double ddd = StraighteningMethods::ClassicStraightening(optiout, cloud, optipath, this->Straightening );
//std::cout << "The straightening parameter: " << ddd << std::endl;
//double valuev = ddd*ClassicUIHandle::branchCollapse;
//BranchSimplification::SimplifyIt(optipath, branchsimplified,valuev);
//BranchSimplification::PathToGraphProper(FG, branchsimplified);
//}


//class AsKLauncher : public AbstractAlgorithm
//{
//    public:
//        AsKLauncher(double a, double b, double c);
//        void Run(std::list<Point> & cloudlist, MyGraphType & out) override;
//
//      //  virtual ~AsKLauncher();
//
//    protected:
//
//    private:
//    double branch_detection;
//    double approxError;
//    double simplificationError;
//};
