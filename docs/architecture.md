# StationaryHub Inventory System

This repository has been reorganized into a layered C++ project structure to separate domain logic, system orchestration, app entry point, and test data.

## Layout

- `include/domain/` — product and warehouse abstractions
- `include/system/` — order and inventory management logic
- `include/app/` — UI-related declarations
- `src/domain/` — domain implementation files
- `src/system/` — system implementation files
- `src/app/` — application entry point
- `data/` — runtime input files
- `tests/` — future automated tests

## Build

```bash
cmake -S . -B build
cmake --build build
./build/bin/StationaryHub
```
