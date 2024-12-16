#ifndef SHOPMANAGER_H
#define SHOPMANAGER_H

#include <QString>
#include <QMap>

class ShopManager
{
public:
    ShopManager();
    ~ShopManager();

    void buyItem(const QString &itemName);  // 购买道具
    void useItem(const QString &itemName);  // 使用道具

private:
    QMap<QString, int> inventory;  // 玩家拥有的道具
};

#endif // SHOPMANAGER_H
