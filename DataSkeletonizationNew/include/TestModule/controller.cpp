#include "controller.h"
#include "stars.h"
#include <thread>
controller::controller()
{

    //ctor
}

void runing(std::list<Point> & cloud){
int runing_time;
vector<stars*> MyList;
vector<int>number_of_edges;
static const int threads=7;

//a method to judge types, return true if it is star, return false if it is doublestar
Boolean isStar=typeJudge(std::list<Point> & cloud);


if(isStar){
   star oneCenter;
   oneCenter.epislon=cloud.getepislon();
   oneCenter.specialparameter=cloud.get..();
    //more
   MyList.push_back(oneCenter);

}
else{
   doublestar moreCenter;
   moreCenter.epislon=cloud.getepislon();
   moreCenter.specialparameter=cloud.get..();
   //more
   MyList.push_back(moreCenter);
}
std::thread t[threads];

for(int i=0;i<threads;++i){

   t[i]=std::thread(computing, MyList[i]);
   names.join();
   }
   std::cout<<"Launched form the main\n";
   for (int i=0;i<threads;++i){
   t[i].join();
   }
   delete [] t;
}

void computing(stars star){
   for(int i=0;i<star.running_times;i++){
   edgeN=star.getNumEdge();
   //paralel programming part
   addedge(int edgeN);
   }
   int maxedgeN=maxEdgeN(number_of_edges);
   int mindegeN=minEdgeN(number_of_edges);
   int avgedgeN=avgEdgeN(number_of_edges );
   cout<<"maximum number of edges:"<<maxedgeN<<"minimum number of edges:"<<mindegeN<<"average number of edges:"<<avgedgeN<<"/n";
}

void addedge(int edgeN){
number_of_edges.push_back(edge);

}

int maxEdgeN(vector<int>number_of_edges ){
int edgeN=0;
for (it = number_of_edges.begin(); it != number_of_edges.end(); it++){
if(edgeN<it){
edgeN=it;
}
return edgeN;

}

int minEdgeN(vector<int>number_of_edges ){
int edgeN=0;
for (it = number_of_edges.begin(); it != number_of_edges.end(); it++){
if(edgeN>it){
edgeN=it;
}
return edgeN;

}

int avgEdgeN(vector<int>number_of_edges ){
int sumedgeN=0;
int avgedgeN=0;
for (it = number_of_edges.begin(); it != number_of_edges.end(); it++){

sumedgeN=sumedgeN+it;
}
avgedgeN=sumedgeN/number_of_edges.size();
return avgedgeN;

}



}



