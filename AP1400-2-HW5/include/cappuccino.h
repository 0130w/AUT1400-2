#ifndef CAPPUCCINO
#define CAPPUCCINO
#include "espresso_based.h"

class Cappuccino : public EspressoBased
{
    public:
        Cappuccino() : EspressoBased() {
            create_ingredients();
            name = "Cappuccino";
        }
        Cappuccino(const Cappuccino& cap) : EspressoBased(cap), side_items(cap.side_items) {}
        ~Cappuccino();
        void operator=(const Cappuccino& cap);

        virtual std::string get_name();
        virtual double price();

        void add_side_item(std::shared_ptr<Ingredient> side);
        std::vector<std::shared_ptr<Ingredient> >& get_side_items();

    private:
        void create_ingredients() {
            std::shared_ptr<Ingredient> espresso(new Espresso(2));
            std::shared_ptr<Ingredient> milk(new Milk(2));
            std::shared_ptr<Ingredient> milkfoam(new MilkFoam(1));
            ingredients.push_back(espresso);
            ingredients.push_back(milk);
            ingredients.push_back(milkfoam); 
        }
        std::vector<std::shared_ptr<Ingredient> > side_items;
};

#endif // CAPPUCCINO