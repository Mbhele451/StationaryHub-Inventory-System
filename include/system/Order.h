#pragma once

#include <vector>

#include "system/OrderItem.h"

class Order {
    int orderID_;
    int warehouseID_;
    std::vector<OrderItem> items_;

public:
    Order(int orderID, int warehouseID);

    void addItem(const OrderItem& item);

    int getOrderID() const;
    int getWarehouseID() const;
    const std::vector<OrderItem>& getItems() const;

    void displayOrder() const;
};
