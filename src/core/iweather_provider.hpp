#pragma once

#include "weather_data.hpp"

#include <QString>

namespace weather {

class IWeatherProvider {
public:
    virtual ~IWeatherProvider() = default;

    virtual WeatherData fetch(const QString& city) = 0;
};

} // namespace weather
