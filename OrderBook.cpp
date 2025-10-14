#include <iostream>
#include "OrderBook.h"
#include <map>
#include <algorithm>
#include <queue>

OrderBook::OrderBook(std::string csvFilename) {
    std::cout << "Loading order book from: " << csvFilename << std::endl;
    orders = CSVReader::readCSV(csvFilename);
}

std::vector<std::string> OrderBook::getKnownProducts() {
    std::vector<std::string> products;
    std::map<std::string, bool> productMap;

    for(const OrderBookEntry& order : orders) {
        if(productMap.find(order.product) == productMap.end()) {
            products.push_back(order.product);
            productMap[order.product] = true;
        }
    }

    return products;
}

std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, std::string product, std::string timestamp) {
    std::vector<OrderBookEntry> filteredOrders;

    for(const OrderBookEntry& order : orders) {
        if(order.orderType == type && order.product == product && order.timestamp == timestamp) {
            filteredOrders.push_back(order);
        }
    }

    return filteredOrders;
}

std::string OrderBook::getEarliestTime() {
    if(!orders.empty()) {
        return orders[0].timestamp;
    }
    return std::string();
}

std::string OrderBook::getNextTime(std::string timestamp) {
    if(orders.empty()) return std::string();
    for(size_t i = 0; i < orders.size(); ++i) {
        if(orders[i].timestamp != timestamp) {
            return orders[i].timestamp;
        }
    }
    return orders.back().timestamp;
}

std::string OrderBook::getPreviousTime(std::string timestamp) {
    if(orders.empty()) return std::string();
    std::string previousTime = orders[0].timestamp;
    for(size_t i = 0; i < orders.size(); ++i) {
        if(orders[i].timestamp != timestamp) {
            previousTime = orders[i].timestamp;
        }
        else{
            return previousTime;
        }
    }
    return orders[0].timestamp;
}

void OrderBook::insertOrder(const OrderBookEntry &order) {
    orders.push_back(order);
    
    // Keep orders sorted by timestamp
    std::sort(orders.begin(), orders.end(), [](const OrderBookEntry &a, const OrderBookEntry &b) {
        return a.timestamp < b.timestamp;
    });
}

std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp) {
    // Priority queue for asks (min-heap based on price)
    auto askComparator = [](const OrderBookEntry& a, const OrderBookEntry& b) {
        return a.price > b.price; // Lowest price has highest priority
    };
    std::priority_queue<OrderBookEntry, std::vector<OrderBookEntry>, decltype(askComparator)> askQueue(askComparator);

    // Priority queue for bids (max-heap based on price)
    auto bidComparator = [](const OrderBookEntry& a, const OrderBookEntry& b) {
        return a.price < b.price; // Highest price has highest priority
    };
    std::priority_queue<OrderBookEntry, std::vector<OrderBookEntry>, decltype(bidComparator)> bidQueue(bidComparator);

    // Populate the priority queues
    for (const auto& ask : getOrders(OrderBookType::ask, product, timestamp)) {
        askQueue.push(ask);
    }
    for (const auto& bid : getOrders(OrderBookType::bid, product, timestamp)) {
        bidQueue.push(bid);
    }

    std::vector<OrderBookEntry> sales;

    // Match asks and bids
    while (!askQueue.empty() && !bidQueue.empty()) {
        OrderBookEntry ask = askQueue.top();
        OrderBookEntry bid = bidQueue.top();

        OrderBookType type = OrderBookType::asksale; // Default to asksale
        

        if (bid.price >= ask.price) {
            // Determine the trade amount (partial matching allowed)
            double tradeAmount = std::min(ask.amount, bid.amount);

            OrderBookEntry sale(
                ask.price, // Use ask price for the trade
                tradeAmount,
                timestamp,
                product,
                type // Use the defined type for completed trades
            );

            // Create a sale entry
            if(bid.username == "simuser") {
                sale.orderType = OrderBookType::bidsale; // If the bid is from the user, mark it as bidsale
                sale.username = "simuser";
            }
            if(ask.username == "simuser") {
                sale.orderType = OrderBookType::asksale; // If the ask is from the user, mark it as asksale
                sale.username = "simuser";
            }


            sales.push_back(sale);

            // Update the amounts
            ask.amount -= tradeAmount;
            bid.amount -= tradeAmount;

            // Remove fully matched orders from the queues
            askQueue.pop();
            bidQueue.pop();

            if (ask.amount > 0) {
                askQueue.push(ask); // Push back remaining ask
            }
            if (bid.amount > 0) {
                bidQueue.push(bid); // Push back remaining bid
            }
        } 
        else {
            // No match possible for this ask
            // Create a sale entry similar to the original implementation
            OrderBookEntry sale(
                bid.price, // Use bid price for the trade
                0.0,       // No trade amount
                timestamp,
                product,
                type// New type for completed trades
            );
            sales.push_back(sale);

            // Update the amounts
            ask.amount -= bid.amount;
            bid.amount = 0;

            // Remove the bid from the queue
            bidQueue.pop();

            continue; // Move to the next ask if this one cannot be matched
        }
    }

    return sales;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry> &orders) {
    if(orders.empty()) return 0.0;
    double highPrice = orders[0].price;
    
    for(const auto& order : orders) {
        if(order.price > highPrice) {
            highPrice = order.price;
        }
    }
    
    return highPrice;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry> &orders) {
    if(orders.empty()) return 0.0;
    double lowPrice = orders[0].price;
    for(const auto& order : orders) {
        if(order.price < lowPrice) {
            lowPrice = order.price;
        }
    }
    
    return lowPrice;
}

double OrderBook::getAveragePrice(std::vector<OrderBookEntry> &orders) {
    if(orders.empty()) {
        return 0.0;
    }
    
    double sum = 0.0;
    for(const auto& order : orders) {
        sum += order.price;
    }
    
    return sum / orders.size();
}

double OrderBook::getTotalVolume(std::vector<OrderBookEntry> &orders) {
    if(orders.empty()) {
        return 0.0;
    }
    
    double totalVolume = 0.0;
    for(const auto& order : orders) {
        totalVolume += order.amount;
    }
    
    return totalVolume;
}

double OrderBook::getVWAP(std::vector<OrderBookEntry> &orders) {
    if(orders.empty()) {
        return 0.0;
    }
    
    double totalValue = 0.0;  // Sum of (price * amount)
    double totalVolume = 0.0; // Sum of amounts
    
    for(const auto& order : orders) {
        totalValue += order.price * order.amount;
        totalVolume += order.amount;
    }
    
    if(totalVolume == 0.0) {
        return 0.0;
    }
    
    return totalValue / totalVolume;
}
