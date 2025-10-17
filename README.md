# Crypto-Trading-App

A C++ based cryptocurrency trading simulation application that allows users to trade various cryptocurrencies, manage a wallet, and analyze market statistics.

## Table of Contents
- [Features](#features)
- [Project Structure](#project-structure)
- [Compilation](#compilation)
- [Running the Application](#running-the-application)
- [Usage Examples](#usage-examples)
- [Menu Options Explained](#menu-options-explained)

## Features

- **Wallet Management**: Manage multiple cryptocurrencies with automatic balance tracking
- **Order Placement**: Place bid (buy) and ask (sell) orders
- **Market Statistics**: View real-time market data including high, low, average prices, VWAP, and trading volumes
- **Order Matching**: Automatic matching of buy and sell orders
- **Time-based Trading**: Simulate trading across different time frames
- **CSV Data Import**: Load historical trading data from CSV files

## Project Structure

```
Crypto-Trading-App/
├── main.cpp              # Entry point
├── MerkelMain.h/cpp      # Main application logic and menu system
├── Wallet.h/cpp          # Wallet management (balance tracking)
├── OrderBook.h/cpp       # Order book management and matching
├── OrderBookEntry.h/cpp  # Order entry data structure
├── CSVReader.h/cpp       # CSV file parsing
├── OrderBook.csv         # Historical trading data
└── README.md             # This file
```

## Compilation

### Method 1: Using g++ (Recommended)

```bash
g++ -std=c++11 -o trading_app main.cpp MerkelMain.cpp Wallet.cpp OrderBook.cpp OrderBookEntry.cpp CSVReader.cpp
```

### Method 2: Using clang++

```bash
clang++ -std=c++11 -o trading_app main.cpp MerkelMain.cpp Wallet.cpp OrderBook.cpp OrderBookEntry.cpp CSVReader.cpp
```

### With Debugging Symbols (Optional)

```bash
g++ -std=c++11 -g -o trading_app main.cpp MerkelMain.cpp Wallet.cpp OrderBook.cpp OrderBookEntry.cpp CSVReader.cpp
```

## Running the Application

After compilation, run the executable:

```bash
./trading_app
```

## Usage Examples

### Example 1: Basic Workflow - Checking Wallet and Market Stats

```
1. Launch the application: ./trading_app
2. You'll see the welcome message and main menu
3. Select option 5 to view your initial wallet:
   
   Input: 5
   
   Output:
   Wallet Info: Displaying your wallet information...
   BTC: 10
   ETH: 100
   USDT: 10000

4. Select option 2 to view market statistics:
   
   Input: 2
   
   Output:
   === Market Statistics ===
   Product: BTC/USDT
   Time: 2020/03/17 17:01:24
   Asks: 125
     High: 5200.00
     Low: 5000.00
     VWAP: 5100.50
     Average: 5100.00
     Total Volume: 250.5
   Bids: 98
     High: 5050.00
     Low: 4900.00
     ...
```

### Example 2: Placing an Ask Order (Selling Cryptocurrency)

To sell 0.5 BTC at 50000 USDT each:

```
1. Select option 3 (Enter Offer Details)
2. Enter the order in format: PRODUCT,PRICE,AMOUNT
   
   Input: BTC/USDT,50000,0.5
   
   The system will:
   - Check if you have 0.5 BTC in your wallet
   - If yes, place the order
   - If no, display "Insufficient funds"
   
   Output:
   Ask order placed successfully!
   Parsed OrderBookEntry - Price: 50000, Amount: 0.5, Timestamp: 2020/03/17 17:01:24, Product: BTC/USDT, Username: simuser
```

**Format Explanation:**
- `BTC/USDT` = Product (BASE/QUOTE currency pair)
- `50000` = Price per unit in quote currency
- `0.5` = Amount of base currency to sell

### Example 3: Placing a Bid Order (Buying Cryptocurrency)

To buy 2 ETH at 3000 USDT each (costs 6000 USDT total):

```
1. Select option 4 (Enter Bid Details)
2. Enter the order in format: PRODUCT,PRICE,AMOUNT
   
   Input: ETH/USDT,3000,2
   
   The system will:
   - Calculate total cost: 3000 × 2 = 6000 USDT
   - Check if you have 6000 USDT
   - If yes, place the order
   
   Output:
   Bid order placed successfully!
   Parsed OrderBookEntry - Price: 3000, Amount: 2, Timestamp: 2020/03/17 17:01:24, Product: ETH/USDT, Username: simuser
```

### Example 4: Advancing Time and Order Matching

```
1. After placing orders, select option 6 (Go to Next Time Frame)
2. The system will:
   - Match your orders with existing market orders
   - Execute trades if matches are found
   - Update your wallet automatically
   - Move to the next timestamp
   
   Output:
   Moving to the next time frame...
   Matching orders for product: BTC/USDT at time: 2020/03/17 17:01:24
   Sale - Price: 50000, Amount: 0.5, Timestamp: 2020/03/17 17:01:24, Product: BTC/USDT, Type: User Sale
   Advancing to next timestamp: 2020/03/17 17:01:30

3. Check your wallet (option 5) to see updated balances:
   
   Output:
   BTC: 9.5      (decreased by 0.5)
   ETH: 102      (increased by 2)
   USDT: 19000   (increased by 25000 from BTC sale, decreased by 6000 for ETH purchase)
```

## Menu Options Explained

### 1. Help
Displays help information about the application.

### 2. Market Stats
Shows comprehensive market data for all trading pairs:
- Number of asks and bids
- High/Low prices
- Volume-Weighted Average Price (VWAP)
- Average price
- Total trading volume

**Use Case**: Check market prices before placing orders

### 3. Enter Offer Details (ASK - Sell Orders)
Place a sell order for cryptocurrency you own.

**Input Format**: `PRODUCT,PRICE,AMOUNT`
**Example**: `BTC/USDT,50000,0.5` (Sell 0.5 BTC at 50000 USDT each)

**Requirements**:
- You must have sufficient base currency (BTC in this example)
- Price must be positive
- Amount must be positive

### 4. Enter Bid Details (BID - Buy Orders)
Place a buy order to purchase cryptocurrency.

**Input Format**: `PRODUCT,PRICE,AMOUNT`
**Example**: `ETH/USDT,3000,2` (Buy 2 ETH at 3000 USDT each)

**Requirements**:
- You must have sufficient quote currency (USDT in this example)
- Total cost = PRICE × AMOUNT
- You need at least 6000 USDT for the example above

### 5. Print Wallet Info
Displays current balances for all currencies in your wallet.

**Example Output**:
```
BTC: 10
ETH: 100
USDT: 10000
```

### 6. Go to Next Time Frame
Advances the simulation to the next timestamp:
1. Matches your orders against market orders
2. Executes trades when bid prices ≥ ask prices
3. Updates wallet balances automatically
4. Moves to next time period in the dataset

### 0. Exit
Safely exits the application.

## Complete Trading Session Example

```bash
# 1. Compile the application
g++ -std=c++11 -o trading_app main.cpp MerkelMain.cpp Wallet.cpp OrderBook.cpp OrderBookEntry.cpp CSVReader.cpp

# 2. Run the application
./trading_app

# 3. Check initial wallet
Input: 5
Output: BTC: 10, ETH: 100, USDT: 10000

# 4. View market statistics
Input: 2
[View current prices for all products]

# 5. Sell 1 BTC at 55000 USDT
Input: 3
Input: BTC/USDT,55000,1

# 6. Buy 5 ETH at 3500 USDT each
Input: 4
Input: ETH/USDT,3500,5

# 7. Advance time to execute orders
Input: 6
[Orders matched and wallet updated]

# 8. Check updated wallet
Input: 5
Output: [Updated balances after trades]

# 9. Continue trading or exit
Input: 0
```

## Trading Tips

1. **Always check market stats** before placing orders to ensure competitive pricing
2. **Monitor your wallet** regularly to track available balances
3. **Advance time frames** to see your orders execute
4. **Start small** - test with small amounts to understand the system
5. **Product format** - Always use BASE/QUOTE format (e.g., BTC/USDT, ETH/BTC)

## Common Issues and Solutions

### Issue: "Insufficient funds in wallet"
**Solution**: Check your wallet (option 5) and ensure you have enough:
- For ASK orders: You need the base currency (left side of pair)
- For BID orders: You need quote currency (right side) = PRICE × AMOUNT

### Issue: "Invalid product format"
**Solution**: Use the format: BASE/QUOTE (e.g., BTC/USDT, not BTC-USDT or BTCUSDT)

### Issue: Orders not executing
**Solution**: Advance to the next time frame (option 6) to trigger order matching

### Issue: Cannot compile
**Solution**: Ensure all .cpp and .h files are in the same directory and you have C++11 support

## Initial Wallet Balances

The application starts with:
- **10,000 USDT** - For buying cryptocurrencies
- **10 BTC** - For selling/trading
- **100 ETH** - For selling/trading

You can modify these in `MerkelMain.cpp` in the `init()` function.

## Order Matching Logic

- **ASK (Sell)**: You offer to sell at a specific price
- **BID (Buy)**: You offer to buy at a specific price
- **Match occurs when**: Bid price ≥ Ask price
- **Execution price**: Typically the ask price (seller's price)
- **Your orders** are matched against market orders when you advance time

## Data Source

The application reads historical order data from `OrderBook.csv`. This file should contain:
- Timestamp
- Product (e.g., BTC/USDT)
- Order type (ask/bid)
- Price
- Amount
- Username

---

**Happy Trading! 🚀📈**
