#ifndef ALGOSE_STRATEGY_H
#define ALGOSE_STRATEGY_H

#include "Defines.h"
#include "BarSeries.h"
#include "OrderList.h"
#include "PositionList.h"
#include "AlgoOrder.h"
#include "StrategyConfig.h"

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the STRATEGY_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// STRATEGY_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#if defined(__PLATFORM_WINDOWS__)
    #ifdef STRATEGY_EXPORTS
        #define STRATEGY_API __declspec(dllexport)
    #else
        #define STRATEGY_API __declspec(dllimport)
    #endif
#elif defined(__PLATFORM_LINUX__)
    #ifdef STRATEGY_EXPORTS
        #define STRATEGY_API __attribute__((visibility("default")))
    #else
        #define STRATEGY_API 
    #endif
#else
    #define STRATEGY_API
#endif

namespace AlgoSE
{

class IRuntime;

class STRATEGY_API Strategy
{
public:
    enum State {
        UNKNOWN = 0,
        LOADING,        // Loading and filling historical data.
        RUNNING,        // Receiving realtime market data.
        PAUSED,
        STOPPED,
        UNLOADED,
    };

    Strategy();
    virtual ~Strategy();

    void         attach(IRuntime* runtime);
    virtual void onCreate() {}
    virtual void onSetParameter(const char* name, int type, const char* value, bool isLast) {}
    virtual int  onBarSeriesFeed(const char* instrument, int resolution, int interval, int num, Tick* buffer) { return 0; }
    virtual void onStart() {}
    virtual void onTick(const Tick& tick) {}
    virtual void onBar(const Bar& bar) {}

    virtual void onOrderSubmitted(const Order& order) {}
    virtual void onOrderUpdated(const Order& order) {}
    virtual void onExecutionReport(const Execution& exec) {}
    virtual void onOrderPartiallyFilled(const Order& order) {}
    // This method is called when an order is filled.
    virtual void onOrderFilled(const Order& order) {}
    // This method is called when an order is rejected.
    virtual void onOrderRejected(const Order& order) {}
    virtual void onOrderReplaced(const Order& order) {}
    virtual void onOrderReplaceRejected(const Order& order) {}
    // This method is called when an order is cancelled.
    virtual void onOrderCancelled(const Order& order) {}
    virtual void onOrderCancelRejected(const Order& order) {}

    virtual bool onAlgoOrderSubmitted(AlgoOrder* order) { return false; }
    virtual bool onAlgoOrderPartiallyFilled(AlgoOrder* order) { return false; }
    // This method is called when an algorithmic order is temporarily failed.
    virtual bool onAlgoOrderUpdated(AlgoOrder* order) { return false; }
    virtual void onAlgoOrderFilled(const AlgoOrder& order) {}
    virtual void onAlgoOrderFailed(const AlgoOrder& order) {}

    virtual void onHistoricalDataRequestAck(const HistoricalDataRequest& request) {}
    virtual void onCommand(const char* command) {}
    virtual void onTimer(int timerId) {}
    virtual void onEnvVariable(const char* name, const char* value) {}
    virtual void onPause() {}
    virtual void onResume() {}
    virtual void onStop() {}
    virtual void onDestory() {}

public:
    // Convenient wrapper functions.
    int  run(const StrategyConfig& config, const char* srvAddr = nullptr, int srvPort = 0);
    bool sendCommand(const char* command);
    bool setVerbosity(bool onoff);
    bool pause();
    bool resume();
    bool stop();

protected:
    int         getId() const;
    int         getStatus() const;
    const char* getName() const;
    const char* getMainInstrument() const;
    TickSeries* getTickSeries(const char* instrument = "");
    BarSeries*  getBarSeries(const char* instrument = "", int resolution = Resolution::MINUTE, int interval = 1);
    
    // If paper trading is enabled, strategy's onBar() function will be called
    // using historical data, thus simulative trading signal will be generated
    // and printed, when historical data playback is done, strategy will switch 
    // to live mode automatically.
    void   enablePaperTrading();
    void   setFastFlowMode(bool onoff);

