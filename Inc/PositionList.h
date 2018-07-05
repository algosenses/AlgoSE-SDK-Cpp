#ifndef POSITION_LIST_H
#define POSITION_LIST_H

#include "Defines.h"

namespace AlgoSE
{

class AccountPositionListImpl;
class StrategyPositionListImpl;

class ALGOSE_API AccountPositionList
{
public:
    typedef AccountPosition* iterator;
    typedef const AccountPosition* const_iterator;

    AccountPositionList();
    AccountPositionList(const AccountPositionList& other);
    ~AccountPositionList();
    AccountPositionList &operator=(const AccountPositionList& other);

    void clear();
    int size() const;
    const AccountPosition& operator[](int idx) const;

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    AccountPositionListImpl& getImplementor() const;

private:
    AccountPositionListImpl* m_implementor;
};

class ALGOSE_API StrategyPositionList
{
public:
    typedef StrategyPosition* iterator;
    typedef const StrategyPosition* const_iterator;

    StrategyPositionList();
    StrategyPositionList(const StrategyPositionList& other);
    ~StrategyPositionList();
    StrategyPositionList &operator=(const StrategyPositionList& other);

    void clear();
    int size() const;
    const StrategyPosition& operator[](int idx) const;
    
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    StrategyPositionListImpl& getImplementor() const;

private:
    StrategyPositionListImpl* m_implementor;
};

} // namespace AlgoSE

#endif // POSITION_LIST_H