#ifndef STARS_H
#define STARS_H



class stars
{
public:
    virtual void printMe() =0;
    int getNumEdge()=0;
    int running_times;
    int number_of_cloudpoints;
    double epsilon;
    int number_of_runs;

    double angle;
    int number_of_branches;
    double scale;
    std::vector<Generalablbe> k;

    void setEpsilon(double t)
    {
        epsilon=t;
    }
    double getepsilon()
    {
        return epsilon;
    }
protected:

private:
}

class star:stars
{
public:

    //get the cloud's number of edges
    int getNumEdge()
    {
        int edgeN;
        return edgeN;
    }
    virtual void printMe(){
    }
//star parameters
}
class doubleStar:stars
{
public:
//doublestar parameter
virtual void printMe(){

}

}

#endif // STARS_H
