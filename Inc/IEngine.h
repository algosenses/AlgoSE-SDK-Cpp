#ifndef ENGINE_INTERFACE_H
#define ENGINE_INTERFACE_H

#include "Defines.h"

namespace AlgoSE
{

class Strategy;
class StrategyConfig;

class ALGOSE_API IEngine
{
public:
    class Listener {
    public:
        virtual ~Listener() {}
        virtual void onSystemLog(const SystemLog& log) {}
        virtual void onServiceStatus(const ServiceStatus& status) {}
        virtual void onAccountDetails(const AccountDetails& account) {}
        virtual void onAccountPosition(const AccountPosition& position) {}
        virtual void onTick(const Tick& tick) {}
        virtual void onBar(const Bar& bar) {}
        virtual void onOrderStatus(const Order& order) {}
        virtual void onExecutionReport(const Execution& execution) {}
        virtual void onStrategyStatus(const StrategyStatus& status) {}
        virtual void onStrategyParameter(const StrategyParam& param) {}
        virtual void onStrategyPosition(const StrategyPosition& position) {}
        virtual void onStrategyLog(const StrategyLog& log) {}
        virtual void onRemoteConnect() {}
        virtual void onRemoteDisconnect() {}
    };

    class MarketDataAPI {
    public:
        virtual ~MarketDataAPI() {}
        virtual int    subscribe(const char** instruments, int num, int srvId =  0) = 0;
        virtual bool   subscribe(const char* instrument, int srvId =  0) = 0;
        virtual double getTickSize(const char* instrument, int srvId =  0) = 0;
        virtual double getLastPrice(const char* instrument, int srvId =  0) = 0;
        virtual double getAskPrice(const char* instrument, int srvId =  0) = 0;
        virtual double getBidPrice(const char* instrument, int srvId =  0) = 0;
        virtual double getUpperLimitPrice(const char* instrument, int srvId =  0) = 0;
        virtual double getLowerLimitPrice(const char* instrument, int srvId =  0) = 0;
    };

    class TradingAPI {
    public:
        virtual ~TradingAPI() {}
        virtual bool buy(const char* instrument, double quantity, double price, char* clOrdId = nullptr, int srvId =  0) = 0;
        virtual bool sell(const char* instrument, double quantity, double price, char* clOrdId = nullptr, int srvId = 0) = 0;
        virtual bool sellShort(const char* instrument, double quantity, double price, char* clOrdId = nullptr, int srvId = 0) = 0;
        virtual bool buyToCover(const char* instrument, double quantity, double price, char* clOrdId = nullptr, int srvId = 0) = 0;
        virtual bool submitOrder(const Order& order) = 0;
        virtual bool cancelOrder(const Order& order) = 0;
        virtual bool cancelOrder(const char* clOrdId) = 0;
        virtual void closeAllPos() = 0;
    };

    /*  API collections for engine and strategy controlling. */
    virtual ~IEngine() {}
    virtual bool registerListener(Listener* listener) = 0;
    virtual bool unregisterListener(Listener* listener) = 0;
    virtual int  loadStrategy(const char* config) = 0;
    virtual int  loadStrategy(Strategy& strategy, const StrategyConfig& config) = 0;
    virtual int  loadStrategy(const StrategyConfig& config) = 0;
    virtual bool run() = 0;
    virtual bool launchStrategy(int stratId) = 0;
    virtual int  getStrategyStatus(int stratId) const = 0;
    virtual bool assignStrategyPosition(int stratId, const char* instrument, int side, int quantity, double price) = 0;
    virtual bool sendStrategyCommand(int stratId, const char* command) = 0;
    virtual bool setStrategyParameter(int stratId, const StrategyParam& param) = 0;
    virtual bool showVerboseMsg(int stratId) = 0;
    virtual bool hideVerboseMsg(int stratId) = 0;
    virtual bool pauseStrategy(int stratId) = 0;
    virtual bool resumeStrategy(int stratId) = 0;
    virtual bool stopStrategy(int stratId) = 0;
    virtual void writeLogMsg(int level, const char* msg) = 0;
    virtual MarketDataAPI* getMarketDataAPI() = 0;
    virtual TradingAPI*    getTradingAPI() = 0;
    virtual bool stop() = 0;
    virtual int  version() = 0;
};

} // namespace AlgoSE

#endif // ENGINE_INTERFACE_H