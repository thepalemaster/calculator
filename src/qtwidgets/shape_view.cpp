#include <QtWidgets/QPushButton>

#include "shape_view.hpp"
#include "modal_option.hpp"
#include "utility_shape_text.hpp"


ShapeViewer::ShapeViewer(Calculator& calc, const Result& shapeResult, QWidget* parent):
QWidget(parent), calculator{calc}
{
    ui.setupUi(this);
    ui.shapeInfo->setText(Utility::getText<QString>(shapeResult, calculator));
    connect(ui.removeButton, &QPushButton::clicked, this, [this](){
        calculator.remove(index);
    });
    connect(ui.editButton, &QPushButton::clicked, this, [this](){
        auto modalWin = new ModalOptions(index, calculator, calculator.getResultList()[index]);//сделать чтобы это удобоваримее
        modalWin->show();
    });
}

void ShapeViewer::newShape(const Result& shapeResult) {
    ui.shapeInfo->setText(Utility::getText<QString>(shapeResult, calculator));
}

void ShapeViewer::setInvisible() {
    ui.shapeInfo->clear();
    this->hide();
}
