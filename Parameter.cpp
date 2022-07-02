#include "Parameter.hpp"
#include <algorithm>


namespace MSQ
{
    inline float fclamp(float max, float min, float value)
    {
        return std::min(max, std::max(min, value));
    }

    Parameter::Parameter(float min, float max)
    : min_(min), max_(max), value_(min_){}

    float Parameter::getMax() const 
    {
        return max_;
    }

    float Parameter::getMin() const 
    {
        return min_;
    }

    float Parameter::getValue() const 
    {
        return value_;
    }

    void Parameter::setValue(float val)
    {
        value_ = fclamp(min_, max_, val);
    }
}