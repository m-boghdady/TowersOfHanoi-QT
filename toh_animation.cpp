    #include "toh_animation.h"
    #include "ui_toh_animation.h"
    #include <iostream>


    TOH_Animation::TOH_Animation(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::TOH_Animation)
    {
        ui->setupUi(this);

        ui->Next->setEnabled(false);
        ui->previous->setEnabled(false);
        top_t1_x = ui->top_t1->x();
        top_t1_y = ui->top_t1->y();
        top_t2_x = ui->top_t2->x();
        top_t2_y = ui->top_t2->y();
        top_t3_x = ui->top_t3->x();
        top_t3_y = ui->top_t3->y();

        QLabel* D1 = ui->MovingDisk1;
        QLabel* D2 = ui->MovingDisk2;
        QLabel* D3 = ui->MovingDisk3;
        labelMap[1] = D1;
        labelMap[2] = D2;
        labelMap[3] = D3;

        QLabel* T1D1 = ui->label_d3;
        QLabel* T1D2 = ui->label_d2;
        QLabel* T1D3 = ui->label_d1;
        TargetAMap[3] = T1D1;
        TargetAMap[2] = T1D2;
        TargetAMap[1] = T1D3;

        QLabel* T2D1 = ui->label_d3_2;
        QLabel* T2D2 = ui->label_d2_2;
        QLabel* T2D3 = ui->label_d1_2;
        TargetBMap[3] = T2D1;
        TargetBMap[2] = T2D2;
        TargetBMap[1] = T2D3;

        QLabel* T3D1 = ui->label_d3_3;
        QLabel* T3D2 = ui->label_d2_3;
        QLabel* T3D3 = ui->label_d1_3;
        TargetCMap[3] = T3D1;
        TargetCMap[2] = T3D2;
        TargetCMap[1] = T3D3;


        }

    TOH_Animation::~TOH_Animation()
    {
        delete ui;
    }


    void TOH_Animation::MoveDisk(const QString& currentTower, const QString& targetTower)
    {

        // Create a property animation for the appropriate labels' geometry
        QLabel* currentLabel = nullptr;
        QLabel* targetLabel = nullptr;

        if (currentTower == "A")
        {
                currentLabel = labelMap[stackA.top()];
        }
        else if (currentTower == "B")
        {
                currentLabel = labelMap[stackB.top()];
        }
        else if (currentTower == "C")
        {
                currentLabel = labelMap[stackC.top()];
        }
        else
        {
            qDebug() << "Invalid current tower name: " << currentTower;
            return;
        }

        if (targetTower == "A")
        {
            if(stackA.empty()){
                targetLabel = TargetAMap[1];
            }
            else
            {
                targetLabel = TargetAMap[stackA.size()+1];
            }
        }
        else if (targetTower == "B")
        {
            if(stackB.empty()){
                targetLabel = TargetBMap[1];
            }
            else
            {
                targetLabel = TargetBMap[stackB.size()+1];
            }
        }
        else if (targetTower == "C")
        {
            if(stackC.empty()){
                targetLabel = TargetCMap[1];
            }
            else
            {
                targetLabel = TargetCMap[stackC.size()+1];
            }
        }
        else
        {
            qDebug() << "Invalid target tower name: " << targetTower;
            return;
        }



        // Calculate the target position
        int targetX = targetLabel->geometry().x();
        int targetY = targetLabel->geometry().y();

        // Create the property animation for the label's geometry
        QPropertyAnimation* animation = new QPropertyAnimation(currentLabel, "pos");
        animation->setDuration(1000);  // Animation duration in milliseconds

        // Calculate the first and second points based on the current and target towers
        QPoint firstPoint;
        QPoint secondPoint;

        if (currentTower == "A" && targetTower == "B")
        {
            firstPoint.setX(top_t1_x);
            firstPoint.setY(top_t1_y);
            secondPoint.setX(top_t2_x);
            secondPoint.setY(top_t2_y);
        }
        else if (currentTower == "A" && targetTower == "C")
        {
            firstPoint.setX(top_t1_x);
            firstPoint.setY(top_t1_y);
            secondPoint.setX(top_t3_x);
            secondPoint.setY(top_t3_y);
        }
        else if (currentTower == "B" && targetTower == "A")
        {
            firstPoint.setX(top_t2_x);
            firstPoint.setY(top_t2_y);
            secondPoint.setX(top_t1_x);
            secondPoint.setY(top_t1_y);
        }
        else if (currentTower == "B" && targetTower == "C")
        {
            firstPoint.setX(top_t2_x);
            firstPoint.setY(top_t2_y);
            secondPoint.setX(top_t3_x);
            secondPoint.setY(top_t3_y);
        }
        else if (currentTower == "C" && targetTower == "A")
        {
            firstPoint.setX(top_t3_x);
            firstPoint.setY(top_t3_y);
            secondPoint.setX(top_t1_x);
            secondPoint.setY(top_t1_y);
        }
        else if (currentTower == "C" && targetTower == "B")
        {
            firstPoint.setX(top_t3_x);
            firstPoint.setY(top_t3_y);
            secondPoint.setX(top_t2_x);
            secondPoint.setY(top_t2_y);
        }
        else
        {
            // Handle the case when the towers are the same or unrecognized tower names
            // You can add your own logic here or display an error message
            return;
        }

        // Set up the animation keyframes
        animation->setKeyValueAt(0, currentLabel->pos());        // Starting point
        animation->setKeyValueAt(0.3, firstPoint);               // First intermediate point
        animation->setKeyValueAt(0.6, secondPoint);              // Second intermediate point
        animation->setKeyValueAt(1, QPoint(targetX, targetY));   // Final target point

        // Start the animation
        animation->start();



    }



    void TOH_Animation::on_start_clicked()
    {

        // Read the target and current tower values from line edits
        QString targetTowerText = ui->lineEdit_target->text();
        QString currentTowerText = ui->lineEdit_current->text();

        // Validate the inputs as characters 'A', 'B', or 'C'
        if (targetTowerText.length() != 1 || currentTowerText.length() != 1 ||
            !QStringList({"A", "B", "C"}).contains(targetTowerText) ||
            !QStringList({"A", "B", "C"}).contains(currentTowerText) || targetTowerText == currentTowerText)
        {
            QMessageBox::critical(this, "Invalid Input", "Please enter valid characters 'A', 'B', or 'C' for target and current towers.");
            return;
        }

        // Convert the inputs to uppercase
        QString targetTower = targetTowerText.toUpper().at(0);
        QString currentTower = currentTowerText.toUpper().at(0);

        ui->start->setEnabled(false);


        // Initialize the stacks

        QPixmap Disk1(":/Images/Disk1.png");
        QPixmap Disk2(":/Images/Disk2.png");
        QPixmap Disk3(":/Images/Disk3.png");

        // Assign disks to the current tower's stack
        if (currentTower == "A")
        {
            stackA.push(3);
            stackA.push(2);
            stackA.push(1);

            ui->MovingDisk3->move(ui->label_d1->geometry().x(), ui->label_d1->geometry().y());
            ui->MovingDisk2->move(ui->label_d2->geometry().x(), ui->label_d2->geometry().y());
            ui->MovingDisk1->move(ui->label_d3->geometry().x(), ui->label_d3->geometry().y());

            ui->MovingDisk3->setPixmap(Disk1);
            ui->MovingDisk2->setPixmap(Disk2);
            ui->MovingDisk1->setPixmap(Disk3);
        }
        else if (currentTower == "B")
        {
            stackB.push(3);
            stackB.push(2);
            stackB.push(1);

            ui->MovingDisk3->move(ui->label_d1_2->geometry().x(), ui->label_d1_2->geometry().y());
            ui->MovingDisk2->move(ui->label_d2_2->geometry().x(), ui->label_d2_2->geometry().y());
            ui->MovingDisk1->move(ui->label_d3_2->geometry().x(), ui->label_d3_2->geometry().y());

            ui->MovingDisk3->setPixmap(Disk1);
            ui->MovingDisk2->setPixmap(Disk2);
            ui->MovingDisk1->setPixmap(Disk3);
        }
        else if (currentTower == "C")
        {

            stackC.push(3);
            stackC.push(2);
            stackC.push(1);

            ui->MovingDisk3->move(ui->label_d1_3->geometry().x(), ui->label_d1_3->geometry().y());
            ui->MovingDisk2->move(ui->label_d2_3->geometry().x(), ui->label_d2_3->geometry().y());
            ui->MovingDisk1->move(ui->label_d3_3->geometry().x(), ui->label_d3_3->geometry().y());

            ui->MovingDisk3->setPixmap(Disk1);
            ui->MovingDisk2->setPixmap(Disk2);
            ui->MovingDisk1->setPixmap(Disk3);
        }

        currentMoveIndex=1;
        QStringList Towers = {"A", "B", "C"};
        target=targetTower;
        current=currentTower;
        Towers.removeAll(targetTowerText);
        Towers.removeAll(currentTowerText);
        Auxillary = Towers.at(0);  // Calculationg Auxillary

        ui->Next->setEnabled(true);
        ui->previous->setEnabled(false);
    }


    stack<int>* TOH_Animation::getStack(const QString& rodName)
    {
        if (rodName == "A")
            return &stackA;
        else if (rodName == "B")
            return &stackB;
        else if (rodName == "C")
            return &stackC;
        else
            throw runtime_error("Invalid rod name: " + rodName.toStdString());
    }

    void TOH_Animation::moveDisk(const QString current, const QString target)
    {
        stack<int>* sourceStackPtr = getStack(current);
        stack<int>* destStackPtr = getStack(target);


        if (destStackPtr->empty() ||((!sourceStackPtr->empty()) && sourceStackPtr->top() < destStackPtr->top()))
        {
            MoveDisk(current, target);
            destStackPtr->push(sourceStackPtr->top());
            sourceStackPtr->pop();
            QString text = QString::number(currentMoveIndex);
            ui->lineEdit_4->setText(text);
        }
        else
        {
            moveDisk(target, current);
        }
    }



    void TOH_Animation::on_Next_clicked()
    {
        QString Cur = current;
        QString Aux = Auxillary;
        QString targ = target;

        if (currentMoveIndex <= 7) {
            if (currentMoveIndex % 3 == 0) {
                moveDisk(Aux, targ);
            } else if (currentMoveIndex % 3 == 1) {
                moveDisk(Cur, targ);
            } else {
                moveDisk(Cur, Aux);
            }
            currentMoveIndex++;
        }

        if (currentMoveIndex > 7){
         ui->Next->setEnabled(false);
        }
        else
          ui->Next->setEnabled(true);

        if (currentMoveIndex>1){
          ui->previous->setEnabled(true);
        }
          else
              ui->previous->setEnabled(false);
    }


    void TOH_Animation::on_previous_clicked()
    {
        if (currentMoveIndex > 1) {
            currentMoveIndex--;
            QString Cur = current;
            QString Aux = Auxillary;
            QString targ = target;

            if (currentMoveIndex % 3 == 0) {
                moveDisk(targ, Aux);
            } else if (currentMoveIndex % 3 == 1) {
                moveDisk(targ, Cur);
            } else {
                moveDisk(Aux, Cur);
            }
        }

        if (currentMoveIndex > 7){
            ui->Next->setEnabled(false);
        }
        else
            ui->Next->setEnabled(true);

        if (currentMoveIndex>1){
            ui->previous->setEnabled(true);
        }
        else
            ui->previous->setEnabled(false);
    }

    void TOH_Animation::on_Reset_clicked()
    {
        // Reset the animation or perform any necessary actions
        QString Cur = current;
        QString Aux = Auxillary;
        QString targ = target;

        while (!stackA.empty())
            stackA.pop();
        while (!stackB.empty())
            stackB.pop();
        while (!stackC.empty())
            stackC.pop();

        ui->MovingDisk3->move(ui->label_d1->geometry().x(), ui->label_d1->geometry().y());
        ui->MovingDisk2->move(ui->label_d2->geometry().x(), ui->label_d2->geometry().y());
        ui->MovingDisk1->move(ui->label_d3->geometry().x(), ui->label_d3->geometry().y());

        if (Cur == "A") {
            stackA.push(3);
            stackA.push(2);
            stackA.push(1);

            ui->MovingDisk3->setPixmap(QPixmap(":/Images/Disk1.png"));
            ui->MovingDisk2->setPixmap(QPixmap(":/Images/Disk2.png"));
            ui->MovingDisk1->setPixmap(QPixmap(":/Images/Disk3.png"));
        } else if (Cur == "B") {
            stackB.push(3);
            stackB.push(2);
            stackB.push(1);

            ui->MovingDisk3->setPixmap(QPixmap(":/Images/Disk1.png"));
            ui->MovingDisk2->setPixmap(QPixmap(":/Images/Disk2.png"));
            ui->MovingDisk1->setPixmap(QPixmap(":/Images/Disk3.png"));
        } else if (Cur == "C") {
            stackC.push(3);
            stackC.push(2);
            stackC.push(1);

            ui->MovingDisk3->setPixmap(QPixmap(":/Images/Disk1.png"));
            ui->MovingDisk2->setPixmap(QPixmap(":/Images/Disk2.png"));
            ui->MovingDisk1->setPixmap(QPixmap(":/Images/Disk3.png"));
        }

        currentMoveIndex = 1;
        ui->lineEdit_4->clear();
    }




    void TOH_Animation::on_clear_clicked()
    {
        // Clear the stacks and reset the animation state
        stackA = stack<int>();
        stackB = stack<int>();
        stackC = stack<int>();

        // Reset the disk positions
        ui->MovingDisk3->move(ui->label_d1->geometry().x(), ui->label_d1->geometry().y());
        ui->MovingDisk2->move(ui->label_d2->geometry().x(), ui->label_d2->geometry().y());
        ui->MovingDisk1->move(ui->label_d3->geometry().x(), ui->label_d3->geometry().y());

        // Clear the disk pixmaps
        ui->MovingDisk3->clear();
        ui->MovingDisk2->clear();
        ui->MovingDisk1->clear();

        // Reset the move index
        currentMoveIndex = 1;
        ui->lineEdit_current->clear();
        ui->lineEdit_target->clear();
        ui->lineEdit_4->clear();

        // Enable the start button
        ui->start->setEnabled(true);

        // Disable the next and previous buttons
        ui->Next->setEnabled(false);
        ui->previous->setEnabled(false);
    }


