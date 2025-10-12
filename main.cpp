#include <iostream>
#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "MerkelMain.h"
#include "CSVReader.h"

// Keep only these utility functions in main.cpp
double computeAveragePrice(const std::vector<OrderBookEntry>& entries) {
    if (entries.empty()) {
        return 0.0;
    }
    
    double sum = 0.0;
    for (const auto& entry : entries) {
        sum += entry.price;
    }
    return sum / entries.size();
}

double computeLowPrice(const std::vector<OrderBookEntry>& entries) {
    if (entries.empty()) {
        return 0.0;
    }
    
    double lowPrice = entries[0].price;
    for (const auto& entry : entries) {
        if (entry.price < lowPrice) {
            lowPrice = entry.price;
        }
    }
    return lowPrice;
}

double computeHighPrice(const std::vector<OrderBookEntry>& entries) {
    if (entries.empty()) {
        return 0.0;
    }
    
    double highPrice = entries[0].price;
    for (const auto& entry : entries) {
        if (entry.price > highPrice) {
            highPrice = entry.price;
        }
    }
    return highPrice;
}

double computePriceSpread(const std::vector<OrderBookEntry>& entries) {
    if (entries.empty()) {
        return 0.0;
    }
    
    return computeHighPrice(entries) - computeLowPrice(entries);
}

int main() {
    std::cout << "Welcome to the Crypto Trading App!" << std::endl;
    
    MerkelMain app{};
    // app.init();
    // CSVReader csvReader;
    // CSVReader::readCSV("../OrderBook.csv");
    return 0;
}