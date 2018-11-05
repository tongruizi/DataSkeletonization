#ifndef EXPLICITMEASURER_H
#define EXPLICITMEASURER_H


//! this is the true interface class
class ExplicitMeasurer
{
    public:
        ExplicitMeasurer() {}
        virtual std::string returnStatisticString() = 0;
        virtual void run( MyGraphType & G )=0;
        virtual void resetStatistic() = 0;
    protected:

    private:
};

#endif // EXPLICITMEASURER_H
