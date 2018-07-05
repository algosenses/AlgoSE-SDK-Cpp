#ifndef ALGO_ORDER_H
#define ALGO_ORDER_H

#include <string.h>
#include "Defines.h"

namespace AlgoSE
{

typedef struct {
    enum {
        ParamId_Start = 0,

        // Global parameters
        LowerLimit_PriceTicks,
        UpperLimit_PriceTicks,
        Float_PriceTicks,
        TimeToLive_Ms,
        CloseAction_TimeToLive_Ms,
        PriceCancel_SeekBestPrice,

        // Normal phase parameters
        NormalPhase_PriceType,
        NormalPhase_CloseAction_PriceType,
        NormalPhase_Order_TimeInforce,
        NormalPhase_CloseAction_Order_TimeInforce,
        NormalPhase_LowerCancel_PriceTicks,
        NormalPhase_UpperCancel_PriceTicks,
        NormalPhase_CloseAction_LowerCancel_PriceTicks,
        NormalPhase_CloseAction_UpperCancel_PriceTicks,
        NormalPhase_CancelTime_Ms,
        NormalPhase_CloseAction_CancelTime_Ms,

        // Catch phase parameters
        CatchPhase_PriceType,
        CatchPhase_CloseAction_PriceType,
        CatchPhase_Order_TimeInforce,
        CatchPhase_CloseAction_Order_TimeInforce,
        CatchPhase_LowerCancel_PriceTicks,
        CatchPhase_UpperCancel_PriceTicks,
        CatchPhase_CloseAction_LowerCancel_PriceTicks,
        CatchPhase_CloseAction_UpperCancel_PriceTicks,
        CatchPhase_CancelTime_Ms,
        CatchPhase_CloseAction_CancelTime_Ms,

        ParamId_End
    };
} AlgoParamID;

#define LowerLimit_PriceTicks_ParamName                             "LowerLimit_PriceTicks"
#define UpperLimit_PriceTicks_ParamName                             "UpperLimit_PriceTicks"
#define Float_PriceTicks_ParamName                                  "Float_PriceTicks"
#define TimeToLive_Ms_ParamName                                     "TimeToLive_Ms"
#define CloseAction_TimeToLive_Ms_ParamName                         "CloseAction_TimeToLive_Ms"
#define PriceCancel_SeekBestPrice_ParamName                         "PriceCancel_SeekBestPrice"
#define NormalPhase_PriceType_ParamName                             "NormalPhase_PriceType"
#define NormalPhase_CloseAction_PriceType_ParamName                 "NormalPhase_CloseAction_PriceType"
#define NormalPhase_Order_TimeInforce_ParamName                     "NormalPhase_Order_TimeInforce"
#define NormalPhase_CloseAction_Order_TimeInforce_ParamName         "NormalPhase_CloseAction_Order_TimeInforce"
#define NormalPhase_LowerCancel_PriceTicks_ParamName                "NormalPhase_LowerCancel_PriceTicks"
#define NormalPhase_UpperCancel_PriceTicks_ParamName                "NormalPhase_UpperCancel_PriceTicks"
#define NormalPhase_CloseAction_LowerCancel_PriceTicks_ParamName    "NormalPhase_CloseAction_LowerCancel_PriceTicks"
#define NormalPhase_CloseAction_UpperCancel_PriceTicks_ParamName    "NormalPhase_CloseAction_UpperCancel_PriceTicks"
#define NormalPhase_CancelTime_Ms_ParamName                         "NormalPhase_CancelTime_Ms"
#define NormalPhase_CloseAction_CancelTime_Ms_ParamName             "NormalPhase_CloseAction_CancelTime_Ms"
#define CatchPhase_PriceType_ParamName                              "CatchPhase_PriceType"
#define CatchPhase_CloseAction_PriceType_ParamName                  "CatchPhase_CloseAction_PriceType"
#define CatchPhase_Order_TimeInforce_ParamName                      "CatchPhase_Order_TimeInforce"
#define CatchPhase_CloseAction_Order_TimeInforce_ParamName          "CatchPhase_CloseAction_Order_TimeInforce"
#define CatchPhase_LowerCancel_PriceTicks_ParamName                 "CatchPhase_LowerCancel_PriceTicks"
#define CatchPhase_UpperCancel_PriceTicks_ParamName                 "CatchPhase_UpperCancel_PriceTicks"
#define CatchPhase_CloseAction_LowerCancel_PriceTicks_ParamName     "CatchPhase_CloseAction_LowerCancel_PriceTicks"
#define CatchPhase_CloseAction_UpperCancel_PriceTicks_ParamName     "CatchPhase_CloseAction_UpperCancel_PriceTicks"
#define CatchPhase_CancelTime_Ms_ParamName                          "CatchPhase_CancelTime_Ms"
#define CatchPhase_CloseAction_CancelTime_Ms_ParamName              "CatchPhase_CloseAction_CancelTime_Ms"

typedef struct {
    //正常下单阶段委托价类型，1为最新价，2为对手价, 3为用户指定价
    int NormalPhase_PriceType;
    //正常下单阶段平仓单委托价类型，1为最新价，2为对手价, 3为用户指定价
    int NormalPhase_CloseAction_PriceType;
    //正常下单阶段报单的时效类型，6为GTD，4为FOK，3为FAK
    int NormalPhase_Order_TimeInforce;
    //正常下单阶段平仓单的时效类型，6为GTD，4为FOK，3为FAK
    int NormalPhase_CloseAction_Order_TimeInforce;

    //追单阶段委托价类型，1为最新价，2为对手价, 3为用户指定价
    int CatchPhase_PriceType;
    //追单阶段平仓单委托价类型，1为最新价，2为对手价, 3为用户指定价
    int CatchPhase_CloseAction_PriceType;
    //追单阶段报单的时效类型，6为GTD，4为FOK，3为FAK
    int CatchPhase_Order_TimeInforce;
    //追单阶段平仓单的时效类型，6为GTD，4为FOK，3为FAK
    int CatchPhase_CloseAction_Order_TimeInforce;

    //算法单价格阀值下限
    int LowerLimit_PriceTicks;
    //算法单价格阀值上限
    int UpperLimit_PriceTicks;

    //算法单撤单次数上限
    int Cancelation_Num_Limit;

    //委托价浮动跳数，买入时报价上浮该跳数，卖出时报价下浮该跳数
    //即以更优价格报价从而提高成交概率
    //如果为负数，则朝相反方向浮动价格
    int Float_PriceTicks;

    // 当价格往有利方向变动且超出价格撤单范围时，是否撤单重追，0不撤单， 非0撤单重追
    // 当价格往有利方向变动时，撤单重追可能会得到更优成交价，但也有可能带来更多风险
    int PriceCancel_SeekBestPrice;

    //正常下单阶段价格撤单下限
    int NormalPhase_LowerCancel_PriceTicks;
    //正常下单阶段价格撤单上限
    int NormalPhase_UpperCancel_PriceTicks;

    //正常下单阶段平仓单价格撤单下限
    int NormalPhase_CloseAction_LowerCancel_PriceTicks;
    //正常下单阶段平仓单价格撤单上限
    int NormalPhase_CloseAction_UpperCancel_PriceTicks;

    //追单阶段价格撤单下限
    int CatchPhase_LowerCancel_PriceTicks;
    //追单阶段价格撤单上限
    int CatchPhase_UpperCancel_PriceTicks;

    //追单阶段平仓单价格撤单下限
    int CatchPhase_CloseAction_LowerCancel_PriceTicks;
    //追单阶段平仓单价格撤单上限
    int CatchPhase_CloseAction_UpperCancel_PriceTicks;

    //正常下单阶段时间撤单毫秒数
    int NormalPhase_CancelTime_Ms;
    //正常下单阶段平仓单时间撤单毫秒数
    int NormalPhase_CloseAction_CancelTime_Ms;
    //追单阶段时间撤单毫秒数
    int CatchPhase_CancelTime_Ms;
    //追单阶段平仓单时间撤单毫秒数
    int CatchPhase_CloseAction_CancelTime_Ms;

    //算法单存活时间毫秒数(超时阀值)
    int TimeToLive_Ms;
    //平仓算法单存活时间毫秒数(超时阀值)
    int CloseAction_TimeToLive_Ms;
} Params;

// 默认每订单最大撤单次数
#define  DEFAULT_MAX_CANCEL_COUNT       (50)

// 默认每订单最大执行次数
#define DEFAULT_MAX_EXEC_COUNT          (50)

// 默认时间撤单毫秒数
#define DEFAULT_CANCLE_TIME_MS          (1000)

// 默认算法单存活时间
#define DEFAULT_LIVE_TO_TIME_MS         (5000)

// 默认算法单价格撤单上限跳数
#define DEFAULT_UPPER_CANCEL_PRICE_TICKS    (5)

// 默认算法单价格撤单下限跳数
#define DEFAULT_LOWER_CANCEL_PRICE_TICKS    (5)

// 默认价格浮动点数，向更易成交的价格方向浮动，买单价格上浮，卖单价格下浮
#define DEFAULT_FLOAT_PRICE_TICK        (0)

// 执行价格类型
enum {
    EXEC_LASTPRICE = 1,  //基于最新成交价
    EXEC_BIDASKPRICE,    //基于盘口价
    EXEC_USER_SPECIFIED, //用户指定价格
};

typedef struct _ParamsBlock
{
    _ParamsBlock()
    {
        memset(&m_params, 0, sizeof(Params));

        m_params.NormalPhase_PriceType = EXEC_LASTPRICE;
        m_params.NormalPhase_CloseAction_PriceType = EXEC_LASTPRICE;
        m_params.NormalPhase_Order_TimeInforce = TimeInForce::GTD;
        m_params.NormalPhase_CloseAction_Order_TimeInforce = TimeInForce::GTD;

        m_params.CatchPhase_PriceType = EXEC_BIDASKPRICE;
        m_params.CatchPhase_CloseAction_PriceType = EXEC_BIDASKPRICE;
        m_params.CatchPhase_Order_TimeInforce = TimeInForce::GTD;
        m_params.CatchPhase_CloseAction_Order_TimeInforce = TimeInForce::GTD;

        m_params.Float_PriceTicks = DEFAULT_FLOAT_PRICE_TICK;
        m_params.PriceCancel_SeekBestPrice = 1;

        m_params.Cancelation_Num_Limit = DEFAULT_MAX_CANCEL_COUNT;

        m_params.NormalPhase_LowerCancel_PriceTicks = DEFAULT_LOWER_CANCEL_PRICE_TICKS;
        m_params.NormalPhase_UpperCancel_PriceTicks = DEFAULT_UPPER_CANCEL_PRICE_TICKS;
        m_params.NormalPhase_CloseAction_LowerCancel_PriceTicks = DEFAULT_LOWER_CANCEL_PRICE_TICKS;
        m_params.NormalPhase_CloseAction_UpperCancel_PriceTicks = DEFAULT_UPPER_CANCEL_PRICE_TICKS;

        m_params.CatchPhase_LowerCancel_PriceTicks = DEFAULT_LOWER_CANCEL_PRICE_TICKS;
        m_params.CatchPhase_UpperCancel_PriceTicks = DEFAULT_UPPER_CANCEL_PRICE_TICKS;
        m_params.CatchPhase_CloseAction_LowerCancel_PriceTicks = DEFAULT_LOWER_CANCEL_PRICE_TICKS;
        m_params.CatchPhase_CloseAction_UpperCancel_PriceTicks = DEFAULT_UPPER_CANCEL_PRICE_TICKS;

        m_params.NormalPhase_CancelTime_Ms = DEFAULT_CANCLE_TIME_MS;
        m_params.CatchPhase_CancelTime_Ms = DEFAULT_CANCLE_TIME_MS;
        m_params.NormalPhase_CloseAction_CancelTime_Ms = DEFAULT_CANCLE_TIME_MS;
        m_params.CatchPhase_CloseAction_CancelTime_Ms = DEFAULT_CANCLE_TIME_MS;
        m_params.TimeToLive_Ms = DEFAULT_LIVE_TO_TIME_MS;
        m_params.CloseAction_TimeToLive_Ms = DEFAULT_LIVE_TO_TIME_MS;
    }

    //算法单参数设置接口

    //设置执行价格类型
    // 1. EXCE_LASTPRICE：     基于最新价执行
    // 2. EXCE_BIDASKPRICE：   基于买卖盘口价执行
    // 3. EXEC_USER_SPECIFIED：基于用户指定价
    void set_NormalPhase_PriceType(int type)
    {
        if (type != EXEC_LASTPRICE &&
            type != EXEC_BIDASKPRICE &&
            type != EXEC_USER_SPECIFIED) {
            return;
        }

        m_params.NormalPhase_PriceType = type;
    }

    inline int get_NormalPhase_PriceType() const
    {
        return m_params.NormalPhase_PriceType;
    }

    inline int get_Cancelation_Num_Limit() const
    {
        return m_params.Cancelation_Num_Limit;
    }

    void set_Cancelation_Num_Limit(int num)
    {
        m_params.Cancelation_Num_Limit = num;
    }

    void set_NormalPhase_CloseAction_PriceType(int type)
    {
        if (type != EXEC_LASTPRICE &&
            type != EXEC_BIDASKPRICE &&
            type != EXEC_USER_SPECIFIED) {
            return;
        }

        m_params.NormalPhase_CloseAction_PriceType = type;
    }

    inline int get_NormalPhase_CloseAction_PriceType() const
    {
        return m_params.NormalPhase_CloseAction_PriceType;
    }

    void set_NormalPhase_Order_TimeInforce(int type)
    {
        if (type != TimeInForce::GTD && 
            type != TimeInForce::FOK && 
            type != TimeInForce::IOC) {
            return;
        }

        m_params.NormalPhase_Order_TimeInforce = type;
    }

    inline int get_NormalPhase_Order_TimeInforce() const
    {
        return m_params.NormalPhase_Order_TimeInforce;
    }

    void set_NormalPhase_CloseAction_Order_TimeInforce(int type)
    {
        if (type != TimeInForce::GTD &&
            type != TimeInForce::FOK &&
            type != TimeInForce::IOC) {
            return;
        }

        m_params.NormalPhase_CloseAction_Order_TimeInforce = type;
    }

    inline int get_NormalPhase_CloseAction_Order_TimeInforce() const
    {
        return m_params.NormalPhase_CloseAction_Order_TimeInforce;
    }

    void set_CatchPhase_PriceType(int type)
    {
        if (type != EXEC_LASTPRICE &&
            type != EXEC_BIDASKPRICE &&
            type != EXEC_USER_SPECIFIED) {
            return;
        }

        m_params.CatchPhase_PriceType = type;
    }

    inline int get_CatchPhase_PriceType() const
    {
        return m_params.CatchPhase_PriceType;
    }

    void set_CatchPhase_CloseAction_PriceType(int type)
    {
        if (type != EXEC_LASTPRICE &&
            type != EXEC_BIDASKPRICE &&
            type != EXEC_USER_SPECIFIED) {
            return;
        }

        m_params.CatchPhase_CloseAction_PriceType = type;
    }

    inline int get_CatchPhase_CloseAction_PriceType() const
    {
        return m_params.CatchPhase_CloseAction_PriceType;
    }

    void set_CatchPhase_Order_TimeInforce(int type)
    {
        if (type != TimeInForce::GTD &&
            type != TimeInForce::FOK &&
            type != TimeInForce::IOC) {
            return;
        }

        m_params.CatchPhase_Order_TimeInforce = type;
    }

    inline int get_CatchPhase_Order_TimeInforce() const
    {
        return m_params.CatchPhase_Order_TimeInforce;
    }

    void set_CatchPhase_CloseAction_Order_TimeInforce(int type)
    {
        if (type != TimeInForce::GTD &&
            type != TimeInForce::FOK &&
            type != TimeInForce::IOC) {
            return;
        }

        m_params.CatchPhase_CloseAction_Order_TimeInforce = type;
    }

    inline int get_CatchPhase_CloseAction_Order_TimeInforce() const
    {
        return m_params.CatchPhase_CloseAction_Order_TimeInforce;
    }

    void set_LowerLimit_PriceTicks(int num)
    {
        if (num < 0) {
            return;
        }

        m_params.LowerLimit_PriceTicks = num;
    }

    inline int get_LowerLimit_PriceTicks() const
    {
        return m_params.LowerLimit_PriceTicks;
    }

    void set_UpperLimit_PriceTicks(int num)
    {
        if (num < 0) {
            return;
        }

        m_params.UpperLimit_PriceTicks = num;
    }

    inline int get_UpperLimit_PriceTicks() const
    {
        return m_params.UpperLimit_PriceTicks;
    }

    void set_Float_PriceTicks(int num)
    {
        m_params.Float_PriceTicks = num;
    }

    inline int get_Float_PriceTicks() const
    {
        return m_params.Float_PriceTicks;
    }

    void set_PriceCancel_SeekBestPrice(bool onoff)
    {
        if (onoff) {
            m_params.PriceCancel_SeekBestPrice = 1;
        } else {
            m_params.PriceCancel_SeekBestPrice = 0;
        }
    }

    inline int get_PriceCancel_SeekBestPrice() const
    {
        return m_params.PriceCancel_SeekBestPrice;
    }

    void set_NormalPhase_LowerCancel_PriceTicks(int num)
    {
        if (num < 0) {
            return;
        }

        m_params.NormalPhase_LowerCancel_PriceTicks = num;
    }

    inline int get_NormalPhase_LowerCancel_PriceTicks() const
    {
        return m_params.NormalPhase_LowerCancel_PriceTicks;
    }

    void set_NormalPhase_UpperCancel_PriceTicks(int num)
    {
        if (num < 0) {
            return;
        }

        m_params.NormalPhase_UpperCancel_PriceTicks = num;
    }

    inline int get_NormalPhase_UpperCancel_PriceTicks() const
    {
        return m_params.NormalPhase_UpperCancel_PriceTicks;
    }

    void set_NormalPhase_CloseAction_LowerCancel_PriceTicks(int num)
    {
        if (num < 0) {
            return;
        }

        m_params.NormalPhase_CloseAction_LowerCancel_PriceTicks = num;
    }

    inline int get_NormalPhase_CloseAction_LowerCancel_PriceTicks() const
    {
        return m_params.NormalPhase_CloseAction_LowerCancel_PriceTicks;
    }

    void set_NormalPhase_CloseAction_UpperCancel_PriceTicks(int num)
    {
        if (num < 0) {
            return;
        }

        m_params.NormalPhase_CloseAction_UpperCancel_PriceTicks = num;
    }

    inline int get_NormalPhase_CloseAction_UpperCancel_PriceTicks() const
    {
        return m_params.NormalPhase_CloseAction_UpperCancel_PriceTicks;
    }

    void set_CatchPhase_LowerCancel_PriceTicks(int num)
    {
        if (num < 0) {
            return;
        }

        m_params.CatchPhase_LowerCancel_PriceTicks = num;
    }

    inline int get_CatchPhase_LowerCancel_PriceTicks() const
    {
        return m_params.CatchPhase_LowerCancel_PriceTicks;
    }

    void set_CatchPhase_UpperCancel_PriceTicks(int num)
    {
        if (num < 0) {
            return;
        }

        m_params.CatchPhase_UpperCancel_PriceTicks = num;
    }

    inline int get_CatchPhase_UpperCancel_PriceTicks() const
    {
        return m_params.CatchPhase_UpperCancel_PriceTicks;
    }

    void set_CatchPhase_CloseAction_LowerCancel_PriceTicks(int num)
    {
        if (num < 0) {
            return;
        }

        m_params.CatchPhase_CloseAction_LowerCancel_PriceTicks = num;
    }

    inline int get_CatchPhase_CloseAction_LowerCancel_PriceTicks() const
    {
        return m_params.CatchPhase_CloseAction_LowerCancel_PriceTicks;
    }

    void set_CatchPhase_CloseAction_UpperCancel_PriceTicks(int num)
    {
        if (num < 0) {
            return;
        }

        m_params.CatchPhase_CloseAction_UpperCancel_PriceTicks = num;
    }

    inline int get_CatchPhase_CloseAction_UpperCancel_PriceTicks() const
    {
        return m_params.CatchPhase_CloseAction_UpperCancel_PriceTicks;
    }

    void set_NormalPhase_CancelTime_Ms(int ms)
    {
        if (ms <= 0) {
            return;
        }

        m_params.NormalPhase_CancelTime_Ms = ms;
    }

    inline int get_NormalPhase_CancelTime_Ms() const
    {
        return m_params.NormalPhase_CancelTime_Ms;
    }

    void set_NormalPhase_CloseAction_CancelTime_Ms(int ms)
    {
        if (ms <= 0) {
            return;
        }

        m_params.NormalPhase_CloseAction_CancelTime_Ms = ms;
    }

    inline int get_NormalPhase_CloseAction_CancelTime_Ms() const
    {
        return m_params.NormalPhase_CloseAction_CancelTime_Ms;
    }

    void set_CatchPhase_CancelTime_Ms(int ms)
    {
        if (ms <= 0) {
            return;
        }

        m_params.CatchPhase_CancelTime_Ms = ms;
    }

    inline int get_CatchPhase_CancelTime_Ms() const
    {
        return m_params.CatchPhase_CancelTime_Ms;
    }

    void set_CatchPhase_CloseAction_CancelTime_Ms(int ms)
    {
        if (ms <= 0) {
            return;
        }

        m_params.CatchPhase_CloseAction_CancelTime_Ms = ms;
    }

    inline int get_CatchPhase_CloseAction_CancelTime_Ms() const
    {
        return m_params.CatchPhase_CloseAction_CancelTime_Ms;
    }

    void set_TimeToLive_Ms(int ms)
    {
        if (ms <= 0) {
            return;
        }

        m_params.TimeToLive_Ms = ms;
    }

    inline int get_TimeToLive_Ms() const
    {
        return m_params.TimeToLive_Ms;
    }

    void set_ClosePos_TimeToLive_Ms(int ms)
    {
        if (ms <= 0) {
            return;
        }

        m_params.CloseAction_TimeToLive_Ms = ms;
    }

    inline int get_ClosePos_TimeToLive_Ms() const
    {
        return m_params.CloseAction_TimeToLive_Ms;
    }

private:
    Params m_params;

} AlgoParams;

typedef struct {
    enum {
        Unknown = 0,
        PriceOutOfRange,
        TimeOut,
    };
} CancelationReason;

typedef struct {
    char          valid;               //有效标志[0-有效,1-无效]
    int           algoId;              //算法单ID(在AlgoTrader内部唯一标识该算法单)
    char          signalId[LEN_ID];    //触发此算法单的信号ID
    int           algoType;            //算法类型
    int           algoStatus;          //算法单状态
    char          action;              //1=Buy，2=Sell，3=Short，4=Cover
    char          instrument[LEN_INSTRUMENT]; //合约名
    double        quantity;            //算法单数量
    double        price;               //限制价位
    double        triggerPx;           //触发价
    double        execPx;              //实际执行价
    double        tickSize;            //最小跳价位
    char          clOrdId[LEN_ID];     //此周期内的底层报单编号
    volatile int  orderStatus;         //底层报单状态
    double        cumQty;              //已成数量
    double        avgTradedPx;         //已成交均价
    long          timeID;              //定时器编号
    unsigned long initTick;            //初始时间戳
    unsigned long lastTick;            //最近的报单时间戳
    unsigned long stopTick;            //算法单终止时间戳
    unsigned int  execCount;           //执行计数
    unsigned int  cancelCount;         //撤单计数
    int           cancelReason;        //撤单原因
    int           execPhase;           //执行阶段
    int           execSrvId;           //使用的订单执行服务
    AlgoParams params;
} AlgoOrder;

} // namespace AlgoSE

#endif // ALGO_ORDER_H