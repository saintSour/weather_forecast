#include "wttr_weather_provider.hpp"

#include <cpr/cpr.h>

#include <QLocale>
#include <QRegularExpression>
#include <QUrl>

namespace weather {

namespace {

QString decodeResponse(const cpr::Response &response) {
  if (response.status_code != 200) return {};

  return QString::fromUtf8(response.text.c_str()).trimmed();
}

WeatherData makeError(const QString &city, const QString &message) {
  WeatherData data;
  data.city = city;
  data.valid = false;
  data.errorMessage = message;
  return data;
}

double parseTemperature(const QString &raw) {
  static const QRegularExpression pattern(QStringLiteral("(-?\\d+)"));
  const QRegularExpressionMatch match = pattern.match(raw);
  if (!match.hasMatch()) return 0.0;

  bool ok = false;
  const double value = QLocale::c().toDouble(match.captured(1), &ok);
  return ok ? value : 0.0;
}

QString normalizeWind(const QString &raw) {
  QString wind = raw.trimmed();
  wind.remove(QRegularExpression(QStringLiteral("[\\x{2190}-\\x{21FF}]")));
  return wind.trimmed();
}

}  // namespace

WeatherData WttrWeatherProvider::fetch(const QString &city) {
  const QString encodedCity = QUrl::toPercentEncoding(city);
  const auto response =
      cpr::Get(cpr::Url{"https://wttr.in/" + encodedCity.toStdString() +
                        "?format=%t|%C|%h|%w&lang=ru"},
               cpr::Header{{"User-Agent", "curl/8.0"}});

  const QString body = decodeResponse(response);
  if (body.isEmpty()) {
    return makeError(city,
                     QStringLiteral("HTTP %1: %2")
                         .arg(response.status_code)
                         .arg(QString::fromStdString(response.error.message)));
  }

  const QStringList parts = body.split('|');
  if (parts.size() < 2)
    return makeError(city, QStringLiteral("Не удалось разобрать ответ API"));

  WeatherData data;
  data.city = city;
  data.valid = true;

  data.temperatureC = parseTemperature(parts.at(0));
  data.description = parts.at(1).trimmed();
  data.condition = conditionFromDescription(data.description);

  if (parts.size() > 2)
    data.humidity = parts.at(2).trimmed().remove('%').toInt();

  if (parts.size() > 3) data.wind = normalizeWind(parts.at(3));

  return data;
}

}  // namespace weather
