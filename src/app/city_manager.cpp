#include "city_manager.hpp"

namespace weather {

CityManager::CityManager() :
    settings_("saintSour", "weather_widget"),
    defaultCities_{"Москва", "Санкт-Петербург", "Новосибирск", "Екатеринбург"} {}

QStringList CityManager::loadCities() const {
    QStringList cities = settings_.value("cities").toStringList();
    return cities.isEmpty() ? defaultCities_ : cities;
}

void CityManager::saveCities(const QStringList &cities) {
    settings_.setValue("sities", cities);
}

} // weather