#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry() {};


OrderBookEntry::OrderBookEntry(double price) : price{price} {}


OrderBookEntry::OrderBookEntry(double p, double a, const std::string& ts, const std::string& prod, OrderBookType ot) 
    : price{p}, amount{a}, timestamp{ts}, product{prod}, orderType{ot} {}



