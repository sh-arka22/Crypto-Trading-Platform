#pragma once

#include "OrderBookEntry.h"
#include "CSVReader.h"

class OrderBook {
public:
    /** Default constructor - does not load any CSV file. */
    OrderBook();

    /** This constructor initializes the OrderBook with a CSV file. */
    OrderBook(std::string csvFilename);
    /** Returns a vector of known products from the dataset. */
    std::vector<std::string> getKnownProducts();
    /** return vector of Orders according to the sent filters*/
    std::vector<OrderBookEntry> getOrders(OrderBookType type, std::string product, std::string timestamp);
    /** Returns the earliest timestamp in the dataset */
    std::string getEarliestTime();
    /** Returns the next timestamp based on the provided timestamp */
    std::string getNextTime(std::string timestamp);
    /** Returns the previous timestamp based on the provided timestamp */
    std::string getPreviousTime(std::string timestamp);
    /** Inserts a new order into the order book */
    void insertOrder(const OrderBookEntry& order);

    std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);



    /** Static methods for calculating statistics on a vector of OrderBookEntryies that I will provide not its own orders */
    static double getHighPrice(std::vector<OrderBookEntry>& orders);
    static double getLowPrice(std::vector<OrderBookEntry>& orders);
    static double getAveragePrice(std::vector<OrderBookEntry>& orders);
    static double getTotalVolume(std::vector<OrderBookEntry>& orders);
    /** Returns the Volume Weighted Average Price (VWAP) of the orders */
    static double getVWAP(std::vector<OrderBookEntry>& orders);

private:
    std::vector<OrderBookEntry> orders;
};