#ifndef STATISTICINFO_H
#define STATISTICINFO_H

//! This will be template file, so please code everything into header and completely DESTROY the implementation file

//! unit here can be either double, size_t, int or what ever. WE DONT CARE XD (but we still want stuff to work smoothly)
template<typename unit>
class StatisticInfo
{
public:
    StatisticInfo();
    //! wrong, we are not running anything here, this is only statistic file!
    //static void run( MyGraphType & G, std::list<Point> & points)=0;
    //! We are not selecting anything...
    //static void seleAlgorithm(std::string type);
    //! INSTEAD:
    unit returnSum()
    {
    return sum;
    }
    double returnAvg()
    {
    return sum/number;
    }
    void addMeasurment()
    {
    //! Implement this method

    }
protected:

private:

//! This is number of measurments: For now its always double, so we dont get stupid errors when dividing stuff
double number;
//! sum is unit
unit sum;
//! but average is always double!!!!
double avg;


//! No need for this
//    int number_of_cloudpoints;
//    double epsilon;
//    int number_of_runs;
//    double angle;
//    int number_of_branches;
//    double scale;
//    std::string type;
//    MyGraphType graph;
//    std::list<Point> clouds;
};



#endif // STATISTICINFO_H
