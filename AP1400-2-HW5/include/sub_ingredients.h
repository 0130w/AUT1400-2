#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H
#include "ingredient.h"

#define DEFCLASS(ingredient_name, price)   class ingredient_name : public Ingredient {                 \
            public:                                                                             \
                ingredient_name(size_t units) : Ingredient{price, units} {                      \
                    this->name = #ingredient_name;                                              \
                }                                                                               \
                virtual std::string get_name() { return this->name; }                           \
}                                                                                               \

DEFCLASS(Cinnamon, 5);
DEFCLASS(Chocolate, 5);
DEFCLASS(Sugar, 1);
DEFCLASS(Cookie, 10);
DEFCLASS(Espresso, 15);
DEFCLASS(Milk, 10);
DEFCLASS(MilkFoam, 5);
DEFCLASS(Water, 1);

#endif // SUB_INGREDIENTS_H