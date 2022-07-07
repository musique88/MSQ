namespace MSQ
{
    class Parameter
    {
        float value_;
        float min_;
        float max_;
    public:
        Parameter(float min, float max);

        float getValue() const;    
        float getMin() const;
        float getMax() const;
        void setValue(float val);
    };
}