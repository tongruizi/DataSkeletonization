#include<iostream>
using namespace std;

//stat rstrcdl info
class BaseCaculate
{
protected:
    double ori;
    double max;
    double min;
    double avg;
public:
    virtual double max = 0;
    virtual double min = 0;
    virtual double avg = 0;
    add(double i)
    {
        ori = i;
    }
};




class timeCaculate: public BaseCaculate
{
    double newTime;
public:
    Caculate(double i, double j):add(i)
    {
        y = newTime;
    }
    void max()
    {
        //method
    };
    void min()
    {
        //method
    };
    void avg()
    {
        //method
    };

};

class newAlgorithms
{

public:
    virtual void Ask=0;
    virtual void mapper=0;
    virtual void AlphaReeb=0;
    run(list<Point>,myGraphType)
    {
    }
}

class Algorithm1:public newAlgorithms
{
    void Ask
    {
    };
    void mapper
    {
    };
    void AlphaReeb
    {
    };

}
class Algorithm2:public newAlgorithms
{
    void Ask
    {
    };
    void mapper
    {
    };
    void AlphaReeb
    {
    };

}


