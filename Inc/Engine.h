#ifndef ALGOSE_ENGINE_H
#define ALGOSE_ENGINE_H

#include "Defines.h"
#include "IEngine.h"

namespace AlgoSE
{

#define DEFAULT_ENGINE_CONFIG_FILE    "AlgoSE.xml"

////////////////////////////////////////////////////////////////////////////////
class EngineImpl;
class ServiceConfig;
class SimulatorConfig;

class ALGOSE_API Engine : public IEngine
{
public:
    /*  API collections for engine and strategy controlling. */
    static Engine* getInstance();
    void setRunningMode(int mode);
    void enableRemoteSrvAccess();
    void setRemoteSrvAddress(const char* addr, int port);
    void setRemoteMgrListenPort(int port);
    void setRemoteMgrUnderlyingServiceName(int type, const char* name);
    void enableRemoteManager();
    void setLogFilePath(const char* path);
    void disableConsoleLog(int mask);
    void enableConsoleLog(int mask);
    void setSimulatorConfig(const SimulatorConfig& config);
    void enablePerformanceMode();
    bool isPerformanceMode() const;
    bool registerListener(Listener* listener);
    bool unregisterListener(Listener* listener);
    bool initialize(const char* config = "");
    int  loadStrategy(const char* config);
    int  loadStrategy(Strategy& strategy, const StrategyConfig& config);
    int  loadStrategy(const StrategyConfig& config);
    bool run();
    bool launchStrategy(int stratId);
    int  getStrategyStatus(int stratId) const;
    bool assignStrategyPosition(int stratId, const char* instrument, int side, int quantity, double price);
    bool sendStrategyCommand(int stratId, const char* command);
    bool setStrategyParameter(int stratId, const StrategyParam& param);
    bool showVerboseMsg(int stratId);
    bool hideVerboseMsg(int stratId);
    bool pauseStrategy(int stratId);
    bool resumeStrategy(int stratId);
    bool stopStrategy(int stratId);
    bool registerService(const char* name, int type, void* srvObject);
    bool registerService(const ServiceConfig& config);
    bool reloadService(int type, int id);
    bool reinitializeService(int type, int id);
    void writeLogMsg(int level, const char* msg);
    MarketDataAPI* getMarketDataAPI();
    TradingAPI* getTradingAPI();
    bool stop();
    int  version();
    void release();

private:
    Engine();
    Engine(Engine const&);
    Engine& operator=(Engine const&);
    ~Engine();

private:
    static Engine* m_instance;
    EngineImpl* m_implementor;
};

} // namespace AlgoSE

#endif // ALGOSE_ENGINE_H