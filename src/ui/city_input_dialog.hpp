#pragma once
#include <QInputDialog>

namespace weather {
class CityInputDialog : public QInputDialog {
    Q_OBJECT
public:
    explicit CityInputDialog(QWidget *parent = nullptr);
    QString getTrimmedCity() const;
};
} // weather