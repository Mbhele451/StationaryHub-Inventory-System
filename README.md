# StationaryHub — Multi-Threaded Real-Time Inventory & Trading System

> **COMP315 Semester Project | 2026**  
> University of KwaZulu-Natal

---

## Table of Contents

- [Project Overview](#project-overview)
- [Team Members](#team-members)
- [System Architecture](#system-architecture)
- [Features](#features)
- [Class Structure](#class-structure)
- [Technologies Used](#technologies-used)
- [Getting Started](#getting-started)
- [How to Run](#how-to-run)
- [Menu Options](#menu-options)
- [Orders File Format](#orders-file-format)
- [Concurrency Design](#concurrency-design)
- [Memory Management](#memory-management)
- [Project Structure](#project-structure)

---

## Project Overview

StationaryHub is a console-based **multi-threaded inventory and trading system** written in C++. It simulates a real-world stationery supply chain across **nine South African province-based warehouses**, each managing its own product stock. The system processes customer orders **concurrently using std::thread**, with full mutex synchronization to prevent race conditions and ensure stock integrity under simultaneous load.

The project demonstrates:
- **Object-Oriented Programming** through a polymorphic product hierarchy
- **STL containers and algorithms** including `std::map`, `std::vector`, `std::sort`, and `std::find_if`
- **Thread-safe concurrency** using `std::mutex` and `std::lock_guard`
- **Smart pointer memory management** with `std::shared_ptr` throughout

---

## Team Members

| Name | Role |
| :--- | :--- |
| Bandile Mhlambu | Project Manager & Concurrency Lead |
| Sbonelo Ntshangase | STL & Data Structures |
| Lerato Mbhele | Core Software, UI Design & Memory Management |
| Bongani Ntshumayelo | Core Software Implementation |
| Lindokuhle Machangu | Unit Testing & Logic Implementation |
| Andile Mthembu | Documentation & Report Lead |
| Sthembiso Mchunu | Class & System Architecture Design |

---

## System Architecture

The system is structured in six distinct layers, with communication flowing strictly downward:

```
┌─────────────────────────────────────────┐
│          CLI / main.cpp                 │  ← User Interface Layer
├─────────────────────────────────────────┤
│     InventoryManagementSystem           │  ← Manager Layer
├─────────────────────────────────────────┤
│         Warehouse (×9)                  │  ← Warehouse Layer
├─────────────────────────────────────────┤
│  Product / TaxableProduct               │
│  DiscountProduct / BulkProduct          │  ← Domain Layer
├─────────────────────────────────────────┤
│      Order / OrderItem                  │  ← Concurrency Layer
├─────────────────────────────────────────┤
│          orders.txt                     │  ← Persistence Layer
└─────────────────────────────────────────┘
```

---

## Features

### Warehouse Operations
- Add a new warehouse with a unique ID and province name
- Remove an existing warehouse by ID
- Display all warehouses in the system

### Product Operations
- Add a product to a warehouse (Taxable, Discount, or Bulk type)
- Remove a product from a warehouse by product ID
- Search for a product within a warehouse by ID
- Display all products in a warehouse (sorted by product ID via `std::map`)
- Sort products by **price** or **quantity** using `std::sort`

### Order Processing
- Load orders from `orders.txt` at runtime
- Process **25 concurrent orders** using `std::thread`
- Fulfil orders by safely reducing stock with mutex protection
- Reject orders with `FAILED` status when stock is insufficient
- Display thread ID, product ordered, warehouse, and outcome for every order

---

## Class Structure

```
Product  (abstract base class)
│   - productID, name, basePrice
│   - calculateFinalPrice() [pure virtual]
│   - display()
│
├── TaxableProduct
│       - taxRate
│       - calculateFinalPrice(): price × qty × (1 + taxRate)
│
├── DiscountProduct
│       - discountRate
│       - calculateFinalPrice(): price × qty × (1 − discountRate)
│
└── BulkProduct
        - threshold, bulkDiscount
        - calculateFinalPrice(): applies discount if qty >= threshold

Warehouse
    - warehouseID, location
    - std::map<int, StockItem> inventory
    - std::mutex inventoryMutex
    - addProduct(), removeProduct(), decreaseStock()
    - displayAllProducts(), searchProduct(), sortAndDisplay()

InventoryManagementSystem
    - std::vector<shared_ptr<Warehouse>> warehouses_
    - std::mutex systemMutex_
    - addWarehouse(), removeWarehouse(), findWarehouse()
    - displayAllWarehouses(), processOrders()

Order
    - orderID, warehouseID
    - std::vector<OrderItem> items_

OrderItem
    - productID, quantity
```

---

## Technologies Used

| Technology | Purpose |
|-----------|---------|
| C++17 | Core programming language |
| `std::thread` | Concurrent order processing |
| `std::mutex` / `std::lock_guard` | Thread synchronization |
| `std::shared_ptr` | Smart pointer memory management |
| `std::map` | Product inventory storage per warehouse |
| `std::vector` | Warehouse collection storage |
| `std::sort` | Sorting products by price or quantity |
| `std::find_if` | Warehouse lookup by ID |
| Code::Blocks | IDE (GNU GCC Compiler) |

---

## Getting Started

### Prerequisites

- **GNU GCC Compiler** (g++ with C++17 support)
- **Code::Blocks IDE** (recommended) or any C++17-compatible compiler
- Windows, Linux, or macOS

### Cloning the Repository

```bash
git clone https://github.com/YOUR-USERNAME/StationaryHub-Inventory-System.git
cd StationaryHub-Inventory-System
```

---

## How to Run

### Option A — Using Code::Blocks

1. Open `StationaryHub.cbp` in Code::Blocks
2. Click **Build → Build and Run** (or press `F9`)
3. Ensure `orders.txt` is in the **same directory as the executable**

### Option B — Using the Terminal (g++)

```bash
g++ -std=c++17 -pthread -o StationaryHub \
    Main.cpp \
    Product.cpp \
    TaxableProduct.cpp \
    DiscountProduct.cpp \
    BulkProduct.cpp \
    Warehouse.cpp \
    InventoryManagementSystem.cpp \
    Order.cpp \
    OrderItem.cpp \
    OrderGenerator.cpp

./StationaryHub
```

> **Note:** The `-pthread` flag is required for `std::thread` on Linux/macOS.

---

## Menu Options

```
*****************************************
*   INVENTORY MANAGEMENT SYSTEM MENU   *
*****************************************
*  --- Warehouse Operations ---        *
*  1.  Add warehouse                   *
*  2.  Remove warehouse                *
*  3.  Display all warehouses          *
*  --- Product Operations ---          *
*  4.  Add product to warehouse        *
*  5.  Remove product from warehouse   *
*  6.  Search product in warehouse     *
*  7.  Process Orders (Multi-thread)   *
*  8.  Display all products            *
*  9.  Sort products by price/qty      *
*  0.  Exit                            *
*****************************************
```

---

## Orders File Format

Each line in `orders.txt` follows this format:

```
orderID warehouseID productID quantity [productID quantity ...]
```

**Example:**
```
1 1 101 5 102 3       ← Order 1, Warehouse 1, buy 5x product 101 and 3x product 102
2 1 101 8             ← Order 2, Warehouse 1, buy 8x product 101
10 5 112 999          ← Order 10, Warehouse 5, request 999x product 112 (will FAIL)
```

The test file includes **25 orders** covering:
- Standard successful fulfilment
- Deliberate `FAILED` orders (quantity exceeds stock)
- Race conditions (multiple threads targeting the same product)
- Multi-item orders (multiple products per order)

---

## Concurrency Design

When option `7` is selected, the system:

1. Reads all orders from `orders.txt` via `OrderGenerator::loadOrders()`
2. Spawns **one `std::thread` per order** — all threads run simultaneously
3. Each thread calls `warehouse->decreaseStock()` which:
   - Acquires `inventoryMutex` via `std::lock_guard`
   - Checks product existence and stock level
   - Deducts stock atomically if sufficient, or rejects the order
   - Releases the lock automatically when the guard goes out of scope
4. A second `consoleMutex` protects `std::cout` so output is not scrambled
5. The main thread calls `join()` on all threads before returning

This design guarantees:
- ✅ No race conditions
- ✅ No deadlocks
- ✅ Stock never goes negative
- ✅ Visible interleaved thread output confirming concurrent execution

---

## Memory Management

The system uses **zero raw pointers**. All dynamic objects are managed through `std::shared_ptr`:

| Object | Pointer Type | Reason |
|--------|-------------|--------|
| `Product` (and derived) | `shared_ptr<Product>` | Shared between warehouse inventory and order processing |
| `Warehouse` | `shared_ptr<Warehouse>` | Contains a `std::mutex` — cannot be copied, must be shared |
| `Order` | `shared_ptr<Order>` | Accessed by multiple threads simultaneously |

When `main()` exits, all `shared_ptr` reference counts reach zero and every object is destroyed automatically — no memory leaks.

---

## Project Structure

```
StationaryHub-Inventory-System/
│
├── Main.cpp
├── Product.h / Product.cpp
├── TaxableProduct.h / TaxableProduct.cpp
├── DiscountProduct.h / DiscountProduct.cpp
├── BulkProduct.h / BulkProduct.cpp
├── Warehouse.h / Warehouse.cpp
├── InventoryManagementSystem.h / InventoryManagementSystem.cpp
├── Order.h / Order.cpp
├── OrderItem.h / OrderItem.cpp
├── OrderGenerator.h / OrderGenerator.cpp
├── orders.txt
├── .gitignore
└── README.md
```
## Sample Output
Processing orders from file: orders.txt

Processing Order ID: 1 | Thread ID: 8670141377090704656 at Warehouse Gauteng
  [SUCCESS] Product ID: 101 | Qty: 5
  [SUCCESS] Product ID: 102 | Qty: 3

Processing Order ID: 2 | Thread ID: 18137369640724998020 at Warehouse Gauteng
  [SUCCESS] Product ID: 101 | Qty: 8
  [SUCCESS] Product ID: 103 | Qty: 10

Processing Order ID: 3 | Thread ID: 1230235464250880600 at Warehouse Western Cape
  [SUCCESS] Product ID: 104 | Qty: 5
  [SUCCESS] Product ID: 105 | Qty: 2
  
Processing Order ID: 14 | Thread ID: 17519169083552770373 at Warehouse Mpumalanga
  [FAILED]  Product ID: 115 | Qty: 999 (Insufficient stock or missing)

Processing Order ID: 15 | Thread ID: 7878728155988826942 at Warehouse North West
  [FAILED]  Product ID: 101 | Qty: 10 (Insufficient stock or missing)
  [SUCCESS] Product ID: 102 | Qty: 20

Processing Order ID: 17 | Thread ID: 12034445389369918683 at Warehouse Northern Cape
  [SUCCESS] Product ID: 107 | Qty: 5
  [SUCCESS] Product ID: 109 | Qty: 80

Processing Order ID: 18 | Thread ID: 3834309123136518406 at Warehouse Northern Cape
  [FAILED]  Product ID: 107 | Qty: 999 (Insufficient stock or missing)
  
Orders processed successfully!
---

> COMP315 — University of KwaZulu-Natal | 2026
