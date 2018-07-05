#ifndef ALGOSE_EVENT_H
#define ALGOSE_EVENT_H

#include <vector>
#include "DateTime.h"

namespace AlgoSE
{

class ALGOSE_API IEventHandler
{
public:
	virtual void onEvent(
        int             type, 
        const DateTime& datetime,
        const void *    context) = 0;
};

class ALGOSE_API Event
{
public:
    enum EvtType {
        EvtNone,
        EvtDispatcherStart,
        EvtDispatcherIdle,
        EvtDispatcherTimeElapsed,
        EvtDataSeriesNewValue,
        EvtDataSeriesReset,
        EvtOrderUpdate,
        EvtMarketDataProcessed,
        EvtNewMarketData,
        EvtNewReturns,
        EvtNewTradingDay
    };

    typedef struct  {
        DateTime datetime;
        void* data;
    } Context;

    Event(EvtType type = EvtNone);
	void    setType(EvtType type);
	EvtType getType() const;
    void    subscribe(IEventHandler* handler);
    void    unsubscribe();
    void    emitEvt(const DateTime& datetime, const void *context);

private:
    void applyChanges();

private:
    std::vector<IEventHandler*> m_handlers;
    std::vector<IEventHandler*> m_toSubscribe;
    std::vector<IEventHandler*> m_toUnsubscribe;
    volatile bool m_emitting;
    bool m_applyChanges;
	EvtType m_type;
};

} // namespace AlgoSE

#endif // ALGOSE_EVENT_H