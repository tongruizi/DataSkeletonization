#include "controller.h"
#include "stars.h"
#include <thread>
controller::controller()
{
}

//! THIS IS HOW IT IS SUPPOSED TO LOOK LIKE. NOW IMPLEMENT STEP 1 AND STEP 2
void BeginTestRun()
{
    for (auto Algorithmit = algorithm.begin(); Algoritmit != algorithm.end(); Algorithmit++)
    {
        for (auto Cloudit = ATC.begin(); Cloudit != ATC.end(); Cloudit++)
        {
        //! Step 1: Generate cloud

        //! Step 2: Run Algorithm

        //! Step 3: Do measurments: (I will add this later)

        }

    }

}

void runing(std::list<Point> & cloud)
{
//! No comments
    //  int runing_time;

    //  vector<stars*> MyList;
//! We dont add threads before this $^&$ is running without them and when we add it,
//! Then THREADS WILL BE A VARIABLE DECLARED IN THE CLASS HEADER !!!!!!! !!!!!!! !!!!!!!!!
    //  static const int threads=7;

//a method to judge types, return true if it is star, return false if it is doublestar
//! Not required anymore
//   Boolean isStar=chooseType(std::list<Point> & cloud);
//! No no no ....
//
//    if(isStar)
//    {
//        star oneCenter;
//        oneCenter.epislon=cloud.getepislon();
//        oneCenter.specialparameter=cloud.get..();
//        //more
//        MyList.push_back(oneCenter);
//
//    }
//    else
//    {
//        doublestar moreCenter;
//        moreCenter.epislon=cloud.getepislon();
//        moreCenter.specialparameter=cloud.get..();
//        //more
//        MyList.push_back(moreCenter);
//    }
//    std::thread t[threads];
//
//    for(int i=0; i<threads; ++i)
//    {
//
//        t[i]=std::thread(computing, MyList[i]);
//        names.join();
//    }
//    std::cout<<"Launched form the main\n";
//    for (int i=0; i<threads; ++i)
//    {
//        t[i].join();
//    }
//    delete [] t;



}



