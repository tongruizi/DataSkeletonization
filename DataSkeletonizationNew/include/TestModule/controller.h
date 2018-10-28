#ifndef CONTROLLER_H
#define CONTROLLER_H


class controller
{
public:
    controller();

    void BeginTestRun();
     //! This method was such a mess that I replaced it by the method above
   // void runing(std::vector<AbstractCloudType> ACT);

    //! implement those:
    void addAlgorithm(AbstractAlgorithm & k);
    void addCloud(generatable & k);

protected:

private:
    //! Vector for cloudtypes:
    std::vector<generatable> ACT;
    //! Vector for algorithmtypes:
    std::vector<AbstractAlgorithm> algorithms;
//! NOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
//    int running_times;
//    int number_of_cloudpoints;
//    double epsilon;
//    int number_of_runs;
//    double angle;
//    int number_of_branches;
//    double scale;
//! Instead, for example:
    StatisticInfo<int> correctRecognition;
    StatisticInfo<double> MinMaxError;

};

#endif // CONTROLLER_H
