#ifndef ALGOSE_HIGH_LOW_H
#define ALGOSE_HIGH_LOW_H

#include <deque>
#include "Technical.h"

namespace AlgoSE
{

class ALGOSE_API HighLowEventWindow : public EventWindow<double>
{
public:
    void init(int period, bool useMin);
    void onNewValue(const DateTime& datetime, const double& value);
    double getValue() const;

private:
    bool m_useMin;
    int m_winSize;
    double m_minimun;
    double m_maximum;
    std::int64_t count;

    std::deque< std::pair<double, std::int64_t> > m_window;
};

class ALGOSE_API High : public EventBasedFilter<double, double>
{
public:
    void init(DataSeries& dataSeries, int period, int maxLen = DataSeries::DEFAULT_MAX_LEN);

private:
    HighLowEventWindow m_eventWindow;
};

class ALGOSE_API Low : public EventBasedFilter<double, double>
{
public:
    void init(DataSeries& dataSeries, int period, int maxLen = DataSeries::DEFAULT_MAX_LEN);

private:
    HighLowEventWindow m_eventWindow;
};

ALGOSE_API int SwingHigh(const DataSeries& dataSeries, int leftStrength, int rightStrength);

ALGOSE_API int SwingLow(const DataSeries& dataSeries, int leftStrength, int rightStrength);

} // namespace AlgoSE

#endif // ALGOSE_HIGH_LOW_H
