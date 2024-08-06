#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void serializeData();
    void deserializeData();

private:
    QWidget* mainWidget;
    QVBoxLayout* mainLayout;
    QLineEdit* nameLineEdit;
    QLineEdit* idLineEdit;
    QLineEdit* emailLineEdit;
    QHBoxLayout* btnLayout;
    QPushButton* btnSerialize;
    QPushButton* btnDeserialize;
    QLabel* statusLabel;
};

#endif // MAINWINDOW_H
