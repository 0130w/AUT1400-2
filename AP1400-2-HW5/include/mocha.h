#ifndef MOCHA_H
#define MOCHA_H
#include "espresso_based.h"

class Mocha : public EspressoBased
{
    public:
        Mocha() : EspressoBased() {
            create_ingredients();
            name = "Mocha";
        } 
        Mocha(const Mocha& mocha) : EspressoBased(mocha), side_items(mocha.side_items) {}
        ~Mocha();
        void operator=(const Mocha& mocha);

        virtual std::string get_name();
        virtual double price();

        void add_side_item(std::shared_ptr<Ingredient> side);
        std::vector<std::shared_ptr<Ingredient> >& get_side_items();


    private:
        void create_ingredients() {
            std::shared_ptr<Ingredient> espresso(new Espresso(2));
            std::shared_ptr<Ingredient> milk(new Milk(2));
            std::shared_ptr<Ingredient> milkfoam(new MilkFoam(1));
            std::shared_ptr<Ingredient> chocolate(new Chocolate(1));
            ingredients.push_back(espresso);
            ingredients.push_back(milk);
            ingredients.push_back(milkfoam);
            ingredients.push_back(chocolate);
        }
        std::vector<std::shared_ptr<Ingredient> > side_items;
    
};

#endif // MOCHA_H