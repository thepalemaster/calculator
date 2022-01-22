#include <QtWidgets/QPushButton>

#include "modal_option.hpp"

ModalOptions::ModalOptions(int index, Calculator& calc, const Result& oldResult, QWidget* parent):
QWidget(parent) {
    modalInput = new ShapeInput(oldResult.shapeID,
                                calc.models[oldResult.shapeID].getName()->text.data(),
                                calc.models[oldResult.shapeID]);
    modalInput->setInput(oldResult);
    auto setupButton = new QPushButton("ИЗМЕНИТЬ");
    auto modalLayout = new QVBoxLayout();
    modalLayout->addWidget(modalInput);
    modalLayout->addWidget(setupButton);
    setWindowModality(Qt::WindowModality::ApplicationModal);
    setWindowTitle("Edit Shape");
    setLayout(modalLayout);
    connect(setupButton, &QPushButton::clicked, this, [this, index, &calc](){
        auto newResult = modalInput->getInput();
        calc.edit(index, newResult);
        this->close();
    });
}
