#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>


int main() {


    mongocxx::instance inst{};
    mongocxx::client conn{ mongocxx::uri{"mongodb://localhost:27017"} };

    auto db = conn["mydatabase"];
    auto collection = db["mycollection"];

    // ���⼭���� MongoDB���� ��ȣ �ۿ� �ڵ� �ۼ�

}

