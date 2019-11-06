#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QGraphicsScene;   // 游戏发生的舞台
class QGraphicsView;    // 观察游戏舞台的组件
class GameController;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    ~MainWindow();

private:
    void initScene();
    void initSceneBackground();

    QGraphicsScene *scene;
    QGraphicsView *view;
    GameController *game;

private slots:
    void adjustViewSize();
};

#endif // MAINWINDOW_H
