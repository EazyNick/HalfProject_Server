#ifndef SESSION_MANAGER_H
#define SESSION_MANAGER_H

#include <unordered_map>
#include <memory>
#include "Session.h"

//class Session; // 전방 선언

class SessionManager {
public:
    void add_session(std::shared_ptr<Session> session) {
        sessions_[session->get_client_id()] = session;
    }

    void remove_session(int client_id) {
        sessions_.erase(client_id);
    }

    std::shared_ptr<Session> get_session(int client_id) const {
        auto it = sessions_.find(client_id);
        if (it != sessions_.end()) {
            return it->second;
        }
        return nullptr;
    }
    int generate_client_id() {
        static int current_id = 0;
        return ++current_id;
    }
private:
    std::unordered_map<int, std::shared_ptr<Session>> sessions_;
};

#endif // SESSION_MANAGER_H