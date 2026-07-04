#pragma once

#include <QSize>
#include <QString>

namespace weather {

struct AppConfig {
    QString city = QStringLiteral("Moscow");
    int refreshIntervalMs = 1 * 60 * 1000;
    QSize windowSize{320, 260};
};

} // namespace weather
