#ifndef CONTROLLER_H
#define CONTROLLER_H


class controller
{
public:
    controller();


    static void runing(std::vector<AbstractCloudType> ACT);
protected:

private:
    std::vector<AbstractCloudType> ACT;

    int running_times;
    int number_of_cloudpoints;
    double epsilon;
    int number_of_runs;
    double angle;
    int number_of_branches;
    double scale;
};

#endif // CONTROLLER_H
