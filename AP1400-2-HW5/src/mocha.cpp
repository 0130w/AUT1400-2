#include "mocha.h"

Mocha::~Mocha() {
    side_items.clear();
}

void Mocha::operator=(const Mocha& mocha) {
    EspressoBased::operator=(mocha);
}

std::string Mocha::get_name() {
    return name;
}

double Mocha::price() {
    double result = 0;
    for(auto ingredient : ingredients) {
        result += (ingredient->get_price_unit() * ingredient->get_units());
    }
    for(auto side_item : side_items) {
        result += (side_item->get_price_unit() * side_item->get_units());
    }
    return result;
}

void Mocha::add_side_item(std::shared_ptr<Ingredient> side) {
    side_items.push_back(side);
}

std::vector<std::shared_ptr<Ingredient> >& Mocha::get_side_items() {
    return side_items;
}