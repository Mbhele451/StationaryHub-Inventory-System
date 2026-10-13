#pragma once

#include <memory>
#include <mutex>
#include <vector>

#include "domain/Warehouse.h"
#include "system/Order.h"

class InventoryManagementSystem {
    std::vector<std::shared_ptr<Warehouse>> warehouses_;
    mutable std::mutex systemMutex_;
    mutable std::mutex consoleMutex_;

public:
    void addWarehouse(std::shared_ptr<Warehouse> warehouse);
    void removeWarehouse(int id);
    std::shared_ptr<Warehouse> findWarehouse(int id);
    void displayAllWarehouses() const;
    void processOrders(const std::vector<Order>& orders);
};
