#include "weather_widget.hpp"

#include <QFrame>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QComboBox>

namespace weather {

WeatherWidget::WeatherWidget(QWidget* parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);

    animationWidget_ = new WeatherAnimationWidget(this);
    animationWidget_->setFixedHeight(150);

    cityLabel_ = new QLabel(this);
    temperatureLabel_ = new QLabel(this);
    descriptionLabel_ = new QLabel(this);
    detailsLabel_ = new QLabel(this);

    cityLabel_->setStyleSheet("color: rgba(255,255,255,220); font-size: 13px; font-weight: 600;");
    temperatureLabel_->setStyleSheet("color: white; font-size: 34px; font-weight: 700;");
    descriptionLabel_->setStyleSheet("color: rgba(255,255,255,230); font-size: 14px;");
    detailsLabel_->setStyleSheet("color: rgba(255,255,255,180); font-size: 12px;");

    // 1. Создаем выпадающее меню (QComboBox) для выбора городов
    QComboBox* cityComboBox = new QComboBox(this);
    cityComboBox->addItems({ "Москва", "Санкт-Петербург", "Новосибирск", "Екатеринбург" });
    cityComboBox->setFixedWidth(130); // Задаем оптимальную ширину
    
    // Стилизуем меню под дизайн вашей темной полупрозрачной карточки
    cityComboBox->setStyleSheet(
        "QComboBox {"
        "   background: rgba(255, 255, 255, 20);" // Полупрозрачный фон
        "   color: white;"
        "   border: 1px solid rgba(255, 255, 255, 40);"
        "   border-radius: 6px;"
        "   padding: 2px 25px 2px 8px;"
        "   font-size: 12px;"
        "}"
        "QComboBox:hover {"
        "   background: rgba(255, 255, 255, 35);"
        "}"
        "QComboBox::drop-down {"
        "   subcontrol-origin: padding;"
        "   subcontrol-position: top right;"
        "   width: 20px;"
        "   border-left: none;"
        "}"
        "QComboBox QAbstractItemView {" // Стилизация выпадающего списка
        "   background-color: #141820;"
        "   color: white;"
        "   selection-background-color: #ff4d4d;" // Выделение в цвет кнопки
        "   border: 1px solid rgba(255, 255, 255, 40);"
        "   border-radius: 6px;"
        "}"
    );

    connect(cityComboBox, &QComboBox::currentTextChanged, this, &WeatherWidget::cityChanged);

    QPushButton* closeButton = new QPushButton(this);
    closeButton->setFixedSize(24, 24);
    closeButton->setStyleSheet(
            "QPushButton {"
            "   background-color: #ff4d4d;" // Красный цвет
            "   color: white;"              // Белый текст/крестик
            "   border: none;"              // Без рамки
            "   border-radius: 12px;"       // Скругление (12px = половина размера, выйдет круг)
            "   font-weight: bold;"
            "}"
            "QPushButton:hover {"
            "   background-color: #ff3333;" // Темнеет при наведении
            "}"
    );
    connect(closeButton, &QPushButton::clicked, this, &QWidget::close);
    
    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->addWidget(cityComboBox);
    topLayout->addStretch();
    topLayout->addWidget(closeButton);

    // 3. Создаем карточку-фон
    auto* card = new QFrame(this);
    card->setObjectName("weatherCard");
    card->setStyleSheet(
        "#weatherCard {"
        "  background: rgba(20, 24, 32, 170);"
        "  border-radius: 16px;"
        "}");

    auto* cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(14, 14, 14, 14);
    cardLayout->setSpacing(6);
    
    cardLayout->addLayout(topLayout);
    cardLayout->addWidget(animationWidget_);
    cardLayout->addWidget(cityLabel_);
    cardLayout->addWidget(temperatureLabel_);
    cardLayout->addWidget(descriptionLabel_);
    cardLayout->addWidget(detailsLabel_);

    auto* rootLayout = new QVBoxLayout(this);
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->addWidget(card);

    showError(QStringLiteral("Загрузка..."));
}

void WeatherWidget::showWeather(const WeatherData& data)
{
    animationWidget_->setCondition(data.condition);
    updateDetails(data);
}

void WeatherWidget::showError(const QString& message)
{
    animationWidget_->setCondition(WeatherCondition::Unknown);
    cityLabel_->setText(QStringLiteral("Погода"));
    temperatureLabel_->setText(QStringLiteral("—"));
    descriptionLabel_->setText(message);
    detailsLabel_->clear();
}

void WeatherWidget::updateDetails(const WeatherData& data)
{
    cityLabel_->setText(data.city);
    temperatureLabel_->setText(QStringLiteral("%1°").arg(qRound(data.temperatureC)));
    descriptionLabel_->setText(data.description.isEmpty() ? conditionLabel(data.condition) : data.description);

    QStringList details;
    if (data.humidity >= 0)
        details << QStringLiteral("Влажность: %1%").arg(data.humidity);
    if (!data.wind.isEmpty())
        details << QStringLiteral("Ветер: %1").arg(data.wind);

    detailsLabel_->setText(details.join(QStringLiteral("  •  ")));
}

void WeatherWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
        dragOffset_ = event->globalPosition().toPoint() - frameGeometry().topLeft();
}

void WeatherWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
        move(event->globalPosition().toPoint() - dragOffset_);
}

} // namespace weather