    bool   openLong(const char* instrument = "", double quantity = 1, char* clOrdId = nullptr);
    bool   closeLong(const char* instrument = "", char* clOrdId = nullptr);
    bool   openShort(const char* instrument = "", double quantity = 1,  char* clOrdId = nullptr);
    bool   closeShort(const char* instrument = "", char* clOrdId = nullptr);

    bool   buy(const char* instrument, double quantity, double price, char* clOrdId = nullptr, int srvId = 0);
    bool   sell(const char* instrument, double quantity, double price, char* clOrdId = nullptr, int srvId = 0);
    bool   sellShort(const char* instrument, double quantity, double price, char* clOrdId = nullptr, int srvId = 0);
    bool   buyToCover(const char* instrument, double quantity, double price, char* clOrdId = nullptr, int srvId = 0);
    const AlgoParams& getDefaultAlgoParams() const;
    bool   algoBuy(const char* instrument, double quantity, double price, const AlgoParams* params = nullptr, char* clOrdId = nullptr, int srvId = 0);
    bool   algoSell(const char* instrument, double quantity, double price, const AlgoParams* params = nullptr, char* clOrdId = nullptr, int srvId = 0);
    bool   algoSellShort(const char* instrument, double quantity, double price, const AlgoParams* params = nullptr, char* clOrdId = nullptr, int srvId = 0);
    bool   algoBuyToCover(const char* instrument, double quantity, double price, const AlgoParams* params = nullptr, char* clOrdId = nullptr, int srvId = 0);
    Order  createMarketOrder(int action, const char* instrument, double quantity, int srvId = 0);
    Order  createLimitOrder(int action, const char* instrument, double limitPrice, double quantity, int srvId = 0);
    void   setDefaultExecSrvId(int id);
    int    getServiceId(const char* name, int type);
    bool   subscribe(const char* instrument, int resolution = Resolution::TICK, int interval = 1, int srvId = 0);
    bool   unsubscribe(const char* instrument, int resolution = Resolution::TICK, int interval = 1, int srvId = 0);
    bool   submitOrder(Order& order);
    bool   splitOrder(Order& order, OrderList& ordGroup);
    int    getOrderStatus(const char* clOrdId);
    Order  getOrderSnapshot(const char* clOrdId);
    int    getPendingOrders(OrderList& list, const char* instrument = "");
    int    getAccountPendingOrders(OrderList& list, const char* instrument = "");
    bool   cancelOrder(const char* clOrdId);
    bool   cancelOrder(const Order& order);
    bool   isOrderPending(const char* clOrdId);
    long   registerTimer(int msFromNow);
    void   unregisterTimer(int timerId);
    void   setEnv(const char* name, const char* value);
    void   unsetEnv(const char* name);
    void   monitorEnv(const char* name);
    unsigned long getSysTickCount();
    bool   saveUserParameter(const char* name, const char* value);
    // Sync read.
    int    loadHistoricalData(const char* instrument, int resolution, int interval, int refNum, HistoricalData* buffer, int srvId = 0);
    // Async read.
    int    requestHistoricalData(const char* instrument, int resolution, int interval, int refNum, HistoricalData* buffer, int srvId = 0);

    // Price fetching functions
    double getMultiplier(const char* instrument = "");
    double getTickSize(const char* instrument = "");
    double getLastPrice(const char* instrument = "");
    double getAskPrice(const char* instrument = "");
    double getBidPrice(const char* instrument = "");

    // Position fetching functions
    int    getAccountPositions(AccountPositionList& list, const char* instrument = "", bool includeClosed = false);
    int    getStrategyPositions(StrategyPositionList& list, const char* instrument = "");
    double getTotalPosSize(const char* instrument = "");

    double getLongPosSize(const char* instrument = "");
    void   getLongPosSize(double* closable, double* frozen, double* unformed);
    void   getLongPosSize(const char* instrument, double* closable, double* frozen, double* unformed);
    StrategyPosition getLongPos(const char* instrument = "");

