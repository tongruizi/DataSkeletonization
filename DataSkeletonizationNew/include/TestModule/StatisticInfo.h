#ifndef STATISTICINFO_H
#define STATISTICINFO_H


class StatisticInfo
{
public:
    StatisticInfo();
    static void run( MyGraphType & G, std::list<Point> & points)=0;
    static void seleAlgorithm(std::string type);
protected:

private:
    int number_of_cloudpoints;
    double epsilon;
    int number_of_runs;
    double angle;
    int number_of_branches;
    double scale;
    std::string type;
    MyGraphType graph;
    std::list<Point> clouds;
};



#endif // STATISTICINFO_H
