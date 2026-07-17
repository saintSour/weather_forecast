#pragma once
#include <QString>
#include <QSettings>

namespace weather {

class CityManager {
public:
    CityManager();
    QStringList loadCities() const;
    void saveCities(const QStringList &cities);

private:
    QSettings settings_;
    const QStringList defaultCities_;
};

} // weather