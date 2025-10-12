#include "CSVReader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

CSVReader::CSVReader() {
    // Constructor implementation (if needed)
}

/** seperates out the data from a CSV line */
std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator) {
    std::vector<std::string> tokens;
    signed int start, end;
    std::string token;
    start = csvLine.find_first_not_of(separator, 0);
    do {
        end = csvLine.find_first_of(separator, start);
        if (start == csvLine.length() || start == end) break;
        if (end >= 0) {
            token = csvLine.substr(start, end - start);
        } 
        else {
            token = csvLine.substr(start, csvLine.length() - start);
        }
        start = end + 1;
        tokens.push_back(token);
    } while (end > 0);
    return tokens;
}

/** Implement conversion from tokens to OrderBookEntry */
OrderBookEntry CSVReader::stringToOBE(const std::vector<std::string>& tokens) {

    // Implemet the conversion logic based on the expected format of tokens
    // For example, if tokens are in the order: timestamp, product, order_type, price, amount
    // You would parse them accordingly and create an OrderBookEntry object
    double price;
    double amount;
    
    if(tokens.size() != 5) {
        throw std::runtime_error("Invalid number of data entries inside the token to convert to OrderBookEntry");
    }

    try{
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
    }
    catch(const std::exception& e){
        throw std::runtime_error("Exception inside stringToOBE: " + std::string(e.what()));
    }

    return OrderBookEntry(/* parameters based on tokens */ 
                                price, 
                                amount, 
                                tokens[0], 
                                tokens[1], 
                                tokens[2] == "bid" ? OrderBookType::bid : OrderBookType::ask
                            );
}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFilename) {
    std::vector<OrderBookEntry> entries;
    
    std::ifstream file(csvFilename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open the file: " + csvFilename);
    }

    std::string line;
    while (std::getline(file, line)) {
        try{
            std::vector<std::string> tokens = tokenise(line, ',');
            entries.push_back(stringToOBE(tokens));
        }
        catch(const std::exception& e){
            std::cerr << "Inside CSVReader::readCSV exception occurred while reading the line {" << line << "}: " << e.what() << std::endl;
            continue; // Skip this line and continue with the next
        }
    }
    std::cout << "CSVReader::readCSV read " << entries.size() << " entries from " << csvFilename << std::endl;
    return entries;
}