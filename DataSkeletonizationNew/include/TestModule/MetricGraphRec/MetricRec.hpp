#ifndef METRICREC_HPP_INCLUDED
#define METRICREC_HPP_INCLUDED


class MetricRec
{
    public:
        MetricRec() {}
        void Run(std::vector<Point> & cloudlist, double r, MyGraphType & out){}
        void Labeling(std::vector<Point> & cloudlist, std::list<Point> & s, double r)(){}
        void ReconstructGraph( MyGraphType & G, std::set<Point> edgePoint, std::set<Point> branchPoint, double r){};
    protected:

    private:
    double r;
    MyGraphType G;
    std::vector<Point> cloudlist;
    std::unordered_set<int> edgePoint;
    std::unordered_set<int> branchPoint;

};





#endif // METRICREC_HPP_INCLUDED
