#ifndef STARS_H
#define STARS_H

#include "CloudGenerator.h"
#include "GraphGeneration.h"


class generatable
{
public:

    generatable(int number_of_cloudpoints, double epsilon, int number_of_runs,std::string name):
        number_of_cloudpoints(number_of_cloudpoints), epsilon(epsilon),number_of_runs(number_of_runs), name(name)
    {

    }

    bool CorrectNumberOfEndPoints(MyGraphType & G, int nob)
    {

        int endcount = 0;

        for (auto it = boost::vertices(G).first; it != boost::vertices(G).second; it++)
        {
            int degree = boost::degree(*it,G);
            if (degree == 1)
            {
                endcount++;
            }
        }
        return (endcount == nob);


    }

    virtual void GenerateGraph(MyGraphType & G) =0;

    virtual bool IsGraphCorrect(MyGraphType & G) =0;

    virtual bool DoesGraphHaveCorrectForm(MyGraphType & G) =0;


    void GenerateCloud(std::list<Point> & p)
    {
        MyGraphType G;
        GenerateGraph(G);
        CloudGenerator::generatePoints(number_of_cloudpoints, G, epsilon,p);
    }

    int returnNumberOfRuns()
    {
        return number_of_runs;
    }
    std::string returnName()
    {
        return name;
    }




protected:

private:

    int number_of_runs;
    int number_of_cloudpoints;
    double epsilon;
    std::string name;

};


#endif // STARS_H
