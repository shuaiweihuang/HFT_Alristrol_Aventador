#pragma once
#include <string>

class Auth {
public:
    Auth() = default;

    // 設定帳號密碼或 token
    void setCredentials(const std::string& user, const std::string& pass);

    // 登入方法
    bool login();

    // 登出
    void logout();

private:
    std::string username;
    std::string password;
    bool loggedIn = false;
};

