#pragma once

#include "result.hpp"
#include "shapes.hpp"

#include <memory>
#include <bitset>

//#include <iterator>
//#include <cstddef>


class ShapeModel {
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
        OptionObject(const OptionObject& other) = delete;
        OptionObject(OptionObject&& other) = default;
        bool init = false;
        const Shapes::Option* name = nullptr;
        std::unique_ptr<StateObject> state;
    };
    
    std::bitset<2> checkOptions;//удалить
    std::bitset<2> prevCheckOptions;
    int paramNumber = 0;
    StateObject defaultState;
    std::vector<OptionObject> stateOptions;
    void setupOptions(const std::vector<Shapes::Option> &options);
    OptionType addOption(const Shapes::Option &option, State state, OptionType prev);
    StateObject& currentStateObject(ShapeModel::State state);
    void initDouble (int number, StateObject& state, const Shapes::Option& option);
    void setDoubleDefault (int number, StateObject& state, const Shapes::Option& option);
    std::vector<const Shapes::Option*> getStateOptions (StateObject& state);
    
public:
    ShapeModel(const std::vector<Shapes::Option> &options);
    ShapeModel(Shapes::AbstactShape &newShape);
    ShapeModel(const ShapeModel& other) = delete;
    ShapeModel(ShapeModel&& other) = default;
    int getParamNumber();
    void setFirstOption(bool value);
    void setSecondOption(bool value);
    const Shapes::Option* getFormat();
    const Shapes::Option* getFormat(bool first, bool second = false);
    std::vector<const Shapes::Option*>& getDefaultShortNames();
    const std::vector<const Shapes::Option&>& getOptionsToRemove();
    const std::vector<const Shapes::Option&>& getOptionsToAdd();
    std::array<const Shapes::Option*, 7> getParamNames(); 
    class Iterator{
    private:
        enum Step {
            NAME,
            SHORT_NAMES,
            PARAMS_NAME,
            PARAMS_DEFAULT,
            FORMAT,
            END_STATE,
            END,
        };
        Step currentStep = END;
        int index = 0;
        const Shapes::Option* result = nullptr;
        StateObject *state = nullptr;
        StateObject *additionalState = nullptr;
        StateObject *currentState = nullptr;

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = const Shapes::Option;
        using pointer           = const Shapes::Option*;
        using reference         = const Shapes::Option&;
        
        Iterator();
        Iterator (StateObject *first, StateObject *second = nullptr);
        Iterator& begin();
        Iterator& end();
        reference operator*() const;
        pointer operator->();
        Iterator& operator++();
        Iterator& operator++(int);
        bool operator!=(const ShapeModel::Iterator& other) const;
    };
    static Iterator endIt;
    Iterator getRemovedOptions();
    Iterator getAddedOption();
};
