// Data series are abstractions used to manage time-series data.
#ifndef ALGOSE_DATA_SERIES_H
#define ALGOSE_DATA_SERIES_H

#include <cassert>
#include <limits>
#include <math.h>
#include "Defines.h"
#include "circular.h"
#include "Event.h"

namespace AlgoSE
{

// Base class for data series.
// This is a base class and should not be used directly.
class ALGOSE_API DataSeries
{
public:
    enum BuiltInType {
        ElemTypeUnknown = 0,
        ElemTypeInt,        // int
        ElemTypeInt64,      // long long
        ElemTypeFloat,      // double
        ElemTypeTick,       // Tick
        ElemTypeBar,        // Bar
        ElemBuiltInTypeEnd
    };

    static const unsigned int DEFAULT_MAX_LEN;
 
    DataSeries();
    // Returns the type of data series.
    int            getType() const;
    void           setType(int type);
    // Returns the number of elements in the data series.
    virtual std::size_t length() const = 0;
    // Returns the value at a given position/slice. It raises 'out_of_range' if the position is invalid,
    // or TypeError if the key type is invalid.
    virtual void* getItem(std::size_t pos) = 0;

    virtual Event& getNewValueEvent() = 0;

	virtual void appendWithDateTime(const DateTime& dateTime, const void* value) = 0;

    virtual ~DataSeries();

private:
    int m_type;
};

// A DataSeries that holds values in a sequence in memory.
template<typename T = double>
class ALGOSE_API SequenceDataSeries : public DataSeries
{
public:
	// @param: maxLen: The maximum number of values to hold.
	// Once a bounded length is full, when new items are added, a corresponding number of items are discarded from the opposite end.
    SequenceDataSeries(int maxLen = DataSeries::DEFAULT_MAX_LEN, int type = ElemTypeFloat)
        : m_newValueEvt(Event::EvtDataSeriesNewValue)
    {
        if (typeid(T) == typeid(int)) {
            setType(DataSeries::ElemTypeInt);
        } else if (typeid(T) == typeid(double)) {
            setType(DataSeries::ElemTypeFloat);
        } else if (typeid(T) == typeid(long long)) {
            setType(DataSeries::ElemTypeInt64);
        } else if (typeid(T) == typeid(Tick)) {
            setType(DataSeries::ElemTypeTick);
        } else if (typeid(T) == typeid(Bar)) {
            setType(DataSeries::ElemTypeBar);
        } else {
            setType(type);
        }

        setMaxLen(maxLen);
    }

    virtual std::size_t length() const
    {
        return m_values.size();
    }

    virtual void* getItem(std::size_t idx)
    {
        if (idx >= 0 && idx < length()) {
            return &(m_values[idx]);
        }

        return nullptr;
    }

    virtual void setItem(std::size_t idx, T value)
    {
        if (idx >= 0 && idx < length()) {
            m_values[idx] = value;
        } else {
            throw std::out_of_range("Index out of range.");
        }
    }

    // Latest value placed at the front of data series.
    // So m_values[0] is the newest one.
    virtual const T operator[](std::size_t idx) const
    {
        if (idx < 0 || idx >= m_values.size()) {
            throw std::out_of_range("Index out of range.");
        }

        return m_values[m_values.size() - 1 - idx];
    }

    virtual const T& at(std::size_t idx) const
    {
        if (idx < 0 || idx >= m_values.size()) {
            throw std::out_of_range("Index out of range.");
        }

        return m_values[m_values.size() - 1 - idx];
    }

	// Sets the maximum number of values to hold and resizes accordingly if necessary.
	virtual void setMaxLen(int maxLen)
    {
        m_dateTimes.clear();
        m_values.clear();
        // It is important to initialize circular_buffer to zero size
        circular_buffer<DateTime> tmpDT(0);
        m_dateTimes.swap(tmpDT);
        m_dateTimes.reserve(maxLen);

        circular_buffer<T> tmpVal(0);
        m_values.swap(tmpVal);
        m_values.reserve(maxLen);
        m_maxLen = maxLen;
    }

	// Returns the maximum number of values to hold.
	virtual int getMaxLen() const
    {
        return m_maxLen;
    }

    // Event handler receives:
    // 1: Data Series generating the event
    // 2: The datetime for the new value
    // 3: The new value
    virtual Event& getNewValueEvent()
    {
        return m_newValueEvt;
    }

    // Appends a value.
    virtual void append(const T& value)
    {
        appendWithDateTime(DateTime(), &value);
    }

	// Appends a value with an associated datetime.
	// Note: If dateTime is not None, it must be greater than the last one.
	virtual void appendWithDateTime(const DateTime& dateTime, const void* value)
    {
        assert(m_dateTimes.size() == m_values.size());

        const T& data = *((T *)value);

        if (value == nullptr || !dateTime.isValid()) {
            return;
        }

        m_dateTimes.push_back(dateTime);
        m_values.push_back(data);

        Event::Context ctx;
        ctx.datetime = dateTime;
        ctx.data     = (void*)value;
        m_newValueEvt.emitEvt(dateTime, (void *)&ctx);
    }

    void clear()
    {
        m_dateTimes.clear();
        m_values.clear();
    }

private:
    Event m_newValueEvt;

	int m_maxLen;
    circular_buffer<DateTime> m_dateTimes;
    circular_buffer<T> m_values;
};

} // namespace AlgoSE

#endif // ALGOSE_DATA_SERIES_H