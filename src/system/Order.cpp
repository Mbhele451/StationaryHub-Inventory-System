#include "system/Order.h"

#include <iostream>

Order::Order(int orderID, int warehouseID)
    : orderID_(orderID), warehouseID_(warehouseID) {}

void Order::addItem(const OrderItem& item) { items_.push_back(item); }

int Order::getOrderID() const { return orderID_; }
int Order::getWarehouseID() const { return warehouseID_; }
const std::vector<OrderItem>& Order::getItems() const { return items_; }

void Order::displayOrder() const {
    std::cout << "\nOrder ID: " << orderID_
              << " | Warehouse ID: " << warehouseID_ << "\n";
    if (items_.empty()) {
        std::cout << "No items in this order.\n";
        return;
    }
    for (const auto& item : items_)
        std::cout << "Product ID: " << item.getProductID()
                  << " | Quantity: " << item.getQuantity() << "\n";
}
