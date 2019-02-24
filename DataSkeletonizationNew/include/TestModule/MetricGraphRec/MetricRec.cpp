#include MetriRec.hpp


void run(std::list<Point> & cloudlist, double r, MyGraphType & out)
{

}

void Labeling(std::list<Point> & cloudlist, std::list<Point> & s, double r)
{
    int degre = 0;
    double toDistance = 0;
    Point prelimBranch;
    for (auto it = s.begin(); it != s.end(); it++)
    {
        std::list<Point> tempraCollect;
        for (auto him = s.begin(); him != s.end(); him++)
        {
            if (him != it)
            {
                toDistance =  sqrt(CGAL::squared_distance(*him,*it));
                if(toDistance<=5r/3 && toDistance>=r)
                {
                    tempraCollect.push_back(it);
                }
            }
        }
        //let's pretend there is a method for Number of connected components of Rips-Vietoris grap
        degre = Rips-Vietoris(tempraCollect, 4r/3).degre();
        if(degr = 2)
        {
            edgePoint.insert(it);
        }
        else
        {
            branchPoint.insert(it);
             prelimBranch = it;
        }

    }
    for (it=cloudlist.begin(); it!=cloudlist.end(); ++it)
    {
        if(*it != prelimBranch)
        {
            toDistance =  sqrt(CGAL::squared_distance(prelimBranch,*it));
            if(toDistance<=2r)
            {
                branchPoint.insert(it);

            }
        }

    }
}

void ReconstructGraph( MyGraphType & G, std::set<Point> edgePoint, std::set<Point> branchPoint, double r)
{
    //let's pretend we can caculate vertices of  Rips-Vietoris graphsR2r(E)andR2r(V).
    std::list<Point> EdgeE = Rips-Vietoris(edgePoint, 2r);
    std::list<Point> BranchV = Rips-Vietoris(branchPoint, 2r);
    double toDistance = 0;
    for (it=BranchV.begin(); it!=BranchV.end(); ++it)
    {
       Graph::add_vertex(G,it);
       for (him=BranchV.begin(); him!=BranchV.end(); ++him){
       toDistance =  sqrt(CGAL::squared_distance(*him,*it));
       if(toDistance<2r){
       Graph::add_custom_edge(G,*him,*it,toDistance+4r);
       }
       }
    }

}










