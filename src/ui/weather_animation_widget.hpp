#pragma once

#include <QColor>
#include <QTimer>
#include <QWidget>
#include <vector>

#include "../core/weather_condition.hpp"

namespace weather {

class WeatherAnimationWidget final : public QWidget {
  Q_OBJECT

 public:
  explicit WeatherAnimationWidget(QWidget *parent = nullptr);

  void setCondition(WeatherCondition condition);

 protected:
  void paintEvent(QPaintEvent *event) override;
  void resizeEvent(QResizeEvent *event) override;

 private:
  struct Particle {
    float x = 0.0F;
    float y = 0.0F;
    float speed = 0.0F;
    float size = 0.0F;
    float drift = 0.0F;
  };

  struct Cloud {
    float x = 0.0F;
    float y = 0.0F;
    float width = 0.0F;
    float height = 0.0F;
    float speed = 0.0F;
    float opacity = 0.0F;
  };

  void initializeScene();
  void tick();
  void drawBackground(QPainter &painter);
  void drawSun(QPainter &painter);
  void drawClouds(QPainter &painter);
  void drawPrecipitation(QPainter &painter);
  void drawFog(QPainter &painter);
  void drawLightning(QPainter &painter);
  QColor skyColor() const;

  WeatherCondition condition_ = WeatherCondition::Unknown;
  QTimer animationTimer_;
  float animationPhase_ = 0.0F;
  float lightningFlash_ = 0.0F;
  std::vector<Particle> particles_;
  std::vector<Cloud> clouds_;
};

}  // namespace weather
