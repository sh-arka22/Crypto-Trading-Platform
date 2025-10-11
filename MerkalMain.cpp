#include "MerkelMain.h"

void MerkelMain::init() {
    std::cout << "Initializing the Crypto Trading App..." << std::endl;


    while(true){
        int returnValue = loadOrderBook();
        if(returnValue > 0){
            std::cout << "Order book loaded with " << returnValue << " entries." << std::endl;
            break;
        }
        else{
            std::cout << "Failed to load order book. Retrying..." << std::endl;
        }
    }

    printMenu();

    int userOption = -1;
    while (userOption != 0) {
        userOption = getUserInput();
        if (userOption == 0) {
            std::cout << "Exiting the application. Goodbye!" << std::endl;
            break;
        }
        else{
            processUserOption(userOption);
            printMenu();
        }
    }
}

/**Constructor call the init function */
MerkelMain::MerkelMain() {
    // Constructor implementation (if needed)
    init();
}

int MerkelMain::loadOrderBook() {

    std::cout << "Loading order book..." << std::endl;
    // Implementation to load order book data
    orders.push_back(OrderBookEntry(100.0, 0.5, "2023-10-01T12:00:00Z", "BTC-USD", OrderBookType::bid));
    orders.push_back(OrderBookEntry(101.0, 0.3, "2023-10-01T12:01:00Z", "BTC-USD", OrderBookType::ask));
    // More loading logic here
    return orders.size();
}


void MerkelMain::printMenu() {
    std::cout << "\n=== Main Menu ===" << std::endl;
    std::cout << "1. Help" << std::endl;
    std::cout << "2. Market Stats" << std::endl;
    std::cout << "3. Enter Offer Details" << std::endl;
    std::cout << "4. Enter Bid Details" << std::endl;
    std::cout << "5. Print Wallet Info" << std::endl;
    std::cout << "6. Go to Next Time Frame" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "=================\n" << std::endl;
}

int MerkelMain::getUserInput() {
    int option;
    std::cout << "Select an option: ";
    std::cin >> option;
    return option;
}

void MerkelMain::processUserOption(int userOption) {
    switch (userOption) {
        case 1:
            printHelp();
            break;
        case 2:
            printMarketStats();
            break;
        case 3:
            enterOfferDetails();
            break;
        case 4:
            enterBidDetails();
            break;
        case 5:
            printWalletInfo();
            break;
        case 6:
            goToNextTimeFrame();
            break;
        default:
            std::cout << "Invalid option." << std::endl;
            break;
    }
}

void MerkelMain::printHelp() {
    std::cout << "Help: This is a crypto trading application. Use the menu to navigate." << std::endl;
}

void MerkelMain::printMarketStats() {
    std::cout << "Market Stats: Displaying current Order Book..." << orders.size() << std::endl;
}

void MerkelMain::enterOfferDetails() {
    std::cout << "Enter Offer Details: Please provide the offer details..." << std::endl;
}

void MerkelMain::enterBidDetails() {
    std::cout << "Enter Bid Details: Please provide the bid details..." << std::endl;
}

void MerkelMain::printWalletInfo() {
    std::cout << "Wallet Info: Displaying your wallet information..." << std::endl;
}

void MerkelMain::goToNextTimeFrame() {
    std::cout << "Moving to the next time frame..." << std::endl;
}
