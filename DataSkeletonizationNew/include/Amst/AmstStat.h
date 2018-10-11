#ifndef AMSTSTAT_H
#define AMSTSTAT_H

#include <mlpack/prereqs.hpp>
#include <mlpack/methods/emst/dtb_stat.hpp>


class AmstStat : public mlpack::emst::DTBStat
{
private:
    double minFf;
    double maxFf;
public:
    AmstStat():
        minFf(DBL_MAX),
        maxFf(0) {}

    template<typename TreeType>
    AmstStat(const TreeType& node):
        minFf(DBL_MAX),
        maxFf(0),
        DTBStat(node)
    {

    }

    double minF() const
    {
        return minFf;
    }
    double maxF() const
    {
        return maxFf;
    }
    double& minF()
    {
        return minFf;
    }
    double& maxF()
    {
        return maxFf;
    }

protected:



};

#endif // AMSTSTAT_H
