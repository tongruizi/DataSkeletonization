#include "StatisticInfo.h"
#include "Graph.h"
#include "GraphGeneration.h"
StatisticInfo::StatisticInfo()
{
    MyGraphType const input_graph;
    AlphaReeb_Parameters const parameters;
    MyGraphType alphaReeb_graph;
    MyGraphType InterMediate;
    std::string type;
    int n_i;
    double o_r;
    std::string const f_f;
    double s;
    double m ;
    void seleAlgorithm(std::string type)
    {
        if(type="AlphaReeb")
        {
            AlphaReebComputation( MyGraphType const& input_graph, AlphaReeb_Parameters const& parameters, MyGraphType& alphaReeb_graph,MyGraphType& InterMediate);


        }
        else(type="Mapper")
        {
            Mapper_Parameters( int n_i, double o_r, std::string const& f_f, double s, double m );
        }
    }




}
/*StatisticInfo::~StatisticInfo()
{
    //dtor
}
*/
