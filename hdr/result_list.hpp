#pragma once
#include "result.hpp"
#include <list>


class ResultList
{
private:
    std::list<Result> resultList;
public:
    void addEntry(Result result);
    void editEntry(Result result, int index);
    void deleteEntry(Result result, int index);
    const std::list<Result>& getList();
    enum action{
        NEW_ITEM,
        REMOVE_ITEM,
        CHANGE_ITEM
    };
};
