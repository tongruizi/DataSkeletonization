#ifndef STARS_H
#define STARS_H



class stars
{
public:


    virtual void GenerateClouud(std::list<Point> & p) =0;


protected:

private:
    std::list<Point> & cloud;
    int getNumEdge()=0;
    int running_times;
    int number_of_cloudpoints;
    double epsilon;
    int number_of_runs;
    double angle;
    int number_of_branches;
    double scale;
}

class star:stars
{
public:

    virtual void GenerateClouud(std::list<Point> & p)
    {

    }

}
class doubleStar:stars
{
public:

    int branch_centers;
    virtual void GenerateClouud(std::list<Point> & p)
    {

    }


}

#endif // STARS_H
