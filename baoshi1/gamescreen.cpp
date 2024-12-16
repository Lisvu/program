#include "gamescreen.h"
#include "ui_gamescreen.h"
#include "GameEngine.h"
#include <QPushButton>
#include <QMessageBox>
#include <QGridLayout>
#include <QPixmap>
#include <QPoint>

GameScreen::GameScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameScreen)
{
    ui->setupUi(this);

    // 设置整个页面大小为 800x600
    this->setFixedSize(900, 650);  // 设置窗口大小为800x600

    // 初始化UI组件
    gameEngine = new GameEngine(this);  // 实例化游戏引擎
    connect(gameEngine, &GameEngine::updateBoard, this, &GameScreen::updateBoard);
    connect(gameEngine, &GameEngine::updateScore, this, &GameScreen::updateScore);

    initBoard();  // 初始化游戏板

    connect(ui->shopButton, &QPushButton::clicked, this, &GameScreen::on_shopButton_clicked);
    connect(ui->exitButton, &QPushButton::clicked, this, &GameScreen::on_exitButton_clicked);


}

GameScreen::~GameScreen()
{
    delete ui;
}

void GameScreen::initBoard()
{
    // 创建并设置QGridLayout作为主布局
    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(0);  // 设置格子间距为0

    // 设置 QGridLayout 区域的大小为 480x480
    QWidget *boardWidget = new QWidget(this);
    boardWidget->setLayout(gridLayout);
    boardWidget->setFixedSize(480, 480);  // 设置布局区域大小为480x480
    boardWidget->move(410, 50);  // 将布局区域移到位置 (310, 10)

    // 初始化按钮数组
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            QPushButton *gemButton = new QPushButton(boardWidget);  // 将按钮设置在boardWidget中
            gemButton->setFixedSize(60, 60);  // 每个宝石按钮大小
            gridLayout->addWidget(gemButton, row, col);

            // 设置初始图片为随机宝石
            updateGemImage(gemButton, row, col);

            // 将按钮保存到数组中
            buttons[row][col] = gemButton;

            // 连接点击事件，交换宝石
            connect(gemButton, &QPushButton::clicked, [this, row, col](){ onGemClicked(row, col); });
        }
    }

    // 启动游戏
    gameEngine->startGame();
}

void GameScreen::updateGemImage(QPushButton *button, int row, int col)
{
    QString gemType = gameEngine->getGemAt(row, col);  // 获取宝石类型

    // 根据宝石类型加载对应的图片路径
    QString gemImagePath;
    if (gemType == "Gem1") {
        gemImagePath = ":/new/prefix1/image/1.bmp";  // 宝石1的图片路径
    } else if (gemType == "Gem2") {
        gemImagePath = ":/new/prefix1/image/2.bmp";  // 宝石2的图片路径
    } else if (gemType == "Gem3") {
        gemImagePath = ":/new/prefix1/image/3.bmp";  // 宝石3的图片路径
    } else if (gemType == "Gem4") {
        gemImagePath = ":/new/prefix1/image/4.bmp";  // 宝石4的图片路径
    }

    QPixmap pixmap(gemImagePath);  // 加载宝石图片
    button->setIcon(pixmap);
    button->setIconSize(pixmap.size());
}

void GameScreen::updateBoard()
{
    // 更新UI中的宝石矩阵显示
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            QPushButton *button = buttons[row][col];  // 获取按钮指针
            updateGemImage(button, row, col);  // 更新每个按钮的图标
        }
    }
}

void GameScreen::on_shopButton_clicked()
{
    // 打开商店界面
}

void GameScreen::on_exitButton_clicked()
{
    // 退出游戏
}

void GameScreen::onGemClicked(int row, int col)
{
    // 实现点击宝石的逻辑
    if (selectedGem.isNull()) {
        selectedGem = QPoint(row, col);  // 第一次点击，选择宝石
    } else {
        // 第二次点击，交换两个宝石
        gameEngine->swapGems(selectedGem.x(), selectedGem.y(), row, col);
        selectedGem = QPoint();  // 清空选择
    }
}
//在这里面展示当前分数
void GameScreen::updateScore(int newScore)
{
    // 更新分数显示
    scoreLabel->setText("Score: " + QString::number(newScore));  // 设置 QLabel 显示最新的分数
}


