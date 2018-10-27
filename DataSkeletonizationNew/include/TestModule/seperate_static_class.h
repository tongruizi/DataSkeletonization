#ifndef SEPERATE_STATIC_CLASS_H
#define SEPERATE_STATIC_CLASS_H


class seperate_static_class
{
public:



    virtual void addedge(int edgeN);
    static void computing(stars star);
    static int maxEdgeN(vector<int>number_of_edges );
    static int minEdgeN(vector<int>number_of_edges );
    static int avgEdgeN(vector<int>number_of_edges );
protected:

private:
    seperate_static_class();
    virtual ~seperate_static_class();
    vector<int>number_of_edges;
    int edgeN;
    int time;
    int succesful recognithon;
    int coorrect_number_of_points;
};

#endif // SEPERATE_STATIC_CLASS_H
