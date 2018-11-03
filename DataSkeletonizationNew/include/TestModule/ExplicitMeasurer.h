#ifndef EXPLICITMEASURER_H
#define EXPLICITMEASURER_H


//! this is the true interface class
class ExplicitMeasurer
{
    public:
        ExplicitMeasurer() {}
        virtual std::string returnStatisticData() = 0;
        virtual void letrun( MyGraphType & G )=0;
    protected:

    private:
};

#endif // EXPLICITMEASURER_H
