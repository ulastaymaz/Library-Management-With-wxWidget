#pragma once
#include "../Data/Data.hpp"
#include <vector>
#include "../Data_Models/Book.hpp"
class ParentFrameInterface {
public:
    virtual void Show() = 0;
    virtual ~ParentFrameInterface() {}
};

