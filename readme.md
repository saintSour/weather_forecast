# Weather Forecast CLI 🌤️

A lightweight and fast desktop widget-application written in C++ that fetches and displays real-time weather forecasts using an external API.

## Features

- **Real-time Data**: Current temperature, humidity, wind speed, and weather conditions.
- **Location Search**: Get weather updates by city name or ZIP code.
<!-- **Clean Output**: Beautifully formatted terminal output (supports custom `clang-format` styling). -->
- **Efficient Memory Management**: Custom optimized vector implementation under the hood.

## Prerequisites

Before building the project, ensure you have the following installed:
- CMake (version 3.16 or higher)
- A C++17 compiler (GCC, Clang, or MSVC)
- QT6 Library
- CPR Library
<!-- [Optional] `clang-format` for code style enforcement -->

## Installation & Build

1. Clone the repository:
   ```bash
   git clone https://github.com
   cd weather_forecast
   ```

2. Build the project using CMake:
   ```bash
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```
   Or you can use autobuild script:
   ```bash
   chmod +x autobuild.sh
   ./autobuild.sh
   ```

## Usage

Run the executable from your terminal by passing a city name as an argument:

```bash
./weather_forecast
```

<!-- ### Options:
- `-c, --city <name>` : Specify the target city.
- `-h, --help`        : Show the help menu.
- `-u, --units <m/i>` : Switch between Metric (Celsius) and Imperial (Fahrenheit). 

## Development

### Code Formatting
This project uses `clang-format` to maintain a consistent code style. To format your code before committing, run:

```bash
clang-format -i -style=file src/*.cpp include/*.hpp -->
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
