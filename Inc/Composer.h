//
// User space bar composer.
//
#ifndef ATS_COMPOSER_H
#define ATS_COMPOSER_H

#include "ATS.h"
#include "Export.h"

namespace ATS
{

class ComposerImpl;

class Composer {
public:
    Composer();
    ~Composer();
    bool       init(const TradingHours& hours, int resolution, int interval);
    void       appendMarketData(const MarketData& data);
    bool       hasNewCompositedData();
    MarketData getCompositedData();

private:
    ComposerImpl* m_implementor;
};

} // namespace ATS

#endif // ATS_COMPOSER_H