#pragma once

#include <QLabel>
#include <QPoint>
#include <QWidget>

#include "../core/weather_data.hpp"
#include "weather_animation_widget.hpp"
#include "../app/city_manager.hpp"

namespace weather {

class WeatherWidget final : public QWidget {
  Q_OBJECT

 public:
  explicit WeatherWidget(QWidget *parent = nullptr);

  void showWeather(const WeatherData &data);
  void showError(const QString &message);

 protected:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;

 signals:
  void cityChanged(const QString &newCity);

 private:
  void updateDetails(const WeatherData &data);

  WeatherAnimationWidget *animationWidget_ = nullptr;
  CityManager cityManager_;

  QLabel *cityLabel_ = nullptr;
  QLabel *temperatureLabel_ = nullptr;
  QLabel *descriptionLabel_ = nullptr;
  QLabel *detailsLabel_ = nullptr;
  QPoint dragOffset_;
};

}  // namespace weather
