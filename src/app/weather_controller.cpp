#include "weather_controller.hpp"

namespace weather {

WeatherController::WeatherController(std::unique_ptr<IWeatherProvider> provider,
                                     AppConfig config, QObject *parent)

    : QObject(parent),
      provider_(std::move(provider)),
      config_(std::move(config)) {
  connect(&refreshTimer_, &QTimer::timeout, this, &WeatherController::refresh);
}

void WeatherController::start() {
  refresh();
  refreshTimer_.start(config_.refreshIntervalMs);
}

void WeatherController::refresh() {
  const WeatherData data = provider_->fetch(config_.city);

  if (data.valid)
    emit weatherUpdated(data);
  else
    emit fetchFailed(data.errorMessage);
}

void WeatherController::changeCity(const QString &newCity) {
  config_.city = newCity;
  start();
}

}  // namespace weather
