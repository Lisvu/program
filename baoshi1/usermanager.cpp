/**
 * UserManager（用户管理类）：负责用户的登录、注册、信息存储。
 * login()
 * register()
 * getUserData()
 *
 *
 */
#include "UserManager.h"
#include <QMessageBox>

UserManager::UserManager()
{
    // 预设一些用户数据
    users["user1"] = "password1";
    users["user2"] = "password2";

    userData["user1"] = "High Score: 5000";  // 假设用户1的高分为5000
    userData["user2"] = "High Score: 3000";  // 假设用户2的高分为3000
}

UserManager::~UserManager()
{
}

bool UserManager::login(const QString &username, const QString &password)
{
    if (users.contains(username) && users[username] == password) {
        return true;  // 登录成功
    }
    return false;  // 登录失败
}

bool UserManager::registerUser(const QString &username, const QString &password)
{
    if (!users.contains(username)) {
        users[username] = password;
        userData[username] = "High Score: 0";  // 新注册用户，初始高分为0
        return true;
    }
    return false;  // 用户名已存在
}

QString UserManager::getUserData(const QString &username)
{
    if (userData.contains(username)) {
        return userData[username];
    }
    return "没有找到用户数据";
}
