#include "system/OrderGenerator.h"

#include <fstream>
#include <iostream>
#include <sstream>

std::vector<Order> OrderGenerator::loadOrders(const std::string& filename) {
    std::vector<Order> orders;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open orders file: " << filename << "\n";
        return orders;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        int orderID, warehouseID;
        iss >> orderID >> warehouseID;

        Order order(orderID, warehouseID);
        int productID, quantity;
        while (iss >> productID >> quantity) {
            order.addItem(OrderItem(productID, quantity));
        }
        orders.push_back(order);
    }

    return orders;
}
