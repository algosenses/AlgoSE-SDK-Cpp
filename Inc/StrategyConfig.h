#ifndef ALGOSE_STRATEGY_CONFIG_H
#define ALGOSE_STRATEGY_CONFIG_H

#include "Defines.h"

namespace AlgoSE
{

class Strategy;
class StrategyConfigImpl;

extern "C" typedef Strategy *StrategyCreator();

class ALGOSE_API StrategyConfig
{
public:
    StrategyConfig();
    StrategyConfig(const StrategyConfig& other);
    ~StrategyConfig();
    StrategyConfig &operator=(const StrategyConfig& other);

    void             setName(const char* name);
    const char*      getName() const;
    void             setDescription(const char* desc);
    const char*      getDescription() const;
    void             setAuthor(const char* author);
    const char*      getAuthor() const;
    void             setSharedLibrary(const char* library);
    const char*      getSharedLibrary() const;
    void             setStrategyCreator(StrategyCreator* creator);
    StrategyCreator* getStrategyCreator() const;

    // Subscribe instrument.
    void subscribe(const char* instrument, int resolution = Resolution::TICK, int interval = 0, int backRefNum = 0);
    void enableAlgoTrader();
    void disableAlgoTrader();
    bool isAlgoTraderEnabled() const;
    void enableAutoStart();
    void disableAutoStart();
    bool isAutoStartDisabled() const;
    void setAcceptAllOrders(bool onoff);
    bool isAcceptAllOrders() const;
    void directActOnAcctPos(bool onoff);
    bool isDirectActOnAcctPos() const;
    bool setPosition(const char* instrument, int side, int quantity, double price, 
                     const TimeStamp& ts, double highest, double lowest);
    bool addTradingHour(const char* instrument, const TradingHour& hour);

    StrategyConfig& setUserParameter(const StrategyParam& item);
    StrategyConfig& setUserParameter(const char* name, int value);
    StrategyConfig& setUserParameter(const char* name, double value);
    StrategyConfig& setUserParameter(const char* name, bool value);
    StrategyConfig& setUserParameter(const char* name, const char* value);
    StrategyConfig& setOptimizeParameter(const char* name, double start, double end, double step);
//    template <typename T1, typename T2>
//    StrategyConfig& setUserParameter(T1 name, T2 value) = delete;
    StrategyConfig& setAlgoTraderParameter(int id, double value);
    StrategyConfig& setAlgoTraderParameter(const char* name, const char* value);

    const StrategyConfigImpl& getImplementor() const;

private:
    StrategyConfigImpl* m_implementor;
};

} // namespace AlgoSE

#endif // ALGOSE_STRATEGY_CONFIG_H