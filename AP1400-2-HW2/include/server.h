#ifndef SERVER_H
#define SERVER_H
#include <iostream>
#include <client.h>
#include <map>

class Client;

class Server
{
    public:
        Server();
        /**
         * @brief create a new client with the specified id.
         * if the id already exists, the server should add random 4 digit number at the end of it automatically.
         * every client should have 5 coins at the beginning.
         * @param id 
         * @return std::shared_ptr<Client> 
         */
        std::shared_ptr<Client> add_client(std::string id);
        /**
         * @brief Get the client shared_ptr
         * 
         * @param id 
         * @return std::shared_ptr<Client> 
         */
        std::shared_ptr<Client> get_client(std::string id);
        /**
         * @param id 
         * @return the wallet value of the client with username id
         */
        double get_wallet(std::string id) const;
        /**
         * @brief parse the transaction shown as "sender-receiver-value"
         * @throw if string is not standard, throw a runtime error 
         */
        bool parse_trx(std::string trx, std::string sender, std::string receiver, double value);
        /**
         * @brief add a pending transaction
         * only accepting a pending transaction by authenticating the sender's signature
         * and if he has enough money.
         */
        bool add_pending_trx(std::string trx, std::string signature);

        size_t mine();
    private:
        std::map<std::shared_ptr<Client>, double> clients;
        friend void show_wallets(const Server& server);
};

#endif //SERVER_H