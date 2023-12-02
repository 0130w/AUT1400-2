#include "cappuccino.h"

Cappuccino::~Cappuccino() {
    side_items.clear();
}
void Cappuccino::operator=(const Cappuccino& cap) {
    EspressoBased::operator=(cap);
}

std::string Cappuccino::get_name() {
    return this->name;
}

double Cappuccino::price() {
    double result = 0;
    for(auto ingredient : ingredients) {
        result += (ingredient->get_price_unit() * ingredient->get_units());
    }
    for(auto side_item : side_items) {
        result += (side_item->get_price_unit() * side_item->get_units());
    }
    return result;
}

void Cappuccino::add_side_item(std::shared_ptr<Ingredient> side) {
    side_items.push_back(side);
}

std::vector<std::shared_ptr<Ingredient> >& Cappuccino::get_side_items() {
    return side_items;
}