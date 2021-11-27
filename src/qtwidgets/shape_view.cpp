#include <QtWidgets/QPushButton>
#include "shape_view.hpp"

ShapeViewer::ShapeViewer(const std::vector<ShapeModel>& modelsList, const Result& shapeResult, QWidget* parent):
QWidget(parent), models{modelsList}, hbox{new QHBoxLayout()}, shapeInfo {new QLabel()}{
    shapeInfo->setText(getText(shapeResult));
    hbox->addWidget(shapeInfo);
    auto buttonRemove = new QPushButton("-");
    buttonRemove->setFlat(true);
    hbox->addWidget(buttonRemove);
    setLayout(hbox);
}

QString ShapeViewer::getText(const Result& shapeResult) {
    auto format = models[shapeResult.shapeID]
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
    shapeInfo->setText(getText(shapeResult));
}

