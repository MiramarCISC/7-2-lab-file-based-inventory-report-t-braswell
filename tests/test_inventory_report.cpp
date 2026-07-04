#include "inventory_report.hpp"
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool nearlyEqual(double actual, double expected, double tolerance = 0.0001) {
    return fabs(actual - expected) <= tolerance;
}

void createTestInventoryFile(string filename) {
    ofstream out(filename);

    out << "A100 Apples 10 1.50" << endl;
    out << "B200 Bread 5 3.25" << endl;
    out << "C300 Cereal 8 4.75" << endl;

    out.close();
}

void testValidation() {
    assert(isValidQuantity(0));
    assert(isValidQuantity(10));
    assert(!isValidQuantity(-1));

    assert(isValidPrice(0.0));
    assert(isValidPrice(1.50));
    assert(!isValidPrice(-0.01));
}

void testCalculateItemValue() {
    InventoryItem item = {"A100", "Apples", 10, 1.50};

    assert(nearlyEqual(calculateItemValue(item), 15.0));

    InventoryItem invalidQuantity = {"X", "Bad", -1, 1.50};
    InventoryItem invalidPrice = {"Y", "Bad", 1, -1.50};

    assert(nearlyEqual(calculateItemValue(invalidQuantity), 0.0));
    assert(nearlyEqual(calculateItemValue(invalidPrice), 0.0));
}

void testReadInventoryFile() {
    string filename = "test_inventory_input.txt";
    createTestInventoryFile(filename);

    InventoryItem items[10];
    int count = readInventoryFile(filename, items, 10);

    assert(count == 3);

    assert(items[0].sku == "A100");
    assert(items[0].name == "Apples");
    assert(items[0].quantity == 10);
    assert(nearlyEqual(items[0].price, 1.50));

    assert(items[2].sku == "C300");
    assert(items[2].name == "Cereal");
    assert(items[2].quantity == 8);
    assert(nearlyEqual(items[2].price, 4.75));
}

void testReadInventoryFileMaxItems() {
    string filename = "test_inventory_limited.txt";
    createTestInventoryFile(filename);

    InventoryItem items[2];
    int count = readInventoryFile(filename, items, 2);

    assert(count == 2);
    assert(items[0].sku == "A100");
    assert(items[1].sku == "B200");
}

void testReadMissingFile() {
    InventoryItem items[10];
    int count = readInventoryFile("missing_file.txt", items, 10);

    assert(count == 0);
}

void testCalculateTotalInventoryValue() {
    InventoryItem items[] = {
        {"A100", "Apples", 10, 1.50},
        {"B200", "Bread", 5, 3.25},
        {"C300", "Cereal", 8, 4.75}
    };

    assert(nearlyEqual(calculateTotalInventoryValue(items, 3), 69.25));
    assert(nearlyEqual(calculateTotalInventoryValue(nullptr, 3), 0.0));
    assert(nearlyEqual(calculateTotalInventoryValue(items, 0), 0.0));
}

void testFindItemBySku() {
    InventoryItem items[] = {
        {"A100", "Apples", 10, 1.50},
        {"B200", "Bread", 5, 3.25},
        {"C300", "Cereal", 8, 4.75}
    };

    assert(findItemBySku(items, 3, "A100") == 0);
    assert(findItemBySku(items, 3, "B200") == 1);
    assert(findItemBySku(items, 3, "Z999") == -1);
    assert(findItemBySku(nullptr, 3, "A100") == -1);
}

void testFindHighestValueItemIndex() {
    InventoryItem items[] = {
        {"A100", "Apples", 10, 1.50},
        {"B200", "Bread", 5, 3.25},
        {"C300", "Cereal", 8, 4.75}
    };

    assert(findHighestValueItemIndex(items, 3) == 2);
    assert(findHighestValueItemIndex(nullptr, 3) == -1);
    assert(findHighestValueItemIndex(items, 0) == -1);
}

void testWriteInventoryReport() {
    InventoryItem items[] = {
        {"A100", "Apples", 10, 1.50},
        {"B200", "Bread", 5, 3.25}
    };

    string filename = "test_inventory_report_output.txt";
    bool success = writeInventoryReport(filename, items, 2);

    assert(success);

    ifstream in(filename);
    assert(in.is_open());

    string contents;
    string line;

    while (getline(in, line)) {
        contents += line + "\n";
    }

    assert(contents.find("A100") != string::npos);
    assert(contents.find("Apples") != string::npos);
    assert(contents.find("Total inventory value") != string::npos);
}

int main() {
    testValidation();
    testCalculateItemValue();
    testReadInventoryFile();
    testReadInventoryFileMaxItems();
    testReadMissingFile();
    testCalculateTotalInventoryValue();
    testFindItemBySku();
    testFindHighestValueItemIndex();
    testWriteInventoryReport();

    cout << "All Lab 7.2 file-based inventory report tests passed!" << endl;
    return 0;
}
