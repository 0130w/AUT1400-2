#include "client.h"

Client::Client(std::string id, const Server& server) : id(id), server(&server) {}

std::string Client::get_id() {
    return id;
}

std::string Client::get_publickey() {
    return public_key;
}

double Client::get_wallet() {
    return server->get_wallet(id);
}

std::string Client::sign(std::string txt) {
    std::string signature = crypto::signMessage(private_key, txt);
    return signature;
}

bool Client::transfer_money(std::string receiver, double value) {
    // TODO
}

size_t Client::generate_nouce() {
    // TODO
}