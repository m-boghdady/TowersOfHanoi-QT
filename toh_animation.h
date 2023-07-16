#ifndef TOH_ANIMATION_H
#define TOH_ANIMATION_H

#include <QMainWindow>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QMessageBox>
#include <stack>
#include <map>
#include <sstream>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class TOH_Animation; }
QT_END_NAMESPACE


class TOH_Animation : public QMainWindow
{
    Q_OBJECT

public:
    TOH_Animation(QWidget *parent = nullptr);
    ~TOH_Animation();


private slots:
    void on_start_clicked();
    void on_Next_clicked();
    void on_Reset_clicked();
    void on_previous_clicked();
    void MoveDisk(const QString& currentTower, const QString& targetTower);
    void moveDisk(const QString current, const QString target);

    stack<int>* getStack(const QString& rodName);
      /*  void on_Reset_clicked();
    void on_previous_clicked();*/



    void on_clear_clicked();

private:

    Ui::TOH_Animation *ui;
    int currentMoveIndex;
    QString current;
    QString Auxillary;
    QString target;
    map<int, QLabel*> labelMap;
    map<int, QLabel*> TargetAMap;
    map<int, QLabel*> TargetBMap;
    map<int, QLabel*> TargetCMap;
    stack<int> stackA;
    stack<int> stackB;
    stack<int> stackC;

    int top_t1_x;
    int top_t1_y;
    int top_t2_x;
    int top_t2_y;
    int top_t3_x;
    int top_t3_y;
};

#endif // TOH_ANIMATION_H
