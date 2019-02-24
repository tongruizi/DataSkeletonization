#ifndef METRICREC_HPP_INCLUDED
#define METRICREC_HPP_INCLUDED


class MetricRec
{
    public:
        MetricRec() {}
        void Run(std::list<Point> & cloudlist, double r, MyGraphType & out){}
        void Labeling(std::list<Point> & cloudlist, std::list<Point> & s, double r)(){}
        void ReconstructGraph( MyGraphType & G, std::set<Point> edgePoint, std::set<Point> branchPoint, double r){};
    protected:

    private:
    double r;
    MyGraphType G;
    std::list<Point> cloudlist;
    std::set<Point> edgePoint;
    std::set<Point> branchPoint;

};





#endif // METRICREC_HPP_INCLUDED
