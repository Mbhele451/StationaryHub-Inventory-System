#include <cassert>

#include "domain/Warehouse.h"
#include "domain/TaxableProduct.h"

int main() {
    Warehouse wh(1, "Test Warehouse");
    auto product = std::make_shared<TaxableProduct>(10, "Widget", 100.0, 0.15);

    wh.addProduct(product, 10);
    assert(wh.decreaseStock(10, 3));
    assert(!wh.decreaseStock(10, 20));
    return 0;
}
