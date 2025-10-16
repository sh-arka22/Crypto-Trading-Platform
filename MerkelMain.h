#include <vector>
#include "OrderBookEntry.h"
#include <iostream>
#include "CSVReader.h"
#include "OrderBook.h"
#include "Wallet.h"
#pragma once
class MerkelMain {
public:
    MerkelMain(/* args */);

    /**Call this to start the simulation */
    void init();
private:
    void loadOrderBook();
    void processUserOption(int userOption);
    void printMenu();
    int getUserInput();
    void printHelp();
    void printMarketStats();
    void enterAsk();
    void enterBid();
    void printWalletInfo();
    void goToNextTimeFrame();

    std::string currentTime;

    OrderBook orderBook;

    Wallet wallet;
};
