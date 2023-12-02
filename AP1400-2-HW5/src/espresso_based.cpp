#include "espresso_based.h"

EspressoBased::~EspressoBased() {
    ingredients.clear();
}

void EspressoBased::brew() {
    // todo!
}

std::vector<std::shared_ptr<Ingredient> >& EspressoBased::get_ingredients() {
    return ingredients;
}