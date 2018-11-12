#include "RealCloudCollection.h"
#include "AbstractCloudType.h"
#include "GeneralConvertor.h"

RealCloudCollection::RealCloudCollection(std::string nameOfInstance, std::string pathName):
    AbstractCloudType(0,nameOfInstance)
{
    boost::filesystem::path p(pathName);
    std::copy(boost::filesystem::directory_iterator(p), boost::filesystem::directory_iterator(), back_inserter(this->directories));
    this->number_of_runs = (this->directories).size();
}


void RealCloudCollection::GenerateCloud(std::list<Point> & p, int iterationNumber)
{
    std::string kkk = (this->directories)[iterationNumber].path().string();
    GeneralConvertor::XYZtoPoint(kkk,p);
}

//void FileSystemTest()
//{
////std::string p = "/home/yury/Dropbox/UnileverData/VTK_First_Files/";
//boost::filesystem::path p("/home/yury/Dropbox/UnileverData/VTK_First_Files/");
//std::vector<boost::filesystem::directory_entry> v; // To save the file names in a vector.
//
//    if(boost::filesystem::is_directory(p))
//    {
//        copy(boost::filesystem::directory_iterator(p), boost::filesystem::directory_iterator(), back_inserter(v));
//        std::cout << p << " is a directory containing:\n";
//
//        for ( std::vector<boost::filesystem::directory_entry>::const_iterator it = v.begin(); it != v.end();  ++ it )
//        {
//            std::cout<< (*it).path().string()<<endl;
//        }
//    }
//
//}
