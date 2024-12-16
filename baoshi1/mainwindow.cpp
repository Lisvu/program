#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamescreen.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);  // 设置主窗口的UI界面



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startGameButton_clicked()
{
    // 初始化GameScreen对象
    gameScreen = new GameScreen();

    // 打开游戏界面
    gameScreen->show();  // 显示游戏界面
    this->hide();        // 隐藏主窗口（可以选择是否隐藏主窗口）
}

