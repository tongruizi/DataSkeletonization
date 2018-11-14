#ifndef SINGLESTAR_H
#define SINGLESTAR_H

#include "CloudGenerator.h"
#include "GraphGeneration.h"
#include "generatable.h"

class SingleStar:public generatable
{
public:
    SingleStar(double angle, int number_of_branches, int number_of_cloudpoints, double epsilon, double scale,int number_of_runs,
               std::string name = "SingleStar"):
        generatable(number_of_cloudpoints,epsilon,number_of_runs,name),angle(angle), number_of_branches(number_of_branches),scale(scale)
    {

    }
    void GenerateGraph(MyGraphType & G)
    {
        GraphGeneration::RandomGraph1(number_of_branches,angle,scale,G);
    }

    bool IsGraphCorrect(MyGraphType & G, int iterationnumber)
    {
        int n = number_of_branches;
        auto vpair = boost::vertices(G);
        int degree1 = 0;
        int starn = 0;
        for (auto it = vpair.first; it != vpair.second; it++)
        {
            int tmpD = boost::degree(*it, G);
            if (tmpD == 1)
            {
                degree1++;
            }
            else if (tmpD == n)
            {
                starn++;
            }
            else if ((tmpD != 2) && (tmpD != n) && (tmpD != 1))
            {
                return false;
            }
        }
        return (starn == 1) && (degree1 == number_of_branches);

    }

    bool DoesGraphHaveCorrectForm(MyGraphType & G,int iterationnumber)
    {
        return this->CorrectNumberOfEndPoints(G,number_of_branches);
    }



private:
    double angle;
    int number_of_branches;
    double scale;
};

#endif // SINGLESTAR_H
