#include "server.h"
#include "client.h"

Server::Server() {}

std::shared_ptr<Client> Server::add_client(std::string id) {
  // scan id
  for(auto &client : clients) {
    if(client.first->get_id() == id) {
      int random_number = std::rand() % 9000 + 1000;
      id += random_number;
    }
  }
  std::shared_ptr<Client> new_client = std::make_shared<Client>(id, *this);
  clients.insert({new_client, 5});
  return new_client;
}

std::shared_ptr<Client> Server::get_client(std::string id) const {
  for(auto &client : clients) {
    if(client.first->get_id() == id) {
      return client.first;
    }
  }
  return nullptr;
}

double Server::get_wallet(std::string id) const {
  for(auto &client : clients) {
    if(client.first->get_id() == id) {
      return client.second;
    }
  }
  std::cout << "client with id = " << id << " not exists" << std::endl;
  return -1;
}

bool Server::parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value) {
  // standard form sender-receiver-value
  std::string delimiter = "-";
  std::string token;
  size_t pos = 0;
  for(int i = 0; i < 3; ++i) {
    pos = trx.find(delimiter);
    if(pos == std::string::npos) {
      if(i != 2)
        throw std::runtime_error("Trx string is not standard.");
      else
        pos = trx.size();
    }
    token = trx.substr(0, pos);
    switch (i) {
      case 0 :
        sender = token;
        break;
      case 1 :
        receiver = token;
        break;
      case 2 : {
        try {
          value = std::stod(token);
        } catch (std::exception()) {
          throw std::runtime_error("Try convert a string to double failed" + std::string(token));
        }
      } break;
      default :
        throw std::runtime_error("Runtime error!");
    }
    trx.erase(0, pos + 1);
  }
  return true;
}

bool Server::add_pending_trx(std::string trx, std::string signature) const{
  // only accept authenticating trx and sender should have enough money
  std::string sender, receiver;
  double value;
  parse_trx(trx, sender, receiver, value);
  double sender_money = 0;
  if(!get_client(sender) || !get_client(receiver)) {
    std::cout << "sender or receiver not exists." << std::endl;
    return false;
  }
  if(get_wallet(sender) < value) {
    std::cout << "sender doesn't have enough money." << std::endl;
    return false;
  }
  bool authentic = crypto::verifySignature(get_client(sender)->get_publickey(), trx, signature);
  if(!authentic) {
    std::cerr << "fail to pass trx verification." << std::endl;
    return false;
  }
  pending_trxs.push_back(trx);
  return true;
}

size_t Server::mine() {
  // put trxs together -> mempool
  std::string mempool;
  for(auto pending_trx : pending_trxs) {
    mempool += pending_trx;
  }
  // call all clients to generate a nonce to generate sha256
  size_t nonce = 0;
  while(true) {
    for(auto &client : clients) {
      nonce = client.first->generate_nouce();
      std::string hash{crypto::sha256(mempool + std::to_string(nonce))};
      if(hash.substr(0, 10).find("000") != std::string::npos) {
        // award
        client.second += 6.25;
        // take effect
        for(auto pending_trx : pending_trxs) {
          std::string sender, receiver;
          double value;
          parse_trx(pending_trx, sender, receiver, value);
          for(auto &client: clients) {
            if(client.first->get_id() == sender) {
              client.second -= value;
            } else if(client.first->get_id() == receiver) {
              client.second += value;
            }
          }
        }
        pending_trxs.clear();
        std::cout << "miner " << client.first->get_id() << " successfully get the award!" << std::endl;
        return nonce;
      }
    }
  }
}
