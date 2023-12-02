#ifndef INGREDIENT_H
#define INGREDIENT_H
#include <string>

class Ingredient 
{
    public:
        double get_price_unit() { return price_unit; }
        size_t get_units() { return units; }
        // note : a pure virtual function can optionally have bodies
        virtual std::string get_name() = 0;
        virtual ~Ingredient() = default;

        double price() { return (double)(price_unit * units); }

    protected:
        Ingredient(double price_unit, size_t units) : price_unit(price_unit), units(units) {}
        
        double price_unit;
        size_t units;
        std::string name;
};

#endif // INGREDIENT_H