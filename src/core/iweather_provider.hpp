#pragma once

#include <QString>

#include "weather_data.hpp"

namespace weather {

class IWeatherProvider {
 public:
  virtual ~IWeatherProvider() = default;

  virtual WeatherData fetch(const QString &city) = 0;
};

}  // namespace weather
