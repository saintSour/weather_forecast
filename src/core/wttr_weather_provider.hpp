#pragma once

#include "iweather_provider.hpp"

namespace weather {

class WttrWeatherProvider final : public IWeatherProvider {
 public:
  WeatherData fetch(const QString &city) override;
};

}  // namespace weather
