#include "seperate_static_class.h"

seperate_static_class::seperate_static_class()
{
    //ctor
}


void computing(stars star)
{
    try
    {
        for(int i=0; i<star.running_times; i++)
        {
            edgeN=star.getNumEdge();
            //paralel programming part
            addedge(int edgeN);
        }
        int maxedgeN=maxEdgeN(number_of_edges);
        int mindegeN=minEdgeN(number_of_edges);
        int avgedgeN=avgEdgeN(number_of_edges );
        cout<<"maximum number of edges:"<<maxedgeN<<"minimum number of edges:"<<mindegeN<<"average number of edges:"<<avgedgeN<<endl;
    }
    catch(std::exception& e)
    {
        cout<<e.what()<<endl;
    }

}

void addedge(int edgeN)
{
    number_of_edges.push_back(edge);

}

int maxEdgeN(vector<int>number_of_edges )
{
    int edgeN=0;
    for (it = number_of_edges.begin(); it != number_of_edges.end(); it++)
    {
        if(edgeN<it)
        {
            edgeN=it;
        }
        return edgeN;

    }

    int minEdgeN(vector<int>number_of_edges )
    {
        int edgeN=0;
        for (it = number_of_edges.begin(); it != number_of_edges.end(); it++)
        {
            if(edgeN>it)
            {
                edgeN=it;
            }
            return edgeN;

        }

        int avgEdgeN(vector<int>number_of_edges )
        {
            int sumedgeN=0;
            int avgedgeN=0;
            for (it = number_of_edges.begin(); it != number_of_edges.end(); it++)
            {

                sumedgeN=sumedgeN+it;
            }
            avgedgeN=sumedgeN/number_of_edges.size();
            return avgedgeN;

        }

