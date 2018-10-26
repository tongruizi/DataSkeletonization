#ifndef STATISTICINFO_H
#define STATISTICINFO_H


class StatisticInfo
{
    public:
        StatisticInfo();
   //     virtual ~StatisticInfo();

        static void run( MyGraphType & G, std::list<Point> & points)=0;
    protected:

    private:
};

#endif // STATISTICINFO_H
