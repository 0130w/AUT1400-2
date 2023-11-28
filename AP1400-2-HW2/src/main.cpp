
#include <iostream>
#include <gtest/gtest.h>
#include "client.h"
#include "server.h"

std::vector<std::string> pending_trxs;

void show_pending_transactions() {
    std::cout << std::string(20, '*') << std::endl;
    for(const auto& trx : pending_trxs) {
        std::cout << trx << std::endl;
    }
    std::cout << std::string(20, '*') << std::endl;
}

void show_wallets(const Server& server) {
    std::cout << std::string(20, '*') << std::endl;
    for(const auto& client : server.clients) {
        std::cout << client.first->get_id() << " : " << client.second << std::endl;
    }
    std::cout << std::string(20, '*') << std::endl;
}

int main(int argc, char **argv)
{
    if (false) // make false to run unit-tests
    {
        // debug section
    }
    else
    {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;   
}