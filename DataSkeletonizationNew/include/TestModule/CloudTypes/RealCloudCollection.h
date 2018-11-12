#ifndef REALCLOUDCOLLECTION_H
#define REALCLOUDCOLLECTION_H

#include <boost/filesystem.hpp>
#include "AbstractCloudType.h"

class RealCloudCollection : public AbstractCloudType
{
    public:
        RealCloudCollection(std::string nameOfInstance, std::string pathName);
        bool IsGraphCorrect(MyGraphType & G)
        {
        return true;
        }
        bool DoesGraphHaveCorrectForm(MyGraphType & G)
        {
        return true;
        }
        void GenerateCloud(std::list<Point> & p, int iterationNumber);


    protected:

    private:
    std::vector<boost::filesystem::directory_entry> directories;
};

#endif // REALCLOUDCOLLECTION_H
