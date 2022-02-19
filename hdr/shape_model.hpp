#pragma once

#include "result.hpp"
#include "shapes.hpp"

#include <memory>


class ShapeModel final {
private: 
    enum State {
        NO_OPTIONS,
        OPTION1_ON,
        OPTION2_ON,
        OPTIONS_ON        
    };
    
    enum OptionType {
        FLOAT_1,
        FLOAT_2,
        FLOAT_3,
        FLOAT_4,
        ANOTHER_LANG,
        OTHER,
    };
    
    struct DoubleObject {
        bool init = false;
        const Shapes::Option* name = nullptr;
        double defaultValue = 0;
        const Shapes::Option* defaultOption = nullptr;
    };
    
    struct StateObject{
        const Shapes::Option* name = nullptr;
        std::vector<const Shapes::Option*> shortNames;
        std::vector<DoubleObject> params;
        const Shapes::Option* printFormat = nullptr;
    };
    
    struct OptionObject {
        OptionObject(bool initialization = false);
        bool init = false;
        const Shapes::Option* name = nullptr;
        std::unique_ptr<StateObject> state;
    };
    int paramNumber = 0;
    StateObject defaultState;
    std::vector<OptionObject> stateOptions;
    void setupOptions(const std::vector<Shapes::Option> &options);
    void applyState(std::array<const Shapes::Option*, 5>& names, const StateObject& state) const;
    OptionType addOption(const Shapes::Option &option, State state, OptionType prev);
    StateObject& currentStateObject(ShapeModel::State state);
    void initDouble (int number, StateObject& state, const Shapes::Option& option);
    void setDoubleDefault (int number, StateObject& state, const Shapes::Option& option);
    std::vector<const Shapes::Option*> getStateOptions (StateObject& state);
    
public:
    ShapeModel(const std::vector<Shapes::Option> &options);
    ShapeModel(Shapes::AbstractShape &newShape);
    int getParamNumber() const;
    const Shapes::Option* getName() const;
    std::pair<const Shapes::Option*, double> getDoubleInput(int number);
    const Shapes::Option* getFormat(bool first, bool second = false) const;
    const std::vector<const Shapes::Option*>& getDefaultShortNames() const;
    std::array<const Shapes::Option*, 7> getParamNames() const; 
    std::array<const Shapes::Option*, 5> updateNames(bool first, bool second) const; 

};
