Program to analyze the following [dataset](https://www.kaggle.com/datasets/zubairatha/revving-up-telangana-vehicle-sales-2023?select=telangana_vehicle_sales.csv). 
The output should show a distribution/count of cars by category (transport or non-transport), company, fuel type.
===============================

# Project layout
```
├── CMakeLists.txt
├── README.md
├── include      # Header files
│   └── carsds.h
├── src          # Source files
│   └── carsds.cpp
|-- resources    # Data files
├── tests        # Various tests
│   ├── integration
│   ├── performance
│   └── unit
├── conanfile.py # Conan package manager file
```

# Requirements
- CMake >=3.23
- Conan 2.x
- C++17 compatible compiler (with Parallel STL support)
  - I've tried to build it on MacOS with AppleClang 15.0.0 and it failed due to lack of Parallel STL support
- git-lfs (to download large files)

# Due to dependencies are managed by Conan, you need to install it first (or install them manually)
```bash
pip install -r requirements.txt
```

# Detect compiler [optional]
```bash
conan profile detect
```

# Build
- release is used due to in debug everything is slow
  - due to that large datasets tests are disabled in debug
```bash
conan install . --build=missing
cmake --preset conan-release
cmake --build --preset conan-release
```

# Run tests
```bash
ctest --preset conan-release
```

# Run the program
```bash
carsds_cli <seq|par> <path/to/dataset>
```

# Local execution [results](RESULTS.md)


>📝
> Based on the template https://github.com/edu-one/cpptest
