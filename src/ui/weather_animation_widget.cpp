#include "weather_animation_widget.hpp"

#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>
#include <QRandomGenerator>
#include <QResizeEvent>
#include <QtMath>

namespace weather {

namespace {

float randomRange(float min, float max)
{
    return min + QRandomGenerator::global()->generateDouble() * (max - min);
}

} // namespace

WeatherAnimationWidget::WeatherAnimationWidget(QWidget* parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_OpaquePaintEvent);
    connect(&animationTimer_, &QTimer::timeout, this, &WeatherAnimationWidget::tick);
    animationTimer_.start(33);
}

void WeatherAnimationWidget::setCondition(WeatherCondition condition)
{
    condition_ = condition;
    initializeScene();
    update();
}

void WeatherAnimationWidget::initializeScene()
{
    particles_.clear();
    clouds_.clear();
    lightningFlash_ = 0.0F;

    const int width = qMax(1, this->width());
    const int height = qMax(1, this->height());

    switch (condition_)
    {
    case WeatherCondition::Rain:
    case WeatherCondition::Thunderstorm:
        particles_.resize(80);
        for (auto& particle : particles_)
        {
            particle.x = randomRange(0.0F, static_cast<float>(width));
            particle.y = randomRange(0.0F, static_cast<float>(height));
            particle.speed = randomRange(6.0F, 12.0F);
            particle.size = randomRange(1.0F, 2.5F);
            particle.drift = randomRange(-0.5F, 0.5F);
        }
        break;

    case WeatherCondition::Snow:
        particles_.resize(60);
        for (auto& particle : particles_)
        {
            particle.x = randomRange(0.0F, static_cast<float>(width));
            particle.y = randomRange(0.0F, static_cast<float>(height));
            particle.speed = randomRange(0.8F, 2.2F);
            particle.size = randomRange(2.0F, 5.0F);
            particle.drift = randomRange(-0.8F, 0.8F);
        }
        break;

    case WeatherCondition::Cloudy:
    case WeatherCondition::PartlyCloudy:
    case WeatherCondition::Fog:
    case WeatherCondition::Unknown:
        clouds_.resize(
            condition_ == WeatherCondition::PartlyCloudy || condition_ == WeatherCondition::Unknown ? 2 : 4);
        for (auto& cloud : clouds_)
        {
            cloud.x = randomRange(0.0F, static_cast<float>(width));
            cloud.y = randomRange(10.0F, static_cast<float>(height) * 0.45F);
            cloud.width = randomRange(70.0F, 120.0F);
            cloud.height = randomRange(24.0F, 42.0F);
            cloud.speed = randomRange(0.15F, 0.45F);
            cloud.opacity = randomRange(0.35F, 0.75F);
        }
        break;

    default:
        break;
    }
}

void WeatherAnimationWidget::tick()
{
    animationPhase_ += 0.03F;

    const float width = static_cast<float>(this->width());
    const float height = static_cast<float>(this->height());

    for (auto& particle : particles_)
    {
        particle.y += particle.speed;
        particle.x += particle.drift;

        if (particle.y > height)
        {
            particle.y = -particle.size;
            particle.x = randomRange(0.0F, width);
        }

        if (particle.x < 0.0F)
            particle.x = width;
        if (particle.x > width)
            particle.x = 0.0F;
    }

    for (auto& cloud : clouds_)
    {
        cloud.x += cloud.speed;
        if (cloud.x > width + cloud.width)
            cloud.x = -cloud.width;
    }

    if (condition_ == WeatherCondition::Thunderstorm && QRandomGenerator::global()->bounded(180) == 0)
        lightningFlash_ = 1.0F;

    if (lightningFlash_ > 0.0F)
        lightningFlash_ = qMax(0.0F, lightningFlash_ - 0.12F);

    update();
}

void WeatherAnimationWidget::paintEvent(QPaintEvent* /*event*/)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    drawBackground(painter);

    switch (condition_)
    {
    case WeatherCondition::Sunny:
        drawSun(painter);
        break;
    case WeatherCondition::PartlyCloudy:
        drawSun(painter);
        drawClouds(painter);
        break;
    case WeatherCondition::Cloudy:
        drawClouds(painter);
        break;
    case WeatherCondition::Fog:
        drawClouds(painter);
        drawFog(painter);
        break;
    case WeatherCondition::Rain:
        drawClouds(painter);
        drawPrecipitation(painter);
        break;
    case WeatherCondition::Snow:
        drawClouds(painter);
        drawPrecipitation(painter);
        break;
    case WeatherCondition::Thunderstorm:
        drawClouds(painter);
        drawPrecipitation(painter);
        drawLightning(painter);
        break;
    case WeatherCondition::Unknown:
        drawSun(painter);
        drawClouds(painter);
        break;
    }
}

