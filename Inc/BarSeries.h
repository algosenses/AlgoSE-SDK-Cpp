#ifndef ALGOSE_BAR_SERIES_H
#define ALGOSE_BAR_SERIES_H

#include "DataSeries.h"
#include "Defines.h"

namespace AlgoSE
{

class ALGOSE_API TickSeries : public SequenceDataSeries<Tick>
{
public:
    TickSeries(int maxLen = DataSeries::DEFAULT_MAX_LEN);
    void append(const Tick& bar);
    void appendWithDateTime(const DateTime& datetime, const void* value);
    DataSeries& getLastPriceDataSeries();
    DataSeries& getBidPrice1DataSeries();
    DataSeries& getBidVolume1DataSeries();
    DataSeries& getAskPrice1DataSeries();
    DataSeries& getAskVolume1DataSeries();

private:
    SequenceDataSeries<double> m_lastPriceDS;
    SequenceDataSeries<double> m_bidPrice1DS;
    SequenceDataSeries<long long> m_bidVolume1DS;
    SequenceDataSeries<double> m_askPrice1DS;
    SequenceDataSeries<long long> m_askVolume1DS;
};

// A DataSeries of Bar instances.
class ALGOSE_API BarSeries : public SequenceDataSeries<Bar>
{
public:
    // @param: maxLen: The maximum number of values to hold.
    // Once a bounded length is full, when new items are added, a corresponding number of items are discarded from the opposite end.
    BarSeries(int maxLen = DataSeries::DEFAULT_MAX_LEN);
    void setResolution(int resolution);
    int  getResolution() const;
    void setInterval(int interval);
    int  getInterval() const;
    void append(const Bar& bar);
    void appendWithDateTime(const DateTime& datetime, const void* value);

    // Returns a `DataSeries` with the open prices.
    DataSeries& getOpenDataSeries();
    // Returns a `DataSeries` with the close prices.
    DataSeries& getCloseDataSeries();
    // Returns a `DataSeries` with the high prices.
    DataSeries& getHighDataSeries();
    // Returns a `DataSeries` with the low prices.
    DataSeries& getLowDataSeries();
    // Returns a `DataSeries` with the volume.
    DataSeries& getVolumeDataSeries();
    // Returns a `DataSeries` with the open interest.
    DataSeries& getOpenIntDataSeries();
    // Returns a `DataSeries` with the close or adjusted close prices.
    DataSeries& getPriceDataSeries();

private:
    int m_resolution;
    int m_interval;

    SequenceDataSeries<double> m_openDS;
    SequenceDataSeries<double> m_highDS;
    SequenceDataSeries<double> m_lowDS;
    SequenceDataSeries<double> m_closeDS;
    SequenceDataSeries<long long> m_volumeDS;
    SequenceDataSeries<long long> m_openIntDS;
};

} // namespace AlgoSE

#endif // ALGOSE_BAR_SERIES_H
