#ifndef SESSION_MANAGER_H
#define SESSION_MANAGER_H

#include <unordered_map>
#include <memory>
// #include <mutex>
// #include "Logger.h"
#include "Session.h"

class SessionManager {
public:
    // Singleton access method
    static SessionManager& GetInstance() {
        static SessionManager instance;
        return instance;
    }

    // Methods to manage sessions
    void add_session(int client_id, std::shared_ptr<Session> session) {
        sessions_[client_id] = session;
    }
    void remove_session(int client_id) {
        sessions_.erase(client_id);
    }
    std::shared_ptr<Session> get_session(int client_id) const {
        //Logger::GetInstance().log("get_session");
        auto it = sessions_.find(client_id);
        if (it != sessions_.end()) {
            return it->second;
        }
        return nullptr;
    }
    int generate_client_id() {
        //static std::mutex mtx; // Mutex ����
        //std::lock_guard<std::mutex> lock(mtx); // �Լ� ������ ���� ������ ��ȣ
        static int current_id = 0;
        return ++current_id;
    }

private:
    // Constructor is private to prevent external instantiation
    SessionManager() {}

    // Container to hold sessions
    std::unordered_map<int, std::shared_ptr<Session>> sessions_;

    // Deleted copy constructor and assignment operator to prevent copying
    SessionManager(const SessionManager&) = delete;
    SessionManager& operator=(const SessionManager&) = delete;
};

#endif // SESSION_MANAGER_H


//#ifndef SESSION_MANAGER_H
//#define SESSION_MANAGER_H
//
//#include <unordered_map>
//#include <memory>
////#include <mutex>
////#include "Logger.h"
//#include "Session.h"
//
////class Session; // ���� ����
//
//class SessionManager {
//public:
//
//    void add_session(int client_id, std::shared_ptr<Session> session) {
//        sessions_[client_id] = session;
//    }
//
//    void remove_session(int client_id) {
//        sessions_.erase(client_id);
//    }
//
//    std::shared_ptr<Session> get_session(int client_id) const {
//        //Logger::GetInstance().log("get_session");
//        auto it = sessions_.find(client_id);
//        if (it != sessions_.end()) {
//            return it->second;
//        }
//        return nullptr;
//    }
//    int generate_client_id() {
//        //static std::mutex mtx; // Mutex ����
//        //std::lock_guard<std::mutex> lock(mtx); // �Լ� ������ ���� ������ ��ȣ
//        static int current_id = 0;
//        return ++current_id;
//    }
//
//    static SessionManager& GetInstance() {
//        static SessionManager instance;
//        return instance;
//
//private:
//    SessionManager() {} // �����ڸ� private���� �����Ͽ� �ܺο����� �ν��Ͻ� ���� ����
//    std::unordered_map<int, std::shared_ptr<Session>> sessions_;
//
//    //// ���� �����ڿ� ���� �����ڸ� ���� Ȥ�� private���� �����Ͽ� ���� ����
//    //SessionManager(const SessionManager&) = delete;
//    //SessionManager& operator=(const SessionManager&) = delete;
//    };
//
//#endif // SESSION_MANAGER_H