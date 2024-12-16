/**
 * ShopManager（商店管理类）：处理商店中道具的购买和使用。
 * buyItem()
 * useItem()
 */
#include "ShopManager.h"
#include <QMessageBox>

ShopManager::ShopManager()
{
    // 初始化道具
    inventory["Health Potion"] = 5;  // 例如: 假设玩家初始有5个生命药水
}

ShopManager::~ShopManager()
{
}

void ShopManager::buyItem(const QString &itemName)
{
    // 假设购买后，物品数量增加
    if (itemName == "Health Potion") {
        inventory["Health Potion"] += 1;
        QMessageBox::information(nullptr, "购买成功", "购买了1个生命药水");
    }
}

void ShopManager::useItem(const QString &itemName)
{
    // 使用道具时检查库存
    if (inventory.contains(itemName) && inventory[itemName] > 0) {
        inventory[itemName] -= 1;
        QMessageBox::information(nullptr, "使用成功", QString("使用了1个%1").arg(itemName));
    } else {
        QMessageBox::warning(nullptr, "库存不足", QString("没有足够的%1").arg(itemName));
    }
}
