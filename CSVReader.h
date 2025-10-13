#pragma once
#include <string>
#include <vector>

#include "OrderBookEntry.h"

class CSVReader {
public:
    CSVReader();

    /** State less function to read the CSV file*/
    static std::vector<OrderBookEntry> readCSV(std::string csvFile);

    /** seperates out the data from a CSV line */
    static std::vector<std::string> tokenise(std::string csvLine, char separator);

    /** Implement conversion from tokens to OrderBookEntry */
    static OrderBookEntry stringToOBE(const std::string& price, const std::string& amount, const std::string& timestamp, const std::string& product, OrderBookType orderBookType);

private:
    
    /** Helper function to convert tokens to OrderBookEntry */
    static OrderBookEntry stringToOBE(const std::vector<std::string>& tokens);
};