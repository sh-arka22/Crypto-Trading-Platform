#include <iostream>
#include <string>
#include <vector>
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

OrderBookEntry::OrderBookEntry() {};
OrderBookEntry::OrderBookEntry(double price) : price{price} {}
OrderBookEntry::OrderBookEntry(double p, double a, const std::string& ts, const std::string& prod, OrderBookType ot) 
    : price{p}, amount{a}, timestamp{ts}, product{prod}, orderType{ot} {}

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

    auto printHelp = [&](){
        std::cout << "Help: This app allows you to trade cryptocurrencies." << std::endl;
    };
    auto printMarketStats = [&](){
        std::cout << "Market Stats: Current market data..." << std::endl;
    };
    auto enterOfferDetails = [&](){
        std::cout << "Enter Offer Details: Please provide the details..." << std::endl;
    };
    auto enterBidDetails = [&](){
        std::cout << "Enter Bid Details: Please provide the details..." << std::endl;
    };
    auto printWalletInfo = [&](){
        std::cout << "Wallet Info: Your current balance is..." << std::endl;
    };
    auto gotToNextTimeFrame = [&](){
        std::cout << "Moving to the next time frame..." << std::endl;
    };



    // Function to print the menu
    auto printMenu = [&]() {
        std::cout << "0. Exit" << std::endl;
        std::cout << "Menu Options:" << std::endl;
        std::cout << "1. Help" << std::endl;
        std::cout << "2. Exchange Stats" << std::endl;
        std::cout << "3. Make an Offer" << std::endl;
        std::cout << "4. Make a Bid" << std::endl;
        std::cout << "5. Wallet" << std::endl;
        std::cout << "Please select an option: ";
    };

    auto getUserInput = [&]() {
        int option;
        std::cin >> option;
        return option;
    };

    auto processUserOption = [&](int userOption) {
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
                gotToNextTimeFrame();
                break;
            default:
                std::cout << "Invalid option." << std::endl;
                break;
        }
    };

    // double price = 9166.0;
    // double amount = 0.1;
    // std::string timeStamp = {"2020/03/17 17:01:45.111661"}; //creating the constructor of string class
    // std::string product = {"BTC/USD"};
    // // std::string orderType = {"bid"};
    // OrderBookType orderType = OrderBookType::bid;

    std::vector<double> prices;
    std::vector<double> amounts;
    std::vector<std::string> timeStamps;
    std::vector<std::string> products;
    std::vector<OrderBookType> orderTypes;

    prices.push_back(9166.0);
    amounts.push_back(0.1);
    timeStamps.push_back("2020/03/17 17:01:45.111661");
    products.push_back("BTC/USD");
    orderTypes.push_back(OrderBookType::bid);


    OrderBookEntry order1;
    order1.price = 1000;
    order1.amount = 0.002;
    order1.timestamp = "2020/03/17 17:01:45.111661";
    order1.product = "BTC/USD";
    order1.orderType = OrderBookType::bid;

    OrderBookEntry order2(2000, 0.005, "2020/03/17 17:01:45.111661", "BTC/USD", OrderBookType::ask);

    OrderBookEntry order3(3000); // Using the new constructor

    OrderBookEntry order4{300, 0.01, "2020/03/17 17:01:45.111661", "BTC/USD", OrderBookType::bid}; // Default constructor

    OrderBookEntry order5{}; // Default constructor

    OrderBookEntry order6(1500, 0.03, "2020/03/17 17:01:45.111661", "ETH/USD", OrderBookType::bid);
    
    std::vector<OrderBookEntry> orders;
    
    orders.push_back(order5);
    orders.push_back(order6);
    orders.push_back(order1);
    orders.push_back(order2);
    orders.push_back(order3);
    orders.push_back(order4);
    std::cout << "Orders in the Order Book:" << std::endl;
    for (const auto& order : orders) {
        std::cout << "Order - Price: " << order.price 
                  << ", Amount: " << order.amount 
                  << ", Timestamp: " << order.timestamp 
                  << ", Product: " << order.product 
                  << ", Order Type: " << (order.orderType == OrderBookType::bid ? "bid" : "ask") 
                  << std::endl;
    }

    // Test the utility functions
    std::cout << "\n=== Order Book Analysis ===" << std::endl;
    std::cout << "Average Price: $" << computeAveragePrice(orders) << std::endl;
    std::cout << "Lowest Price: $" << computeLowPrice(orders) << std::endl;
    std::cout << "Highest Price: $" << computeHighPrice(orders) << std::endl;
    std::cout << "Price Spread: $" << computePriceSpread(orders) << std::endl;
    std::cout << "================================\n" << std::endl;

    // Main loop
    while (true) {
        printMenu();
        int userOption = getUserInput();
        printf("You selected option: %d\n", userOption);
        if (userOption == 0) {
            break;
        }
        processUserOption(userOption);
        std::cout << "----------------------------------------" << std::endl;
    }
    return 0;
}