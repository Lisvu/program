#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QString>
#include <QTimer>

class GameEngine : public QObject
{
    Q_OBJECT

public:
    explicit GameEngine(QObject *parent = nullptr);
    ~GameEngine();

    void startGame();
    void swapGems(int row1, int col1, int row2, int col2);
    QString getGemAt(int row, int col);
    void updateScore(int points);
    void setScore(int newScore);

signals:
    void updateBoard();
    void scoreChanged(int newScore);

private:
    QString board[8][8];  // 游戏板
    int score;
    QTimer *m_timer;      // 动画定时器

    // Step 枚举定义
    enum class Step {
        None,
        Swap,
        Clear,
        Fall,
        Generate
    };


    Step m_currentStep;  // 当前的步骤（交换、消除、掉落等）
    int m_swapProgress;  // 交换动画进度（0 - 100）
    int m_row1, m_col1, m_row2, m_col2;  // 交换宝石的坐标
    int m_swapCount;

    // 游戏核心逻辑函数
    QString randomGemType();
    bool matchGems();
    bool checkMatch(int row, int col);
    void clearMatchedGems(int row, int col);
    void handleGemFalling();
    void updateBoardWithAnimation();
};

#endif // GAMEENGINE_H
