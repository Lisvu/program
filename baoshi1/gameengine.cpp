#include "GameEngine.h"
#include <QRandomGenerator>
#include <QTimer>
#include <QDebug>

GameEngine::GameEngine(QObject *parent)
    : QObject(parent),
    score(0),
    m_timer(new QTimer(this)),
    m_currentStep(Step::None),
    m_swapProgress(0),  // 添加交换动画的进度控制
    m_swapCount(0) // 新增交换计数器
{
    // 初始化宝石矩阵
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            board[row][col] = randomGemType();
        }
    }

    // 设置定时器，用于动画效果
    connect(m_timer, &QTimer::timeout, this, &GameEngine::updateBoardWithAnimation);
    m_timer->setInterval(100);  // 每次动画帧间隔200毫秒
}

GameEngine::~GameEngine() {}

void GameEngine::startGame()
{
    score = 0;
    emit updateBoard();  // 初始更新UI
}

QString GameEngine::randomGemType()
{
    QStringList gemTypes = {"Gem1", "Gem2", "Gem3", "Gem4"};
    return gemTypes[QRandomGenerator::global()->bounded(4)];
}

QString GameEngine::getGemAt(int row, int col)
{
    return board[row][col];
}

void GameEngine::swapGems(int row1, int col1, int row2, int col2)
{
    // 记录交换的坐标
    m_row1 = row1;
    m_col1 = col1;
    m_row2 = row2;
    m_col2 = col2;

    // 交换宝石并暂时不检查匹配，等待动画进行
    QString temp = board[row1][col1];
    board[row1][col1] = board[row2][col2];
    board[row2][col2] = temp;

    // 进行动画时，不直接检查是否匹配
    m_currentStep = Step::Swap;  // 设置当前步骤为交换动画
    m_swapProgress = 0;  // 重置交换动画进度
    m_swapCount++;  // 交换次数增加
    m_timer->start();  // 启动定时器，开始交换动画
}

bool GameEngine::matchGems()
{
    bool matched = false;

    do {
        matched = false;
        // 检查并消除行或列上的匹配宝石
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                // 只在该位置有匹配宝石时清除
                if (checkMatch(row, col)) {
                    clearMatchedGems(row, col);
                    matched = true;
                }
            }
        }

        // 如果有消除，处理下落
        if (matched) {
            handleGemFalling();
        }

    } while (matched); // 如果消除了匹配的宝石，继续检查是否有新的匹配

    return matched;
}

bool GameEngine::checkMatch(int row, int col)
{
    // 横向匹配检查
    if (col + 2 < 8 && board[row][col] == board[row][col + 1] && board[row][col] == board[row][col + 2]) {
        return true;
    }
    // 纵向匹配检查
    if (row + 2 < 8 && board[row][col] == board[row + 1][col] && board[row][col] == board[row + 2][col]) {
        return true;
    }
    return false;
}

void GameEngine::clearMatchedGems(int row, int col)
{
    // 横向检查并消除大于3个连续的宝石
    // 从当前宝石开始，检查右侧连续相同的宝石
    QString gem = board[row][col];
    QVector<QPair<int, int>> matchedGems;
    matchedGems.append(qMakePair(row, col));  // 当前宝石加入匹配列表

    // 横向检查
    for (int i = col + 1; i < 8 && board[row][i] == gem; ++i) {
        matchedGems.append(qMakePair(row, i));
    }
    // 如果有3个及以上连续宝石
    if (matchedGems.size() >= 3) {
        for (auto &gemPos : matchedGems) {
            board[gemPos.first][gemPos.second] = "Empty";
        }
        updateScore(matchedGems.size() * 1);  // 根据消除的宝石数量加分
    }

    matchedGems.clear();  // 清空匹配的宝石列表

    // 纵向检查并消除大于3个连续的宝石
    matchedGems.append(qMakePair(row, col));  // 当前宝石加入匹配列表

    // 纵向检查
    for (int i = row + 1; i < 8 && board[i][col] == gem; ++i) {
        matchedGems.append(qMakePair(i, col));
    }

    // 如果有3个及以上连续宝石
    if (matchedGems.size() >= 3) {
        for (auto &gemPos : matchedGems) {
            board[gemPos.first][gemPos.second] = "Empty";
        }
        updateScore(matchedGems.size() * 1);  // 根据消除的宝石数量加分
    }
}

void GameEngine::handleGemFalling()
{
    // 向下掉落的算法，处理空位
    for (int col = 0; col < 8; ++col) {
        for (int row = 7; row >= 0; --row) {
            if (board[row][col] == "Empty") {
                // 从上方查找非空的宝石
                for (int above = row - 1; above >= 0; --above) {
                    if (board[above][col] != "Empty") {
                        // 将上方的宝石下移到当前空位
                        board[row][col] = board[above][col];
                        board[above][col] = "Empty";
                        break;
                    }
                }
            }
        }
    }

    // 生成新的宝石填充空位
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (board[row][col] == "Empty") {
                board[row][col] = randomGemType();  // 随机生成新的宝石
            }
        }
    }

    // 更新UI显示
    emit updateBoard();
}

void GameEngine::updateBoardWithAnimation()
{
    switch (m_currentStep) {
    case Step::Swap:
        // 逐步交换宝石
        m_swapProgress += 10;  // 每次增加10%的动画进度
        if (m_swapProgress >= 100) {
            // 交换完成，进入下一步
            if (matchGems()) {
                // 如果交换后有匹配的宝石，继续消除并下落
                m_currentStep = Step::Clear;
            } else {
                // 否则，交换回来，继续进行第二次交换
                if (m_swapCount < 2) {
                    // 执行第二次交换
                    m_currentStep = Step::Swap;
                    m_swapCount++;
                    m_timer->start();
                } else {
                    // 执行完两次交换后，恢复原状态
                    QString temp = board[m_row1][m_col1];
                    board[m_row1][m_col1] = board[m_row2][m_col2];
                    board[m_row2][m_col2] = temp;
                    m_currentStep = Step::None;
                    m_swapCount = 0;  // 重置交换计数器
                    emit updateBoard();  // 完成交换，更新UI
                    m_timer->stop();
                }
            }
        }
        break;

    case Step::Clear:
        // 执行消除动画
        matchGems();  // 消除匹配的宝石
        m_currentStep = Step::Fall;  // 切换到掉落步骤
        break;

    case Step::Fall:
        // 执行掉落动画
        handleGemFalling();
        m_currentStep = Step::Generate;  // 切换到生成步骤
        break;

    case Step::Generate:
        // 执行生成新宝石动画
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                if (board[row][col] == "Empty") {
                    board[row][col] = randomGemType();
                }
            }
        }
        m_timer->stop();  // 停止定时器
        emit updateBoard();  // 完成动画，更新UI
        break;

    case Step::None:
        // 没有进行中的动画
        break;
    }

    emit updateBoard();  // 每个步骤后更新UI
}

void GameEngine::updateScore(int points)
{
    score += points;
    qDebug() << "当前分数: " << score;  // 更新控制台显示的分数

    // 这里可以将分数更新到UI中，例如通过信号发送更新分数的请求
    emit scoreChanged(score);
}
