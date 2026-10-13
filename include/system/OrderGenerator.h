#pragma once

#include <string>
#include <vector>

#include "system/Order.h"

class OrderGenerator {
public:
    static std::vector<Order> loadOrders(const std::string& filename);
};
