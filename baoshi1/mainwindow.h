#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // 游戏界面对象
    class GameScreen *gameScreen;

private slots:
    // 打开游戏界面
    void on_startGameButton_clicked();
};

#endif // MAINWINDOW_H
