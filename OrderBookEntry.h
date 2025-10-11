#pragma once
#include <string>
enum class OrderBookType { bid, ask};
class OrderBookEntry {
public:
    double price;
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType orderType;
    /*
        // Brace initialization (uniform initialization)
        OrderBookEntry(double price): price{price} {}
        
        // Parentheses initialization (traditional)
        OrderBookEntry(double price): price(price) {}
    */
    OrderBookEntry();
    OrderBookEntry(double _price);
    OrderBookEntry(double p, double a, const std::string& ts, const std::string& prod, OrderBookType ot);
};