#pragma once

#include "../core/iweather_provider.hpp"
#include "../core/weather_data.hpp"
#include "app_config.hpp"

#include <QObject>
#include <QTimer>
#include <memory>

namespace weather {

class WeatherController final : public QObject {
    Q_OBJECT

public:
    explicit WeatherController(
        std::unique_ptr<IWeatherProvider> provider,
        AppConfig config,
        QObject* parent = nullptr);

    void start();
    void refresh();

signals:
    void weatherUpdated(const weather::WeatherData& data);
    void fetchFailed(const QString& message);

private:
    std::unique_ptr<IWeatherProvider> provider_;
    AppConfig config_;
    QTimer refreshTimer_;
};

} // namespace weather