    double getShortPosSize(const char* instrument = "");
    void   getShortPosSize(double* closable, double* frozen, double* unformed);
    void   getShortPosSize(const char* instrument, double* closable, double* frozen, double* unformed);
    StrategyPosition getShortPos(const char* instrument = "");

    double getClosableLongPosSize(const char* instrument = "");
    StrategyPosition getClosableLongPos(const char* instrument = "");

    double getClosableShortPosSize(const char* instrument = "");
    StrategyPosition getClosableShortPos(const char* instrument = "");

    double getFrozenLongPosSize(const char* instrument = "");
    double getFrozenShortPosSize(const char* instrument = "");

    double getUnformedLongPosSize(const char* instrument = "");
    double getUnformedShortPosSize(const char* instrument = "");

    double getAcctClosableLongPosSize(const char* instrument = "", int srvId = 0);
    StrategyPosition getAcctClosableLongPos(const char* instrument = "", int srvId = 0);

    double getAcctClosableShortPosSize(const char* instrument = "", int srvId = 0);
    StrategyPosition getAcctClosableShortPos(const char* instrument = "", int srvId = 0);

    double getAcctLongPosSize(const char* instrument = "", int srvId = 0);
    double getAcctHistLongPosSize(const char* instrument = "", int srvId = 0);
    double getAcctLongPos(const char* instrument, double* price, TimeStamp* ts, int srvId = 0);
    StrategyPosition getAcctLongPos(const char* instrument = "", int srvId = 0);

    double getAcctShortPosSize(const char* instrument = "", int srvId = 0);
    double getAcctHistShortPosSize(const char* instrument = "", int srvId = 0);
    double getAcctShortPos(const char* instrument, double* price, TimeStamp* ts, int srvId = 0);
    StrategyPosition getAcctShortPos(const char* instrument = "", int srvId = 0);

    bool   assignLongPosition(const char* instrument, double quantity, double price, const TimeStamp& timestamp,
                              double frozen = 0, double highest = 0, double lowest = 0);
    bool   assignShortPosition(const char* instrument, double quantity, double price, const TimeStamp& timestamp, 
                               double frozen = 0, double highest = 0, double lowest = 0);

    double getAcctUnrealizedPnL(int srvId = 0) const;
    double getAcctRealizedPnL(int srvId = 0) const;
    double getInstrumentUnrealizedPnL() const;
    double getInstrumentRealizedPnL() const;

    bool   setStopLossAmount(const char* instrument, int side, double amount);
    bool   setStopLossPrice(const char* instrument, int side, double price);
    bool   setStopLossPercent(const char* instrument, int side, double pct);
    bool   setStopLossTick(const char* instrument, int side, int tick);
    bool   setStopProfitAmount(const char* instrument, int side, double amount);
    bool   setStopProfitPrice(const char* instrument, int side, double price);
    bool   setStopProfitPct(const char* instrument, int side, double returns);
    bool   setPercentTrailing(const char* instrument, int side, double amount, double percentage);
    bool   setTrailingStop(const char* instrument, int side, double returns, double drawdown);

    void   writeLogMsg(const char* msg);
    bool   isVerbose() const;
    void   writeVerboseMsg(const char* msg);
    void   writeErrorMsg(const char* msg);

private:
    IRuntime* m_runtime;
};

#define EXPORT_STRATEGY(strategy_name)                      \
    extern "C" STRATEGY_API Strategy* CreateStrategy()      \
    {                                                       \
        return new strategy_name;                           \
    }

////////////////////////////////////////////////////////////////////////////////
// Strategy Creator Definitions
////////////////////////////////////////////////////////////////////////////////
extern "C" typedef Strategy *StrategyCreator();

// Only lambdas with no capture can be converted to a function pointer.
// This is an extension of lambdas for only this particular case.
// In general, lambdas are function objects, and you cannot convert a
// function object to a function.
// The alternative for lambdas that have state(capture) is to use
// std::function rather than a plain function pointer.
#define STRATEGY_CREATOR(strategy_name) \
    []() -> Strategy* { return new strategy_name; }

} // namespace AlgoSE

#endif // ALGOSE_STRATEGY_H