/************************************************************************************
 * Data structure and Platform related definitions for Algorithmic Strategy Engine. *
 *                                                                                  *
 * $Author: zhuangshaobo $                                                          *
 * $Mail:   zhuang@algo.trade $                                                     *
 * $Date:   2013-08-15 $                                                            *
 ************************************************************************************/

#ifndef ALGOSE_DEFINES_H
#define ALGOSE_DEFINES_H

namespace AlgoSE
{

////////////////////////////////////////////////////////////////////////////////
// Platform Related Definitions
////////////////////////////////////////////////////////////////////////////////
#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64) || defined(_WINDOWS)
#define __PLATFORM_WINDOWS__
#elif defined(__GNUC__)
#define __PLATFORM_LINUX__
#endif

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the ALGOSE_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// ALGOSE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#if defined(__PLATFORM_WINDOWS__)
    #ifdef ALGOSE_EXPORTS
        #define ALGOSE_API __declspec(dllexport)
    #else
        #define ALGOSE_API __declspec(dllimport)
    #endif
#elif defined(__PLATFORM_LINUX__)
    #define ALGOSE_API  __attribute__((visibility("default")))
#else
    //  do nothing and hope for the best?
    #define ALGOSE_API
    #pragma warning Unknown dynamic link import/export semantics.
#endif

#ifdef _MSC_VER
#pragma warning(disable: 4251)
#endif

////////////////////////////////////////////////////////////////////////////////
// Data Structure Definitions
////////////////////////////////////////////////////////////////////////////////

// Structure TimeStamp represents the number of seconds that have elapsed since 
// January 1, 1970 (midnight UTC/GMT), not counting leap seconds (in ISO 8601: 1970-01-01T00:00:00Z). 
// It's also known as 'Unix epoch' (or Unix time or POSIX time or Unix timestamp).
typedef struct {
    long sec;       // in seconds
    long usec;      // in microseconds
} TimeStamp;

const unsigned int LEN_ID         = 32;
const unsigned int LEN_NAME       = 32;
const unsigned int LEN_INSTRUMENT = 32;
const unsigned int LEN_EXCHANGE   = 8;
const unsigned int LEN_STATE_MSG  = 128;
const unsigned int LEN_TEXT       = 256;

typedef struct {
    enum {
        LOG_VERBOSE = 0x01,
        LOG_TRACE   = 0x02,
        LOG_DEBUG   = 0x04,
        LOG_INFO    = 0x08,
        LOG_WARN    = 0x10,
        LOG_ERROR   = 0x20,
        LOG_FATAL   = 0x40,
    };
} LogLevel;

typedef struct {
    enum {
        LIVE,
        SIMULATION,
        OPTIMIZATION,
    };
} RunningMode;

typedef struct {
    enum {
        CSV_DATA_FILE,
        BIN_DATA_FILE,
    };
} DataFileFormat;

typedef struct {
    enum {
        UNKNOWN = 0,
        STOCK,
        FUTURE,
        FOREX,
        OPTION
    };
} SecurityType;

typedef struct {
    enum {
        // It is important for frequency values to get bigger for bigger windows.
        TICK   = 0,                 // The bar represents a single trade.
        SECOND = 1,                 // The bar summarizes the trading activity during 1 second.
        MINUTE = 60,                // The bar summarizes the trading activity during 1 minute.
        HOUR   = 60 * 60,           // The bar summarizes the trading activity during 1 hour.
        DAY    = 24 * 60 * 60,      // The bar summarizes the trading activity during 1 day.
        WEEK   = 24 * 60 * 60 * 7,  // The bar summarizes the trading activity during 1 week.
    };
} Resolution;

typedef struct {
    enum {
        EXCHG_UNKNOWN = 0x00,
        EXCHG_SSE     = 0x0001,
        EXCHG_SZE     = 0x0002,
        EXCHG_SHFE    = 0x0004,
        EXCHG_DCE     = 0x0008,
        EXCHG_CZCE    = 0x0010,
        EXCHG_CFFEX   = 0x0020,
        EXCHG_GOLD    = 0x0040
    };
} ExchangeCode;

typedef struct {
    enum {
        SNAPSHOT = 0,
        TRADES,
    };
} TickType;

typedef struct {
    char      type;
    char      secType;  // security type
    char      instrument[LEN_INSTRUMENT];
    char      exchange[LEN_EXCHANGE];
    TimeStamp timestamp;
    double    lastPrice;
    double    openPrice;
    double    highestPrice;
    double    lowestPrice;
    double    closePrice;
    double    volume;
    long long openInterest;
    double    turnover;
    double    upperLimitPrice;
    double    lowerLimitPrice;
    double    preSettlePrice;
    double    preClosePrice;
    double    settlePrice;
    int       preOpenInterest;
    double    averagePrice;
    int       depth;

    double    bidPrice1;
    int       bidVolume1;
    double    bidPrice2;
    int       bidVolume2;
    double    bidPrice3;
    int       bidVolume3;
    double    bidPrice4;
    int       bidVolume4;
    double    bidPrice5;
    int       bidVolume5;

    double    askPrice1;
    int       askVolume1;
    double    askPrice2;
    int       askVolume2;
    double    askPrice3;
    int       askVolume3;
    double    askPrice4;
    int       askVolume4;
    double    askPrice5;
    int       askVolume5;

    int       srvId;
} Tick;

typedef struct {
    char      secType;      // security type
    char      instrument[LEN_INSTRUMENT];
    char      exchange[LEN_EXCHANGE];
    TimeStamp timestamp;
    int       resolution;
    int       interval;
    double    open;
    double    high;
    double    low;
    double    close;
    double    last;
    long long volume;
    long long openInt;
    double    amount;
} Bar;

typedef struct {
    long      reqId;
    int       isLast;
    char      secType;
    char      exchange[LEN_EXCHANGE];
    char      instrument[LEN_INSTRUMENT];
    TimeStamp timestamp;
    int       resolution;
    int       interval;
    double    open;
    double    high;
    double    low;
    double    close;
    double    last;
    long long openInt;
    long long volume;
    double    turnover;
    double    upperLimitPrice;
    double    lowerLimitPrice;
    double    preSettlePrice;
    double    preClosePrice;
    double    settlePrice;
    int       preOpenInterest;
    double    averagePrice;
    int       depth;

    double    bidPrice1;
    int       bidVolume1;
    double    bidPrice2;
    int       bidVolume2;
    double    bidPrice3;
    int       bidVolume3;
    double    bidPrice4;
    int       bidVolume4;
    double    bidPrice5;
    int       bidVolume5;

    double    askPrice1;
    int       askVolume1;
    double    askPrice2;
    int       askVolume2;
    double    askPrice3;
    int       askVolume3;
    double    askPrice4;
    int       askVolume4;
    double    askPrice5;
    int       askVolume5;

    // Identifies whether this bar(market data) is completed.
    // Used in the historical data loading scenarios.
    int       uncompleted;
    int       srvId;
} HistoricalData;

// State chart:
// INITIAL           -> PENDING_NEW
// PENDING_NEW       -> SUBMITTED
// PENDING_NEW       -> CANCELED
// SUBMITTED         -> ACCEPTED
// SUBMITTED         -> PENDING_CANCEL
// ACCEPTED          -> FILLED
// ACCEPTED          -> PARTIALLY_FILLED
// ACCEPTED          -> PENDING_CANCEL
// PARTIALLY_FILLED  -> PARTIALLY_FILLED
// PARTIALLY_FILLED  -> FILLED
// PARTIALLY_FILLED  -> PENDING_CANCEL
// PENDING_CANCEL    -> CANCELED

// ACCEPTED: Engine is triggered to frozen positions.
// CANCELED or REJECTED: Engine is triggered to unfrozen positions.
typedef struct {
    enum {
        UNKNOWN = 0,
        INITIAL,           // Initial state.
        PENDING_NEW,
        SUBMITTED,         // Order has been submitted.
        ACCEPTED,          // Order has been acknowledged by the broker.
        PENDING_CANCEL,
        CANCELED,          // Order has been canceled.
        PARTIALLY_FILLED,  // Order has been partially filled.
        FILLED,            // Order has been completely filled.
        REJECTED           // Order has been rejected.
    };
} OrderState;

// Class for orders.
//
// Valid type parameter values are:
//
// 1. MARKET
// A market order is an order to buy or sell an asset at the bid or offer price currently available in the marketplace. 
// When you submit a market order, you have no guarantee that the order will execute at any specific price.
//
// 2. LIMIT
// A limit order is an order to buy or sell a contract ONLY at the specified price or better.
//
// 3. STOP
// A Stop order becomes a market order to buy or sell securities or commodities once the specified stop price is attained or penetrated. 
// A Stop order is not guaranteed a specific execution price.
//
// 4. STOP_LIMIT
// A Stop Limit order is similar to a stop order in that a stop price will activate the order. However, unlike the stop order, 
// which is submitted as a market order when elected, the stop limit order is submitted as a limit order. 
//
// When you place a stop or limit order, you are telling your broker that you don't want the market price
// (the current price at which a stock is trading), but that you want the stock price to move in a certain 
// direction before your order is executed.
// 
// With a stop order, your trade will be executed only when the security you want to buy or sell reaches a 
// particular price (the stop price). Once the stock has reached this price, a stop order essentially becomes 
// a market order and is filled. For instance, if you own stock ABC, which currently trades at $20, and you 
// place a stop order to sell it at $15, your order will only be filled once stock ABC drops below $15. Also 
// known as a "stop-loss order", this allows you to limit your losses. However, this type of order can also be
// used to guarantee profits. For example, assume that you bought stock XYZ at $10 per share and now the stock
// is trading at $20 per share. Placing a stop order at $15 will guarantee profits of approximately $5 per share,
// depending on how quickly the market order can be filled.
//
// A STOP_LIMIT order is an order placed with a broker that combines the features of stop order with those of a 
// limit order. A stop-limit order will be executed at a specified price (or better) after a given stop price 
// has been reached. Once the stop price is reached, the stop-limit order becomes a limit order to buy (or sell)
// at the limit price or better.
//
// Valid action parameter values are:
//
// 1. BUY
// 2. BUY_TO_COVER
// 3. SELL
// 4. SHORT
//
typedef struct {
    enum {
        MARKET = 1,
        LIMIT,
        STOP,
        STOP_LIMIT,
    };
} OrderType;

typedef struct {
    enum {
        BUY = 1,
        BUY_TO_COVER,
        SELL,
        SELL_SHORT,
    };
} OrderAction;

typedef struct {
    enum {
        CANCEL,
        MODIFY,
        SUSPEND,
        RESUME,
    };
} OrderOperationRequest;

//0 = Day
//1 = Good Till Cancel (GTC)
//2 = At the Opening (OPG)
//3 = Immediate or Cancel (IOC)
//4 = Fill or Kill (FOK)
//5 = Good Till Crossing (GTX)
//6 = Good Till Date
typedef struct {
    enum  {
        DAY = 0,
        GTC,
        OPG,
        IOC,
        FOK,
        GTX,
        GTD,
    };
} TimeInForce;

// When buy side places an order, they have only their own Client Reference ID (clOrdId) available.
// The Order ID (ordId) comes to life only when the Order is accepted by the sell side.
typedef struct {
    // Buy side's original client order ID, uniqueness must be guaranteed within a single trading day.
    char          clOrdId[LEN_ID];
    // Sell side's reference for this order.
    char          ordId[LEN_ID];
    char          instrument[LEN_INSTRUMENT];
    int           exchange;
    int           type;
    int           action;
    int           timeInforce;
    bool          allOrNone;
    int           status;
    double        quantity;
    double        price;
    double        stopPx;
    double        tradedQty;
    double        avgTradedPx;
    double        lastTradedQty;
    double        lastTradedPx;
    TimeStamp     timestamp;
    double        commissions;
    char          stateMsg[LEN_STATE_MSG];
    char          parentClOrdId[LEN_ID];
    int           closeEffect;          // Distinguish three effects of position closing.
    int           compId;               // Component who submit this order.
    int           ownerId;              // Strategy who submit this order.
    int           srvId;
} Order;

typedef struct {
    char          instrument[LEN_INSTRUMENT];
    int           type;
    int           action;
    TimeStamp     timestamp;
    double        quantity;
    double        price;
    int           closeEffect;  
    char          clOrdId[LEN_ID];
    char          ordId[LEN_ID];
    char          execId[LEN_ID];
    int           srvId;
} Execution;

typedef struct {
    enum {
        CLOSE = 0,
        CLOSE_TODAY,
        CLOSE_YESTERDAY,
    };
} CloseEffect;

typedef struct {
    char          clOrdId[LEN_ID];
    char          ordId[LEN_ID];
    char          origClOrdId[LEN_ID];
    char          instrument[LEN_INSTRUMENT];
    int           operation;
    TimeStamp     timestamp;
    int           side;
    double        price;
    double        quantity;
    bool          success;
    char          stateMsg[LEN_STATE_MSG];
    int           compId;
    int           ownerId;
    int           srvId;
} OrderOperation;

typedef struct {
    char   userId[32];
    char   password[32];
    char   userName[64];
    char   currency[8];
    double preBalance;
    double preDeposit;
    double margin;
    double lastFund;
    double currMargin;
    double deposit;
    double withdraw;
    double equity;
    double availFunds;
    double buyFreeze;
    double sellFreeze;
    double buyBond;
    double sellBond;
    double realizedPnL;
    double unrealizedPnL;
    double totalBond;
    double totalExBond;
    double todayReleaseFund;
    double comFreeze;
    double commission;
    double otherFreeze;
    double totalFreeze;
    double riskLevel;

    int    validFields;
    int    srvId;
} AccountDetails;

typedef struct {
    char   instrument[LEN_INSTRUMENT];
    int    secType;
    char   secName[LEN_NAME];
    int    exchgCode;
    double upperLimitPrice;
    double lowerLimitPrice;
    double longMarginRatio;
    double shortMarginRatio;
    double multiplier;
    double tickSize;
    int    isTrading;
    int    srvId;
} SecurityDefinition;

typedef struct {
    enum {
        POSITION_SIDE_LONG  = 'L',
        POSITION_SIDE_SHORT = 'S'
    };
} PositionSide;

// Account Position
// An Account Position is the position you actually hold in a real-time trading account.
typedef struct {
    char      instrument[LEN_INSTRUMENT];
    char      side;
    double    cumQty;
    double    todayQty;
    double    histQty;
    double    frozen;
    double    histFrozen;
    double    unformed;
    double    preSettlmntPx;
    double    cost;
    double    avgPx;
    double    unrealizedPnL;
    double    realizedPnL;
    double    margin;
    TimeStamp lastOpenTime;
    double    lastOpenPx;
    double    lastOpenQty;
    TimeStamp lastCloseTime;
    double    lastClosePx;
    double    lastCloseQty;
    double    histHighestPx;
    double    histLowestPx;
    char      accountId[LEN_ID];
    int       srvId;
} AccountPosition;

typedef struct {
    int  srvId;
    int  type;
    int  state;
    char name[LEN_NAME];
    char desc[LEN_TEXT];
} ServiceStatus;

typedef struct {
    enum {
        PARAM_TYPE_BOOL,
        PARAM_TYPE_INT,
        PARAM_TYPE_FLOAT,
        PARAM_TYPE_STRING,
    };
} StrategyParamType;

typedef struct {
    enum {
        PARAM_CATEGORY_SYSTEM,
        PARAM_CATEGORY_ALGO_TRADER,
        PARAM_CATEGORY_USER,
    };
} StrategyParamCategory;

typedef struct {
    int    strategyId;
    int    category;
    int    type;
    char   name[64];
    char   value[64];
    double start;
    double end;
    double step;
    bool   isLast;
} StrategyParam;

typedef struct {
    int       strategyId;
    TimeStamp timestamp;
    int       level;
    char      text[LEN_TEXT];
} StrategyLog;

// Strategy Position
// A Strategy Position is a virtual position that is created by the entry and exit executions
// generated by a strategy and is independent from any other running strategy's position or an 
// Account Position.
typedef struct {
    int       strategyId;
    char      instrument[LEN_INSTRUMENT];
    TimeStamp timestamp;
    int       side;
    double    quantity;
    double    frozen;
    double    unformed;
    double    avgPx;
    double    margin;
    double    unrealizedPnL;
    double    realizedPnL;
    double    highestPx;
    double    lowestPx;
} StrategyPosition;

typedef struct {
    int    strategyId;
    char   name[LEN_NAME];
    char   desc[64];
    int    state;
    bool   verbose;
    int    submittion;
    int    cancellation;
} StrategyStatus;

typedef struct {
    TimeStamp timestamp;
    int       level;
    char      text[LEN_TEXT];
} SystemLog;

// For example: begin: "09:00:00", end: "10:15:00"
typedef struct {
    char begin[16];
    char end[16];
} TradingHour;

typedef struct {
    enum {
        BackRef,
        TimeRange,
    };
} HistoricalDataRequestType;

typedef struct {
    enum {
        SyncLoad,
        AsyncLoad,
    };
} HistoricalDataLoadMode;

typedef struct _HistoricalDataRequest {
    long            reqId;
    int             type;
    char            instrument[LEN_INSTRUMENT];
    int             resolution;
    int             interval;
    int             beginDate;
    int             beginTime;
    int             endDate;
    int             endTime;
    int             refNum;
    int             mode;
    int             srvId;
    HistoricalData* histDataBuffer;
    int             ownerId;
    int             respond;
    int             retNum;
} HistoricalDataRequest;

typedef struct {
    int  timerId;
    int  compId;
    int  ownerId;
    char extra[LEN_ID];
    int  srvId;
} TimerMsg;

#define INVALID_TIMER_ID        (0)
#define INVALID_STRATEGY_ID     (0)

////////////////////////////////////////////////////////////////////////////////
// Backtesting Related Definitions
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    enum {
        NO_COMMISSION,
        FIXED_PER_TRADE,
        TRADE_PERCENTAGE    // percent of trade value
    };
} CommissionType;

