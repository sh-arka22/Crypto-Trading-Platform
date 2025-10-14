#include <map>
#include <string>
#include "OrderBookEntry.h"
#pragma once
class Wallet{
public:
    Wallet();
    void insertCurrency(const std::string& currency, double amount);
    bool containsCurrency(const std::string& currency, double amount) const;
    bool removeCurrency(const std::string& currency, double amount);
    /** checks if the wallet can cope with this ask or bid */
    bool canFulfillOrder(OrderBookEntry& orderEntry) const;
    /** updates the contents of the wallet, assumes the order made by the owner of the wallet */
    void processSale(const OrderBookEntry& sale);
    std::string toString();
private:
    std::map<std::string, double> currencies;
};