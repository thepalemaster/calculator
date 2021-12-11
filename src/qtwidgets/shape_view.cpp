#include <QtWidgets/QPushButton>

#include "shape_view.hpp"
#include "modal_option.hpp"



ShapeViewer::ShapeViewer(Calculator& calc, const Result& shapeResult, QWidget* parent):
QWidget(parent), calculator{calc}
{
    ui.setupUi(this);
    ui.shapeInfo->setText(getText(shapeResult));
    connect(ui.removeButton, &QPushButton::clicked, this, [this](){
        calculator.remove(index);
    });
    connect(ui.editButton, &QPushButton::clicked, this, [this, /*!!!*/&shapeResult](){
        auto modalWin= new ModalOptions(index, calculator, shapeResult);
        modalWin->show();
    });
}

QString ShapeViewer::getText(const Result& shapeResult) {
    auto format = calculator.models[shapeResult.shapeID]
        .getFormat(shapeResult.param.options[0], shapeResult.param.options[1]);
    int expectedSize = format->text.size() + 5 * 10;
    char buff[expectedSize];
    int realSize = std::snprintf(buff, expectedSize, format->text.data(), shapeResult.area, shapeResult.param.numbers[0], shapeResult.param.numbers[1],
                        shapeResult.param.numbers[2], shapeResult.param.numbers[3]);
    if (realSize > expectedSize) {
        char newBuff[realSize + 1];
        std::sprintf(newBuff, format->text.data(), shapeResult.area, shapeResult.param.numbers[0], shapeResult.param.numbers[1],
                        shapeResult.param.numbers[2], shapeResult.param.numbers[3]);
        newBuff[realSize] = '\0';
        return newBuff;
    }
    buff[realSize] = '\0';
    return buff;
}

void ShapeViewer::newShape(const Result& shapeResult) {
    ui.shapeInfo->setText(getText(shapeResult));
}

void ShapeViewer::setInvisible() {
    ui.shapeInfo->clear();
    this->hide();
}
