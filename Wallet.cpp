#include "Wallet.h"
#include "CSVReader.h"
#include <iostream>
#include <sstream>
#include <stdexcept>  
#include <vector>
#include <map>
#include <string> 
Wallet::Wallet() {

}

void Wallet::insertCurrency(const std::string &currency, double amount) {
    if(amount < 0) {
        throw std::invalid_argument("Amount must be positive."); // Ignore non-positive amounts
    }
    double currentAmount = 0.0;
    if(currencies.find(currency) != currencies.end()) {
        currentAmount = currencies[currency];
        currencies[currency] = currentAmount + amount;
    } 
    else {
        currencies[currency] = amount;
    }
}
    

bool Wallet::containsCurrency(const std::string &currency, double amount) const {

    auto it = currencies.find(currency);
    if (it != currencies.end()) {
        return it->second >= amount;
    }
    return false;
}

bool Wallet::removeCurrency(const std::string &currency, double amount) {
    if(amount < 0) {
        throw std::invalid_argument("Amount must be positive."); // Ignore non-positive amounts
    }
    auto it = currencies.find(currency);
    if (it != currencies.end() && it->second >= amount) {
        it->second -= amount;
        if (it->second == 0) {
            currencies.erase(it);
        }
        return true;
    
    }
    return false;
}

bool Wallet::canFulfillOrder(OrderBookEntry &orderEntry) const {
    std::vector<std::string> parts = CSVReader::tokenise(orderEntry.product, '/');
    if (parts.size() != 2) {
        throw std::invalid_argument("Invalid product format. Expected 'BASE/QUOTE'.");
    }

    if (orderEntry.orderType == OrderBookType::ask) {
        return containsCurrency(parts[0], orderEntry.amount);
    }
    if (orderEntry.orderType == OrderBookType::bid) {
        const double cost = orderEntry.price * orderEntry.amount;
        return containsCurrency(parts[1], cost);
    }
    return false;
}

void Wallet::processSale(const OrderBookEntry &sale) {
    // Extract the currencies from the product string (e.g., "BTC/USD" -> "BTC" and "USD")
    std::vector<std::string> currencies = CSVReader::tokenise(sale.product, '/');
    if (currencies.size() != 2) {
        throw std::invalid_argument("Invalid product format. Expected 'BASE/QUOTE'.");
    }

    // If it's an ask sale, we sold the base currency and received quote currency
    if(sale.orderType == OrderBookType::asksale) {
        insertCurrency(currencies[1], sale.price * sale.amount); // Add quote currency (e.g., USD)
        removeCurrency(currencies[0], sale.amount); // Remove base currency (e.g., BTC)
    }
    // If it's a bid sale, we bought the base currency and spent quote currency
    else if(sale.orderType == OrderBookType::bidsale) {
        insertCurrency(currencies[0], sale.amount); // Add base currency (e.g., BTC)
        removeCurrency(currencies[1], sale.price * sale.amount); // Remove quote currency (e.g., USD)
    }
}

std::string Wallet::toString() {

    for(std::pair<std::string, double> pair : currencies) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    std::ostringstream oss;
    for(const auto& pair : currencies) {
        oss << pair.first << ": " << pair.second << "\n";
    }
    return oss.str();
}
