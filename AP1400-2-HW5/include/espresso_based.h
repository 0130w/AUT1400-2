#ifndef ESPRESSO_BASED_H
#define ESPRESSO_BASED_H
#include <string>
#include "sub_ingredients.h"
class EspressoBased
{
    public:
        virtual std::string get_name() = 0;
        virtual double price() = 0;
        void brew();
        std::vector<std::shared_ptr<Ingredient> >& get_ingredients();

        virtual ~EspressoBased();

    protected:
        EspressoBased() {};
        EspressoBased(const EspressoBased& esp) : ingredients(esp.ingredients), name(esp.name) {}
        void operator=(const EspressoBased& esp) {
            this->ingredients = esp.ingredients;
            this->name = esp.name;
        }

        std::vector<std::shared_ptr<Ingredient> > ingredients;
        std::string name;
};

#endif // ESPRESSO_BASED_H