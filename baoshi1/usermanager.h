#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QString>
#include <QMap>

class UserManager
{
public:
    UserManager();
    ~UserManager();

    bool login(const QString &username, const QString &password);  // 用户登录
    bool registerUser(const QString &username, const QString &password);  // 用户注册
    QString getUserData(const QString &username);  // 获取用户信息

private:
    QMap<QString, QString> users;  // 用户名和密码
    QMap<QString, QString> userData;  // 用户额外信息（如得分等）
};

#endif // USERMANAGER_H
