#include "app/app_config.hpp"
#include "app/weather_controller.hpp"
#include "core/wttr_weather_provider.hpp"
#include "ui/weather_widget.hpp"

#include <QApplication>
#include <memory>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    weather::AppConfig config;
    config.city = QStringLiteral("Moscow");

    auto* widget = new weather::WeatherWidget();
    widget->resize(config.windowSize);
    widget->show();

    auto provider = std::make_unique<weather::WttrWeatherProvider>();
    auto* controller = new weather::WeatherController(std::move(provider), config, &app);

    QObject::connect(controller, &weather::WeatherController::weatherUpdated, widget, &weather::WeatherWidget::showWeather);
    QObject::connect(controller, &weather::WeatherController::fetchFailed, widget, &weather::WeatherWidget::showError);

    controller->start();

    return app.exec();
}
