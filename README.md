program to analyze the following dataset. 
 
https://www.kaggle.com/datasets/zubairatha/revving-up-telangana-vehicle-sales-2023?select=telangana_vehicle_sales.csv
 
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

# Due to dependencies are managed by Conan, you need to install it first
```bash
pip install -r requirements.txt
```

# Build
```bash
conan install . --build=missing
cmake --preset conan-debug
cmake --build --preset conan-debug
```

# Run tests
```bash
ctest --preset conan-debug
```


>📝
> Based on the template https://github.com/edu-one/cpptest
