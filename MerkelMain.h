#include <vector>
#include "OrderBookEntry.h"
#include <iostream>
class MerkelMain {
public:
    MerkelMain(/* args */);

    /**Call this to start the simulation */
    void init();
private:
    int loadOrderBook();
    void processUserOption(int userOption);
    void printMenu();
    int getUserInput();
    void printHelp();
    void printMarketStats();
    void enterOfferDetails();
    void enterBidDetails();
    void printWalletInfo();
    void goToNextTimeFrame();

    /**
     * Vector to hold order book entries
     */
    std::vector<OrderBookEntry> orders; // vector to hold order book entries
};
