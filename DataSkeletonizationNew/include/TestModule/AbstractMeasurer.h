#ifndef ABSTRACTMEASURER_H
#define ABSTRACTMEASURER_H

template <class T>
class AbstractMeasurer
{
  public:
  virtual T CompleteMeasurments(MyGraphType & G) =0;
  virtual void Append(MyGraphType & G)=0;
  private:

  StatisticInfo <unit> mystatistic;
};




#endif // ABSTRACTMEASURER_H
