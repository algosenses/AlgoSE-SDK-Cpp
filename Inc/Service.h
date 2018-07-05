#ifndef ALGOSE_SERVICE_H
#define ALGOSE_SERVICE_H

#include "Defines.h"

namespace AlgoSE
{

#if defined(__PLATFORM_WINDOWS__)
    #ifdef SERVICE_EXPORTS
        #define SERVICE_API __declspec(dllexport)
    #else
        #define SERVICE_API __declspec(dllimport)
    #endif
#elif defined(__PLATFORM_LINUX__)
    #define SERVICE_API __attribute__((visibility("default")))
#else
    //  do nothing and hope for the best?
    #define SERVICE_API
    #pragma warning Unknown dynamic link import/export semantics.
#endif

////////////////////////////////////////////////////////////////////////////////
// Service Definitions
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    enum {
        SERVICE_UNKNOWN         = 0x00,
        SERVICE_TIMER           = 0x01,  // Timer.
        SERVICE_INSTRUMENT      = 0x02,  // Instrument definitions.
        SERVICE_MARKET_DATA     = 0x04,  // Real time market data.
        SERVICE_HISTORICAL_DATA = 0x08,  // Historical market data.
        SERVICE_ORDER_EXECUTION = 0x10,  // Trade execution.
    };
} ServiceType;

typedef struct {
    enum  {
        LOADED,
        CONNECTED,
        CONNECT_ERROR,
        DISCONNECTED,
        INITIALIZE_DONE,
    };
} MarketDataServiceState;

typedef struct {
    enum  {
        LOADED,
        CONNECTED,
        CONNECT_ERROR,
        DISCONNECTED,
        INITIALIZE_DONE,
        READY,
        RESET,
    };
} ExecutionServiceState;

typedef struct {
    enum {
        LOADED,
        CONNECTED,
        CONNECT_ERROR,
        DISCONNECTED,
        INITIALIZE_DONE,
    };
} HistoricalDataServiceState;

typedef struct {
    enum {
        LOADED,
        CONNECTED,
        CONNECT_ERROR,
        DISCONNECTED,
        INITIALIZE_DONE,
    };
} TimerServiceState;

class EngineImpl;

class ALGOSE_API ServiceBase
{
public:
    ServiceBase();
    virtual ~ServiceBase();

    virtual bool initialize(const char* config) = 0;
    virtual bool reinitialize() { return false; }
    virtual bool release() = 0;

    void setId(int id);
    int  getId() const;
    void setType(int type);
    int  getType() const;
    void setName(const char* name);
    const char* getName() const;
    void attach(EngineImpl* engine);

protected:
    const char* getParamValue(const char* name);
    void writeLog(int level, const char* fmt, ...);
    void notifyStatus(int state, const char* desc = "");

protected:
    int m_id;
    int m_type;
    char m_name[32];
    EngineImpl* m_engine;
};

#define INVALID_SERVICE_ID      (-1)

#define TIMER_SERVICE_TYPE_NAME   "Timer"

class ALGOSE_API TimerService : public ServiceBase
{
public:
    virtual int  registerTimer(int msFromNow, const char* extra, int compId, int ownerId) = 0;
    virtual void unregisterTimer(int timerId) = 0;

protected:
    void notifyTimer(TimerMsg& timerMsg);
};

extern "C" typedef TimerService *CreateTimerServiceProc();
#define EXPORT_TIMER_SERVICE(service_name)                              \
    extern "C" SERVICE_API TimerService* CreateTimerService()           \
    {                                                                   \
        return new service_name;                                        \
    }

#define INSTRUMENT_SERVICE_TYPE_NAME   "Instrument"

class ALGOSE_API SecurityDefinitionService : public ServiceBase
{
protected:
    void notifySecurityDefinition(SecurityDefinition& security);
};

#define MARKET_DATA_SERVICE_TYPE_NAME   "MarketData"

class ALGOSE_API MarketDataService : public ServiceBase
{
public:
    // Reenterable and thread-safe must be guaranteed by implementor.
    virtual int getSupportedExchanges();
    virtual int subscribe(const char** instruments, int num) = 0;
    virtual int unsubscribe(const char** instruments, int num) = 0;

protected:
    void notifyMarketData(Tick& tick);
};

extern "C" typedef MarketDataService *CreateMarketDataServiceProc();
#define EXPORT_MARKET_DATA_SERVICE(service_name)                           \
    extern "C" SERVICE_API MarketDataService* CreateMarketDataService()    \
    {                                                                      \
        return new service_name;                                           \
    }

#define EXECUTION_SERVICE_TYPE_NAME     "Execution"

#define EXEC_SRV_POS_PRICING_MODEL_PARAM_NAME   "PosPricingModel"
#define EXEC_SRV_POS_PRICING_FIFO               "FIFO"
#define EXEC_SRV_POS_PRICING_COMBINED           "Combined"

class ALGOSE_API ExecutionService : public ServiceBase
{
public:
    // Reenterable and thread-safe must be guaranteed by implementor.
    virtual bool submitOrder(const Order& order) = 0;
    virtual bool cancelOrder(const Order& order) = 0;
    virtual bool motifyOrder(const Order& order) = 0;

protected:
    void notifySecurityDefinition(SecurityDefinition& security);
    void notifyOrderStatus(Order& order);
    void notifyOrderOperationStatus(OrderOperation& operation);
    void notifyExecutionReport(Execution& execution);
    void notifyAccountDetails(AccountDetails& details);
    void notifyAccountPosition(AccountPosition& position);
    void initializeDone();
    void ready();
    void reset();
};

extern "C" typedef ExecutionService *CreateExecutionServiceProc();
#define EXPORT_EXECUTION_SERVICE(service_name)                            \
    extern "C" SERVICE_API ExecutionService* CreateExecutionService()     \
    {                                                                     \
        return new service_name;                                          \
    }

#define HISTORICAL_DATA_SERVICE_TYPE_NAME   "HistoricalData"

class ALGOSE_API HistoricalDataService : public ServiceBase
{
public:
    virtual int  requestHistoricMarketData(const HistoricalDataRequest& request) = 0;
    virtual void freeRequest(int reqId) = 0;
};

extern "C" typedef HistoricalDataService *CreateHistoricalDataServiceProc();
#define EXPORT_HISTORICAL_DATA_SERVICE(service_name)                                \
    extern "C" SERVICE_API HistoricalDataService* CreateHistoricalDataService()     \
    {                                                                               \
        return new service_name;                                                    \
    }

#define ALERT_SERVICE_TYPE_NAME   "Alert"

class ALGOSE_API AlertService : public ServiceBase
{
public:
    virtual int  sendAlertMessage(int level, const char* text) = 0;
    virtual bool cancelAlert(int alertId) = 0;
};

extern "C" typedef AlertService *CreateAlertServiceProc();
#define EXPORT_ALERT_SERVICE(service_name)                                          \
    extern "C" SERVICE_API AlertService* CreateAlertService()                       \
    {                                                                               \
        return new service_name;                                                    \
    }

} // namespace AlgoSE

#endif // ALGOSE_SERVICE_H