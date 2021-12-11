#include "shape_model.hpp"
#include  <cstring>

ShapeModel::ShapeModel(const std::vector<Shapes::Option> &options) {
    setupOptions(options);
    for(auto& x: defaultState.params) {
        if (x.init) {
            ++paramNumber;
        } else {
            break;
        }
    }
}

 void ShapeModel::setupOptions(const std::vector<Shapes::Option> &options) {
    State currentState = NO_OPTIONS;
    OptionType previous;
    for (auto& option: options) {
        previous = OTHER;
        switch (option.type) {
            case Shapes::IF_BOOL_1_ON:
                if (stateOptions.empty()) {
                    stateOptions.emplace_back(false);
                }
                currentState = OPTION1_ON;
                break;
            case Shapes::IF_BOOL_2_ON:
                if (stateOptions.size() < 2) {
                    stateOptions.resize(2);
                }
                currentState = OPTION2_ON;
                break;
            case Shapes::FI_BOOL_ON:
                currentState = NO_OPTIONS;
                break;
            case Shapes::IF_BOTH_BOOL_ON:
                if (stateOptions.size() < 3) {
                    stateOptions.resize(3);
                }
                stateOptions[2].init = true;
                currentState = OPTIONS_ON;
                break;
            case Shapes::INPUT_BOOL_1:
                if (stateOptions.empty()) {
                    stateOptions.emplace_back(true);
                } else {
                    stateOptions[0].init = true;
                }
                stateOptions[0].name = &option;
                break;
            case Shapes::INPUT_BOOL_2:
                if (stateOptions.size() < 2) {
                    stateOptions.resize(2);
                } 
                stateOptions[1].init = true;
                stateOptions[1].name = &option;
                break;
            default:
                addOption(option, currentState, previous);
        }
    }
}

ShapeModel::OptionType ShapeModel::addOption(const Shapes::Option& option, ShapeModel::State state, OptionType prev){
    auto& stateObj = currentStateObject(state);
    switch (option.type) {
        case Shapes::INPUT_DOUBLE_1:
            initDouble(1, stateObj, option);
            return FLOAT_1;
            break;
        case Shapes::INPUT_DOUBLE_2:
            initDouble(2, stateObj, option);
            break;
        case Shapes::INPUT_DOUBLE_3:
            initDouble(3, stateObj, option);
            break;
        case Shapes::INPUT_DOUBLE_4:
            initDouble(4, stateObj, option);
            break;
        case Shapes::NAME:
            stateObj.name = &option;
            break;
        case Shapes::SHORT_NAME:
            stateObj.shortNames.push_back(&option);
            break;
        case Shapes::PRINTF_TEMPLATE:
            stateObj.printFormat = &option;
            break;
        case Shapes::DOUBLE_DEFAULT:
            if (prev == FLOAT_1) {
                setDoubleDefault(1, stateObj, option);
            } else if (prev == FLOAT_2) {
                setDoubleDefault(2, stateObj, option);
            } else if (prev == FLOAT_3) {
                setDoubleDefault(3, stateObj, option);
            } else if (prev == FLOAT_4) {
                setDoubleDefault(4, stateObj, option);
            }
            return prev;
        default:
            return OTHER;
    }
    return OTHER;
}


ShapeModel::OptionObject::OptionObject(bool initialization):
init{initialization}, name {nullptr}, state{}
{}


void ShapeModel::initDouble (int number, StateObject& state, const Shapes::Option& option) {
    if(number > state.params.size()){
        state.params.resize(number);
    }
    --number;
    state.params[number].init = true;
    state.params[number].name = &option;
}

void ShapeModel::setDoubleDefault(int number, ShapeModel::StateObject& state, const Shapes::Option& option) {
    if (number > state.params.size()) return;
    state.params[number - 1].defaultOption = &option;
    auto pos = option.text.find(',');
    if (pos != std::string::npos) {
        char tempData[option.text.size()];
        std::strcpy(tempData, option.text.c_str());
        tempData[pos] = '.';
        state.params[number - 1].defaultValue = std::atof(tempData);
    }
    state.params[number - 1].defaultValue = std::atof(option.text.c_str());
}

