#include "server.h"

Server::Server() {
    // TODO
}

std::shared_ptr<Client> Server::add_client(std::string id) {
    // TODO
}

std::shared_ptr<Client> Server::get_client(std::string id) {
    // TODO
}

double Server::get_wallet(std::string id) const {
    // TODO
}

bool Server::parse_trx(std::string trx, std::string sender, std::string receiver, double value) {
    // TODO
}

bool Server::add_pending_trx(std::string trx, std::string signature) {
    // TODO
}

size_t Server::mine() {
    // TODO
}