typedef struct {
    enum {
        NO_SLIPPAGE,
        FIXED_PER_TRADE,
        TRADE_PERCENTAGE
    };
} SlippageType;

typedef struct _Contract {
    int    secType;
    char   instrument[32];
    int    exchange;
    double multiplier;
    double tickSize;
    double marginRatio;
    int    commType;
    double commission;
    int    slippageType;
    double slippage;
    int    mktOpenTime;
    int    mktCloseTime;
    _Contract()
    {
        secType       = SecurityType::UNKNOWN;
        instrument[0] = '\0';
        exchange      = ExchangeCode::EXCHG_UNKNOWN;
        multiplier    = 1;
        tickSize      = 1;
        marginRatio   = 0;
        commType      = CommissionType::TRADE_PERCENTAGE;
        commission    = 4.0 / 10000; // default commission
        slippageType  = SlippageType::TRADE_PERCENTAGE;
        slippage      = 0;
        mktOpenTime   = 90000;    // 09:00:00 by default
        mktCloseTime  = 153000;   // 15:30:00 by default
    }
} Contract;

typedef struct {
    double    initialCapital;
    long long tradingPeriod;
    double    finalPortfolioValue;
    // 'Account Size Required' calculates the amount of money you must 
    // have in your account to trade the strategy.
    double    acctSizeRequired;
    double    cumReturn;
    double    annualReturn;
    double    monthlyReturn;
    double    totalNetProfits;
    double    maxDD;                 // Max. Drawdown.
    double    maxDDPercentage;
    double    maxCTCDD;              // Max. Close To Close Drawdown.
    TimeStamp maxDDBegin;
    TimeStamp maxDDEnd;
    int       longestDDDuration;     // Longest Drawdown Duration, in days
    TimeStamp longestDDDBegin;
    TimeStamp longestDDDEnd;
    double    retOnMaxDD;            // Return on max drawdown.
                                     // The sum of money you would make compared to the sum of money required
                                     // to trade the strategy, after considering the margin and margin calls.
                                     // This value is calculated by dividing the net profit by the account
                                     // size required.
                                     // For leverage trading this value is more important than the Total Net 
                                     // Profit (e.g., buy or sell futures contracts or stocks on margin).
                                     // When trading using leverage, you must a sizable margin deposit.
                                     // The margin size is a certain percent of the overall transaction cost.
                                     // In addition, when trading on leverage, you need sufficient money to 
                                     // counteract equity dips - the same as in futures and stock trading is 
                                     // named margin calls.
    double    retOnAcctSizeRequired; // Return on Account Size Required.

                                     // Nobel laureate William Sharpe introduced the Sharpe Ratio, in 1996, 
                                     // under the name reward-to-variability ratio. This ratio is perhaps the
                                     // best known of the return to risk measures. The formula for the Sharpe
                                     // ratio is SR = (MR -RFR) / SD, where MR is the average return for period
                                     // (monthly), RFR is the risk-free rate of return. SD is the standard 
                                     // deviation of returns. Thus, this formula yields a value that could be
                                     // loosely defined as return per unit risked if we accept the premise 
                                     // that variability is risk. The higher Sharpe ratio the smoother the
                                     // equity curve on a monthly basis. Having a smooth equity curve is a very
                                     // important objective for many traders. That is why this ratio is widely
                                     // used both at individual market and at a portfolio level.
    double    sharpeRatio;

    // The total number of trades (both winning and losing) generated by
    // a strategy. The total number of trades is important for a number of
    // reasons. For example, no matter how large is the strategies Total
    // Net Profit, one must be sure the value is statistically valid, i.e. 
    // the number of trades is large enough. Also important is the relation
    // between the number of trades and time; even good, profitable trades
    // may be taking place too rarely or too frequently for your needs.
    long      totalTrades;

    // The number of positions currently opened.
    long      totalOpenTrades;
    // The total number of winning trades generated by a strategy.
    long      winningTrades;
    // The total number of losing trades generated by a strategy.
    long      losingTrades;

    // The percentage of winning trades generated by a strategy.
    // Calculated by dividing the number of winning trades by total
    // number of trades generated by a strategy. Percent profitable is not a
    // very reliable measure by itself since approaches to profitability can
    // differ. A strategy could have many small winning trades, making the 
    // percent profitable high with a small average winning trade, or a few big
    // winning trades accounting for a low percent profitable and a big average
    // winning trade. Many successful strategies have a percent profitability 
    // below 50% but are still profitable due to proper loss control.
    double    percentProfitable;

    // The Gross Profits divided by the number of Winning Trades.
    double    avgWinningTrade;

    // The Gross Loss divided by the number of Losing Trades.
    double    avgLosingTrade;

    // The average value of how many $ you win for every $ you lose.
    // This is calculated by dividing the average winning trades by the average
    // losing trade. This field is not a very meaningful value by itself, because
    // strategies can have different approaches to profitability. A strategy may
    // attempt trading at every possibility in order to capture many small profits
    // yet have an average losing trade greater than the average winning trade.
    // The higher this value is the better, but it should be regarded together with
    // the percentage of winning trades and the net profit.
    double    ratioAvgWinAvgLoss;

    double    avgProfit;
    double    maxProfit;
    double    minProfit;
    double    grossProfit;
    double    grossLoss;
    double    slippagePaid;
    double    commissionPaid;
} BacktestingMetrics;

typedef struct {
    double cumReturns;
    double totalNetProfits;
    double sharpeRatio;
    double maxDrawDown;
    double retOnMaxDD;
} SimplifiedMetrics;

typedef struct {
    TimeStamp tradingDay;
    double    closedProfit;
    double    realizedProfit;
    double    posProfit;
    int       tradesNum;
    int       openVolume;
    int       tradedVolume;
    int       todayPosition;
    double    commissions;
    double    slippages;
    double    tradeCost;

    double    cash;
    double    equity;
    double    profit;
    double    margin;

    double    cumRealizedProfit;
    int       cumTradesNum;
    int       cumTradedVolume;
    int       cumCloseVolume;
    double    cumCommissions;
    double    cumSlippages;
    double    cumTradeCost;
} DailyMetrics;

} // namespace AlgoSE

#endif // ALGOSE_DEFINES_H