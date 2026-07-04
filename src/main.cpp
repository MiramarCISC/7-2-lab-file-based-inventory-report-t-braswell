#include "inventory_report.hpp"
#include <iostream>

using namespace std;

int main() {
    InventoryItem items[MAX_ITEMS];
    string inputFile = "data/inventory.txt";
    string outputFile = "inventory_report.txt";

    cout << "File-Based Inventory Report" << endl;
    cout << endl;

    int count = readInventoryFile(inputFile, items, MAX_ITEMS);

    cout << "Read " << count << " item(s)." << endl;
    cout << "Total inventory value: "
         << calculateTotalInventoryValue(items, count)
         << endl;

    int highestIndex = findHighestValueItemIndex(items, count);

    if (highestIndex != -1) {
        cout << "Highest value item: "
             << items[highestIndex].sku << " "
             << items[highestIndex].name
             << endl;
    }

    if (writeInventoryReport(outputFile, items, count)) {
        cout << "Report written to " << outputFile << endl;
    } else {
        cout << "Unable to write report." << endl;
    }

    return 0;
}
