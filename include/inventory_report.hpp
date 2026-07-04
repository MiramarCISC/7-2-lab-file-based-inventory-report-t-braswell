#ifndef INVENTORY_REPORT_HPP
#define INVENTORY_REPORT_HPP

#include <string>

const int MAX_ITEMS = 100;

struct InventoryItem {
    std::string sku;
    std::string name;
    int quantity;
    double price;
};

bool isValidQuantity(int quantity);
bool isValidPrice(double price);
double calculateItemValue(const InventoryItem& item);

int readInventoryFile(std::string filename, InventoryItem items[], int maxItems);
bool writeInventoryReport(std::string filename, const InventoryItem items[], int count);

double calculateTotalInventoryValue(const InventoryItem items[], int count);
int findItemBySku(const InventoryItem items[], int count, std::string sku);
int findHighestValueItemIndex(const InventoryItem items[], int count);

#endif
