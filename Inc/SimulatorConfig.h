#ifndef SIMULATOR_CONFIG_H
#define SIMULATOR_CONFIG_H

#include "Defines.h"

namespace AlgoSE
{

class SimulatorConfigImpl;

class ALGOSE_API SimulatorConfig
{
public:
    enum {
        REPORT_SUMMARY       = 0x01,
        REPORT_TRADES        = 0x02,
        REPORT_POSITION      = 0x04,
        REPORT_RETURNS       = 0x08,
        REPORT_EQUITIES      = 0x10,
        REPORT_DAILY_METRICS = 0x20,
        REPORT_OPTIMIZATION  = 0x40
    };

    SimulatorConfig();
    SimulatorConfig(const SimulatorConfig& other);
    ~SimulatorConfig();
    SimulatorConfig &operator=(const SimulatorConfig& other);
    void        setRunningMode(int mode);
    int         getRunningMode() const;
    void        registerDataStream(const char* instrument, int resolution, int interval, const char* filename, int format, const Contract& contract);
    void        setCash(double cash);
    double      getCash() const;
    void        setTradingDayEndTime(int timeNum);
    int         getTradingDayEndTime() const;
    void        setProcessorNum(int num);
    void        setOptimizeMode(int mode);
    void        enableReporting(int mask);
    void        disableReporting(int mask);
    bool        isReportingEnable(int mask) const;
    void        setSummaryReportFileName(const char* filename);
    const char* getSummaryReportFileName() const;
    void        setDailyMetricsReportFileName(const char* filename);
    const char* getDailyMetricsReportFileName() const;
    void        setTradeLogFileName(const char* filename);
    const char* getTradeLogFileName() const;
    void        setPositionsReportFileName(const char* filename);
    const char* getPositionsReportFileName() const;
    void        setReturnsReportFile(const char* filename);
    const char* getReturnsReportFileName() const;
    const char* getEquitiesReportFileName() const;
    void        setOptimizationReportFileName(const char* filename);
    const char* getOptimizationReportFileName() const;

    const SimulatorConfigImpl& getImplementor() const;

private:
    SimulatorConfigImpl* m_implementor;
};

} // namespace AlgoSE

#endif // SIMULATOR_CONFIG_H