#include "controller.h"
#include "stars.h"
#include <thread>
controller::controller()
{
}

void runing(std::list<Point> & cloud)
{
    int runing_time;
    vector<stars*> MyList;

    static const int threads=7;

//a method to judge types, return true if it is star, return false if it is doublestar
    Boolean isStar=chooseType(std::list<Point> & cloud);


    if(isStar)
    {
        star oneCenter;
        oneCenter.epislon=cloud.getepislon();
        oneCenter.specialparameter=cloud.get..();
        //more
        MyList.push_back(oneCenter);

    }
    else
    {
        doublestar moreCenter;
        moreCenter.epislon=cloud.getepislon();
        moreCenter.specialparameter=cloud.get..();
        //more
        MyList.push_back(moreCenter);
    }
    std::thread t[threads];

    for(int i=0; i<threads; ++i)
    {

        t[i]=std::thread(computing, MyList[i]);
        names.join();
    }
    std::cout<<"Launched form the main\n";
    for (int i=0; i<threads; ++i)
    {
        t[i].join();
    }
    delete [] t;
}


}



