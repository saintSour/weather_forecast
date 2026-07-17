#include "city_input_dialog.hpp"

namespace weather {

CityInputDialog::CityInputDialog(QWidget *parent) {
    setWindowTitle("Добавление города");
    setLabelText("Введите название города:");
    setInputMode(QInputDialog::TextInput);

    setStyleSheet(
    "QInputDialog { background-color: #141820; border-radius: 12px; }"
    "QLabel { color: rgba(255, 255, 255, 230); font-size: 13px; }"
    "QLineEdit { background: rgba(255, 255, 255, 20); color: white; border: 1px solid rgba(255, 255, 255, 40); border-radius: 6px; padding: 6px; font-size: 13px; }"
    "QPushButton { background-color: rgba(255, 77, 77, 200); color: white; border: none; border-radius: 6px; padding: 6px 14px; font-weight: bold; }"
    "QPushButton:hover { background-color: #ff3333; }"
    );
}

QString CityInputDialog::getTrimmedCity() const {
    return textValue().trimmed();
}

} // weather