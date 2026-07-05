#pragma once

#include <QString>

#include "weather_condition.hpp"

namespace weather {

struct WeatherData {
  QString city;
  double temperatureC = 0.0;
  WeatherCondition condition = WeatherCondition::Unknown;
  QString description;
  int humidity = -1;
  QString wind;
  bool valid = false;
  QString errorMessage;
};

}  // namespace weather
