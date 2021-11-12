#include "shape_model.hpp"

ShapeModel::Iterator::Iterator() {}

ShapeModel::Iterator::Iterator(ShapeModel::StateObject* first, ShapeModel::StateObject* second):
currentStep (NAME), state{first}, additionalState {second} 
{}

ShapeModel::Iterator ShapeModel::endIt {};


ShapeModel::Iterator& ShapeModel::Iterator::begin() {
    currentStep = NAME;
    index = 0;
    return *this;
}


ShapeModel::Iterator& ShapeModel::Iterator::operator++() {
    while (!result) {
        switch (currentStep){
        case NAME:
            result = state->name;
            currentStep = SHORT_NAMES;
            index = 0;
            break;
        case SHORT_NAMES:
            if (index < state->shortNames.size()) {
                result = state->shortNames[index];
                ++index;
            } else {
                result = nullptr;
                currentStep = PARAMS_NAME;
                index = 0;
            }
            break;
        case PARAMS_NAME:
            if (index < state->params.size()) {
                result = state->params[index].name;
                ++index;
            } else {
                result = nullptr;
                currentStep = PARAMS_DEFAULT;
                index = 0;
            }
            break;
        case PARAMS_DEFAULT:
            if (index < state->params.size()) {
                result = state->params[index].defaultOption;
                ++index;
            } else {
                result = nullptr;
                currentStep = FORMAT;
                index = 0;
            }
            break;
        case FORMAT:
            result = state->printFormat;
            currentStep = END_STATE;
        case END_STATE:
            if (additionalState && currentState == additionalState) {
                currentState = additionalState;
                currentStep = NAME;
            } else {
                currentStep = END;
            }
            break;
        case END:
            return *this;
            break;
        }
    }
    return *this;
}


ShapeModel::Iterator::pointer ShapeModel::Iterator::operator->() {
    return result;
}


ShapeModel::Iterator::reference ShapeModel::Iterator::operator*() const {
    return *result;
}

bool ShapeModel::Iterator::operator!=(const ShapeModel::Iterator& other) const {
    return other.currentStep != currentStep;
}


ShapeModel::Iterator& ShapeModel::Iterator::end() {
    return ShapeModel::endIt;
}
