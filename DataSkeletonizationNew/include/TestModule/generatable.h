#ifndef STARS_H
#define STARS_H

#include "CloudGenerator.h"
#include "GraphGeneration.h"


class generatable
{
public:


    public generatable(number_of_cloudpoints, epsilon):
        number_of_cloudpoints(number_of_cloudpoints), epsilon(epsilon)
    {

    }
    virtual void GenerateGraph(MyGraphType & G) =0;
    void GenerateCloud(std::list<Point> & p)
    {
        MyGraphType G;
        GenerateGraph(G);
        CloudGenerator::generatePoints(number_of_cloudpoints, G, epsilon,p);
    }


protected:

private:
    //! And here we go again. I told you, no extra $%^$ here ! :D
    //! Only those 3 variables are required here

    int number_of_cloudpoints;
    double epsilon;

}


class SingleStar:public generatable
{
public:

    SingleStar(double angle, int number_of_branches, double scale, int number_of_cloudpoints, double epsilon, double scale):
    generatable(number_of_cloudpoints,epsilon),angle(angle), number_of_branches(number_of_branches),scale(scale)
    {

    }
    void GenerateGraph(MyGraphType & G)
    {
        GraphGeneration::RandomGraph1(number_of_branches,angle,scale,G)
    }

private:
    double angle;
    int number_of_branches;
    double scale;
}
class doubleStar:public generatable
{
public:
    //! Implement this, as in single star. Note that we have an extra parameter...
    doubleStar(double angle, int number_of_branches,int number_of_branches2, int number_of_cloudpoints, double epsilon, double scale):
     generatable(number_of_cloudpoints,epsilon),angle(angle), number_of_branches(number_of_branches), number_of_branches2(number_of_branches2),scale(scale)
    {

    }
    /*or doubleStar(double angle, int number_of_branches,int number_of_branches2, int number_of_cloudpoints, double epsilon, double scale):
     generatable(number_of_cloudpoints,epsilon),angle(angle), number_of_branches(number_of_branches), number_of_branches(number_of_branches2),scale(scale)
    {

    }*/
    void GenerateGraph(MyGraphType & G)
    {
        GraphGeneration::RandomGraph2(number_of_branches, number_of_branches2, angle, scale, G);
    }
private:
//! Variables here:
    double angle;
    int number_of_branches;
    int number_of_branches2;
    double scale;

}

#endif // STARS_H
