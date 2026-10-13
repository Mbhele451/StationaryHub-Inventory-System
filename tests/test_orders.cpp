#include <cassert>

#include "system/Order.h"
#include "system/OrderItem.h"

int main() {
    Order order(101, 1);
    order.addItem(OrderItem(10, 5));
    order.addItem(OrderItem(11, 3));

    assert(order.getOrderID() == 101);
    assert(order.getWarehouseID() == 1);
    assert(order.getItems().size() == 2);
    assert(order.getItems()[0].getProductID() == 10);
    assert(order.getItems()[1].getQuantity() == 3);
    return 0;
}
