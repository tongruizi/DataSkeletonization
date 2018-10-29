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
    unit returnMax()
    {
        return maxValue;
    }
    unit returnMin()
    {
        return minValue;
    }
    void reset(){
     number=0;
     sum=0;
     avg=0;
     maxValue=0;
     minValue=0;


    }



protected:

private:

//! This is number of measurments: For now its always double, so we dont get stupid errors when dividing stuff
    double number;
//! sum is unit
    unit sum;
//! but average is always double!!!!
    double avg;

    unit maxValue;
    unit minValue;

};





#endif // STATISTICINFO_H
