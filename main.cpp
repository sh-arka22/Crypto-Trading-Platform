#include <iostream>
#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "MerkelMain.h"
#include "CSVReader.h"
#include "OrderBook.h"

int main() {
    std::cout << "Welcome to the Crypto Trading App!" << std::endl;
    
    MerkelMain app{};
    // app.init();
    // CSVReader csvReader;
    // CSVReader::readCSV("../OrderBook.csv");
    // Wallet wallet;
    // wallet.insertCurrency("USD", 1000.0);
    // wallet.insertCurrency("BTC", 0.5);
    // wallet.insertCurrency("ETH", 2.0);
    // wallet.insertCurrency("LTC", 5.0);
    // std::cout << "Wallet contents:\n" << wallet.toString() << std::endl;
    // wallet.removeCurrency("ETH", 1.0);
    // std::cout << "After removing 1.0 ETH, wallet contents:\n" << wallet.toString() << std::endl;
    // wallet.insertCurrency("ETH", 1.5);
    // std::cout << "After adding 1.5 ETH, wallet contents:\n" << wallet.toString() << std::endl;
    // wallet.removeCurrency("BTC", 0.2);
    // std::cout << "After removing 0.2 BTC, wallet contents:\n" << wallet.toString() << std::endl;
    return 0;
}