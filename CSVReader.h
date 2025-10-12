#pragma once
#include <string>
#include <vector>

#include "OrderBookEntry.h"

class CSVReader {
public:
    CSVReader();

    /** State less function to read the CSV file*/
    static std::vector<OrderBookEntry> readCSV(std::string csvFile);


private:
    static std::vector<std::string> tokenise(std::string csvLine, char separator);
    static OrderBookEntry stringToOBE(const std::vector<std::string>& tokens);
};