ShapeModel::StateObject& ShapeModel::currentStateObject(ShapeModel::State state){
    switch(state) {
        case NO_OPTIONS:
            return defaultState;
        case OPTION1_ON:
            if (!stateOptions[0].state) {
                stateOptions[0].state = std::make_unique<StateObject>();
            }
            return *stateOptions[0].state;
        case OPTION2_ON:
            if (!stateOptions[1].state) {
                stateOptions[1].state = std::make_unique<StateObject>();
            }
            return *stateOptions[1].state;
        case OPTIONS_ON:
            if (!stateOptions[2].state) {
                stateOptions[2].state = std::make_unique<StateObject>();
            }
            return *stateOptions[2].state;
    }
    return defaultState;
}


std::vector<const Shapes::Option*> ShapeModel::getStateOptions(ShapeModel::StateObject& state) {
    std::vector<const Shapes::Option*> vect;
    if (state.name) vect.push_back(state.name);
    for (auto ptr: state.shortNames) vect.push_back(ptr);
    for (auto& param: state.params) {
        if (!param.init) continue;
        if (param.name) vect.push_back(param.name);
        if (param.defaultOption) vect.push_back(param.defaultOption);
    }
    if (state.printFormat) vect.push_back(state.printFormat);    
    return vect;
}
/*
ShapeModel::Iterator ShapeModel::getRemovedOptions() {
    if (prevCheckOptions[0] != checkOptions[0]) {
        if (checkOptions[0]) {
            if (checkOptions[1]){
                return Iterator(stateOptions[0].state.get(), stateOptions[2].state.get());
            } else {
                return Iterator(stateOptions[0].state.get());
            }
        } else {
            
        }
        
    } else if (prevCheckOptions[1] != checkOptions[1]) {
        if (checkOptions[1]) {
            
        } else {}
    }
    return Iterator();
}
*/
const Shapes::Option* ShapeModel::getFormat(bool first, bool second) const {
    if (stateOptions.size() == 3) {
        if (first && second && stateOptions[2].init 
            && stateOptions[2].state && stateOptions[2].state->printFormat) {
            return stateOptions[2].state->printFormat;
        }
    }
    if (stateOptions.size() > 0) {
        if (first && stateOptions[0].init 
            && stateOptions[0].state && stateOptions[0].state->printFormat) {
            return stateOptions[0].state->printFormat;
        }
        if (stateOptions.size() > 1) {
            if (second && stateOptions[1].init 
                && stateOptions[1].state && stateOptions[1].state->printFormat) {
                return stateOptions[1].state->printFormat;
            }
        }
    }
    return defaultState.printFormat;
}

const std::vector<const Shapes::Option*>& ShapeModel::getDefaultShortNames () const {
    return defaultState.shortNames;
}

std::array<const Shapes::Option*, 7> ShapeModel::getParamNames() const {
    std::array<const Shapes::Option*, 7> paramNames{defaultState.name};
    int index = 1;
    for (auto& param: defaultState.params) {
        if (param.init) {
            paramNames[index] = param.name;
        }
        ++index;
    }
    if (stateOptions.size() > 0 && stateOptions[0].init) {
        paramNames[5] =  stateOptions[0].name;
        if (stateOptions.size() > 1 && stateOptions[1].init) {
            paramNames[6] =  stateOptions[1].name;
        }
    }
    return paramNames;
}

int ShapeModel::getParamNumber() const {
    return paramNumber;
}

const Shapes::Option* ShapeModel::getName() const {
    return defaultState.name;
}

std::pair<const Shapes::Option *, double> ShapeModel::getDoubleInput(int number) {
    --number;
    if (defaultState.params[number].init || defaultState.params.size() <= number || number < 0){
        return {nullptr, 0.};
    }
    return {defaultState.params[number].name, defaultState.params[number].defaultValue};
}
