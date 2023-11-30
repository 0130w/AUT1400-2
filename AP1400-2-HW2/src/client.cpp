#include "client.h"
#include "server.h"

Client::Client(std::string id, const Server& server) : id(id), server(&server) {
  crypto::generate_key(public_key, private_key);
}

std::string Client::get_id() {
  return id;
}

std::string Client::get_publickey() const{
  return public_key;
}

double Client::get_wallet() {
  return server->get_wallet(id);
}

std::string Client::sign(std::string txt) const{
  std::string signature = crypto::signMessage(private_key, txt);
  return signature;
}

bool Client::transfer_money(std::string receiver, double value) {
  // create a transaction in the server according to its input
  std::string transaction_string;
  transaction_string = id + "-" + receiver + "-" + std::to_string(value);
  std::cout << "transaction_string : " << transaction_string << std::endl;
  // check value
  if(get_wallet() <= value) {
    std::cout << "sender doesn't have enough money." << std::endl;
    return false;
  }
  // check receiver
  if(!server->get_client(receiver)) {
    std::cout << "receiver not exists." << std::endl;
    return false;
  }
  std::string transaction_signature = crypto::signMessage(private_key, transaction_string);
  server->add_pending_trx(transaction_string, transaction_signature);
  return true;
}

size_t Client::generate_nouce() {
  return std::rand();
}
