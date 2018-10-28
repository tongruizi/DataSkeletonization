#ifndef CONTROLLER_H
#define CONTROLLER_H


class controller
{
public:
    controller();

    void BeginTestRun();


    void addAlgorithm(AbstractAlgorithm & k);
    void addCloud(generatable & k);

protected:

private:
    //! Vector for cloudtypes:
    std::vector<generatable> ACT;
    //! Vector for algorithmtypes:
    std::vector<AbstractAlgorithm> algorithms;
    std::vector<AbstractMeasurer> measurers ;
    StatisticInfo<int> correctRecognition;
    StatisticInfo<double> MinMaxError;

};

#endif // CONTROLLER_H