void WeatherAnimationWidget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    initializeScene();
}

QColor WeatherAnimationWidget::skyColor() const
{
    switch (condition_)
    {
    case WeatherCondition::Sunny:
        return QColor(74, 144, 226);
    case WeatherCondition::PartlyCloudy:
        return QColor(96, 146, 210);
    case WeatherCondition::Cloudy:
        return QColor(110, 124, 145);
    case WeatherCondition::Fog:
        return QColor(145, 155, 165);
    case WeatherCondition::Rain:
        return QColor(72, 92, 118);
    case WeatherCondition::Snow:
        return QColor(170, 188, 210);
    case WeatherCondition::Thunderstorm:
        return QColor(52, 62, 86);
    case WeatherCondition::Unknown:
        return QColor(90, 98, 112);
    }

    return QColor(90, 98, 112);
}

void WeatherAnimationWidget::drawBackground(QPainter& painter)
{
    QLinearGradient gradient(0, 0, 0, height());
    gradient.setColorAt(0.0, skyColor().lighter(115));
    gradient.setColorAt(1.0, skyColor().darker(110));
    painter.fillRect(rect(), gradient);
}

void WeatherAnimationWidget::drawSun(QPainter& painter)
{
    const QPointF center(width() * 0.78, height() * 0.24);
    const float pulse = 1.0F + 0.05F * qSin(animationPhase_);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255, 220, 120, 70));
    painter.drawEllipse(center, 34.0 * pulse, 34.0 * pulse);

    painter.setBrush(QColor(255, 236, 140));
    painter.drawEllipse(center, 22.0 * pulse, 22.0 * pulse);

    painter.setPen(QPen(QColor(255, 240, 170, 180), 3.0));
    for (int ray = 0; ray < 8; ++ray)
    {
        const float angle = animationPhase_ + ray * (M_PI / 4.0F);
        const QPointF start = center + QPointF(qCos(angle) * 28.0, qSin(angle) * 28.0);
        const QPointF end = center + QPointF(qCos(angle) * 38.0, qSin(angle) * 38.0);
        painter.drawLine(start, end);
    }
}

void WeatherAnimationWidget::drawClouds(QPainter& painter)
{
    painter.setPen(Qt::NoPen);

    for (const Cloud& cloud : clouds_)
    {
        painter.setBrush(QColor(255, 255, 255, static_cast<int>(cloud.opacity * 255.0F)));

        const QRectF base(cloud.x, cloud.y, cloud.width, cloud.height);
        painter.drawEllipse(base);
        painter.drawEllipse(base.translated(-cloud.width * 0.28, cloud.height * 0.18));
        painter.drawEllipse(base.translated(cloud.width * 0.28, cloud.height * 0.12));
    }
}

void WeatherAnimationWidget::drawPrecipitation(QPainter& painter)
{
    if (condition_ == WeatherCondition::Snow)
    {
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(255, 255, 255, 220));

        for (const Particle& particle : particles_)
            painter.drawEllipse(QPointF(particle.x, particle.y), particle.size, particle.size);

        return;
    }

    painter.setPen(QPen(QColor(180, 210, 255, 180), 1.5));

    for (const Particle& particle : particles_)
    {
        painter.drawLine(
            QPointF(particle.x, particle.y),
            QPointF(particle.x + particle.drift * 4.0F, particle.y + particle.size * 5.0F));
    }
}

void WeatherAnimationWidget::drawFog(QPainter& painter)
{
    painter.setBrush(QColor(255, 255, 255, 55));
    painter.setPen(Qt::NoPen);

    for (int layer = 0; layer < 3; ++layer)
    {
        const float y = height() * (0.45F + layer * 0.12F) + qSin(animationPhase_ + layer) * 6.0F;
        painter.drawRect(QRectF(-10.0, y, width() + 20.0, 28.0));
    }
}

void WeatherAnimationWidget::drawLightning(QPainter& painter)
{
    if (lightningFlash_ <= 0.0F)
        return;

    painter.fillRect(rect(), QColor(255, 255, 255, static_cast<int>(lightningFlash_ * 120.0F)));

    QPainterPath bolt;
    const float x = width() * 0.55F;
    bolt.moveTo(x, height() * 0.12F);
    bolt.lineTo(x - 8.0F, height() * 0.34F);
    bolt.lineTo(x + 4.0F, height() * 0.34F);
    bolt.lineTo(x - 6.0F, height() * 0.58F);

    painter.setPen(QPen(QColor(255, 245, 150), 3.0));
    painter.drawPath(bolt);
}

} // namespace weather
