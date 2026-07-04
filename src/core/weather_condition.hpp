#pragma once

#include <QString>

namespace weather {

enum class WeatherCondition {
    Unknown,
    Sunny,
    PartlyCloudy,
    Cloudy,
    Fog,
    Rain,
    Snow,
    Thunderstorm,
};

inline WeatherCondition conditionFromDescription(const QString& description)
{
    const QString text = description.toLower();

    // English
    if (text.contains("thunder"))
        return WeatherCondition::Thunderstorm;
    if (text.contains("snow") || text.contains("sleet") || text.contains("blizzard"))
        return WeatherCondition::Snow;
    if (text.contains("rain") || text.contains("drizzle") || text.contains("shower"))
        return WeatherCondition::Rain;
    if (text.contains("fog") || text.contains("mist") || text.contains("haze"))
        return WeatherCondition::Fog;
    if (text.contains("clear") || text.contains("sunny"))
        return WeatherCondition::Sunny;
    if (text.contains("partly"))
        return WeatherCondition::PartlyCloudy;
    if (text.contains("cloud") || text.contains("overcast"))
        return WeatherCondition::Cloudy;

    // Russian
    if (text.contains(QStringLiteral("гроз")))
        return WeatherCondition::Thunderstorm;
    if (text.contains(QStringLiteral("снег")) || text.contains(QStringLiteral("метель")))
        return WeatherCondition::Snow;
    if (text.contains(QStringLiteral("дожд")) || text.contains(QStringLiteral("лив")))
        return WeatherCondition::Rain;
    if (text.contains(QStringLiteral("туман")) || text.contains(QStringLiteral("мгла")))
        return WeatherCondition::Fog;
    if (text.contains(QStringLiteral("ясн")) || text.contains(QStringLiteral("солнеч")))
        return WeatherCondition::Sunny;
    if (text.contains(QStringLiteral("переменн")))
        return WeatherCondition::PartlyCloudy;
    if (text.contains(QStringLiteral("облач")) || text.contains(QStringLiteral("пасмур")))
        return WeatherCondition::Cloudy;

    return WeatherCondition::Unknown;
}

inline QString conditionLabel(WeatherCondition condition)
{
    switch (condition)
    {
    case WeatherCondition::Sunny: return QStringLiteral("Солнечно");
    case WeatherCondition::PartlyCloudy: return QStringLiteral("Переменная облачность");
    case WeatherCondition::Cloudy: return QStringLiteral("Облачно");
    case WeatherCondition::Fog: return QStringLiteral("Туман");
    case WeatherCondition::Rain: return QStringLiteral("Дождь");
    case WeatherCondition::Snow: return QStringLiteral("Снег");
    case WeatherCondition::Thunderstorm: return QStringLiteral("Гроза");
    case WeatherCondition::Unknown: return QStringLiteral("Неизвестно");
    }

    return QStringLiteral("Неизвестно");
}

} // namespace weather
