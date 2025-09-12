#include "common/auth.hpp"
#include <iostream>

void Auth::setCredentials(const std::string& user, const std::string& pass) {
    username = user;
    password = pass;
}

bool Auth::login() {
    // 模擬登入流程
    if (username.empty() || password.empty()) {
        std::cerr << "Login failed: empty credentials" << std::endl;
        loggedIn = false;
        return false;
    }

    // 真實系統這裡會連線 API 或檢查資料庫
    std::cout << "User " << username << " logged in successfully." << std::endl;
    loggedIn = true;
    return true;
}

void Auth::logout() {
    if (loggedIn) {
        std::cout << "User " << username << " logged out." << std::endl;
        loggedIn = false;
    }
}

