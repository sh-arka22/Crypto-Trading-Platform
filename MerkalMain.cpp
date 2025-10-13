#include "MerkelMain.h"

void MerkelMain::init() {
    std::cout << "Initializing the Crypto Trading App..." << std::endl;


    // while(true){
    //     int returnValue = loadOrderBook();
    //     if(returnValue > 0){
    //         std::cout << "Order book loaded with " << returnValue << " entries." << std::endl;
    //         break;
    //     }
    //     else{
    //         std::cout << "Failed to load order book. Retrying..." << std::endl;
    //     }
    // }
    currentTime = orderBook.getEarliestTime();
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

// int MerkelMain::loadOrderBook() {

//     orders = CSVReader::readCSV("../OrderBook.csv");
//     return orders.size();
// }


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
    std::cout << "Current Time: " << currentTime << std::endl;
}

int MerkelMain::getUserInput() {
    int option;
    std::string line;
    std::cout << "Select an option: ";
    std::getline(std::cin, line);
    try{
        option = std::stoi(line);
    }
    catch(const std::exception& e){
        std::cout << "Invalid input. Please enter a number corresponding to the menu options." << std::endl;
        return -1;
    }
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
            enterAsk();
            break;
        case 4:
            enterBid();
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

/** This function displays market statistics */
void MerkelMain::printMarketStats() {
    std::cout << "\n=== Market Statistics ===" << std::endl;
    
    for(const std::string &product : orderBook.getKnownProducts()) {
        std::cout << "\nProduct: " << product << std::endl;
        std::cout << "Time: " << currentTime << std::endl;

        // Get ask orders
        std::vector<OrderBookEntry> asks = orderBook.getOrders(OrderBookType::ask, product, currentTime);
        std::cout << "Asks: " << asks.size() << std::endl;
        if(!asks.empty()) {
            std::cout << "  High: " << orderBook.getHighPrice(asks) << std::endl;
            std::cout << "  Low: " << orderBook.getLowPrice(asks) << std::endl;
            std::cout << "  VWAP: " << orderBook.getVWAP(asks) << std::endl;
            std::cout << "  Average: " << orderBook.getAveragePrice(asks) << std::endl;
            std::cout << "  Total Volume: " << orderBook.getTotalVolume(asks) << std::endl;
        }

        // Get bid orders  
        std::vector<OrderBookEntry> bids = orderBook.getOrders(OrderBookType::bid, product, currentTime);
        std::cout << "Bids: " << bids.size() << std::endl;
        if(!bids.empty()) {
            std::cout << "  High: " << orderBook.getHighPrice(bids) << std::endl;
            std::cout << "  Low: " << orderBook.getLowPrice(bids) << std::endl;
            std::cout << "  VWAP: " << orderBook.getVWAP(bids) << std::endl;
            std::cout << "  Average: " << orderBook.getAveragePrice(bids) << std::endl;
            std::cout << "  Total Volume: " << orderBook.getTotalVolume(bids) << std::endl;
        }
        std::cout << "-------------------" << std::endl;
    }
}

/** This function allows users to enter offer details */
void MerkelMain::enterAsk() {
    std::cout << "Enter Offer Details: Please provide the offer details..." << std::endl;
    std::string input;
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // To ignore the newline character left in the input buffer
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if(tokens.size() != 3) {
        std::cout << "MerkalMain::enterAsk -> Error: Please provide correct ASK details" << std::endl;
        return;
    }
    else{
        
        try{
            OrderBookEntry obe = CSVReader::stringToOBE(tokens[1], tokens[2], currentTime, tokens[0], OrderBookType::ask);
            orderBook.insertOrder(obe);
            std::cout << "Parsed OrderBookEntry - Price: " << obe.price << ", Amount: " << obe.amount << ", Timestamp: " << obe.timestamp << ", Product: " << obe.product << std::endl;
        } 
        catch (const std::exception& e) {
            std::cout << "MerkalMain::enterAsk -> Error: " << e.what() << std::endl;
        }
    }
    std::cout << "You entered: " << input << std::endl;
}

/** This function allows users to enter bid details */
void MerkelMain::enterBid() {
    std::cout << "Enter Bid Details: Please provide the bid details..." << std::endl;
    std::string input;
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // To ignore the newline character left in the input buffer
    std::getline(std::cin, input);
    std::cout << "You entered: " << input << std::endl;
}

/** This function prints wallet information */
void MerkelMain::printWalletInfo() {
    std::cout << "Wallet Info: Displaying your wallet information..." << std::endl;
}

/** This function advances to the next time frame in the order book */
void MerkelMain::goToNextTimeFrame() {
    std::cout << "Moving to the next time frame..." << std::endl;
    currentTime = orderBook.getNextTime(currentTime);
}
