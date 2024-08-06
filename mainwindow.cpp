#include "person.pb.h"
#include <fstream>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    mainLayout = new QVBoxLayout(mainWidget);

    nameLineEdit = new QLineEdit(this);
    idLineEdit = new QLineEdit(this);
    emailLineEdit = new QLineEdit(this);

    mainLayout->addWidget(new QLabel("Name:", this));
    mainLayout->addWidget(nameLineEdit);
    mainLayout->addWidget(new QLabel("ID:", this));
    mainLayout->addWidget(idLineEdit);
    mainLayout->addWidget(new QLabel("Email:", this));
    mainLayout->addWidget(emailLineEdit);

    btnLayout = new QHBoxLayout();
    btnSerialize = new QPushButton("Serialize", this);
    btnDeserialize = new QPushButton("Deserialize", this);

    btnLayout->addWidget(btnSerialize);
    btnLayout->addWidget(btnDeserialize);

    mainLayout->addLayout(btnLayout);

    statusLabel = new QLabel("Status: Ready", this);
    mainLayout->addWidget(statusLabel);

    connect(btnSerialize, &QPushButton::clicked, this, &MainWindow::serializeData);
    connect(btnDeserialize, &QPushButton::clicked, this, &MainWindow::deserializeData);
}

MainWindow::~MainWindow()
{

}

void MainWindow::serializeData() {
    Person person;
    person.set_name(nameLineEdit->text().toStdString());
    person.set_id(idLineEdit->text().toInt());
    person.set_email(emailLineEdit->text().toStdString());

    std::string serialized_data;
    if (!person.SerializeToString(&serialized_data)) {
        statusLabel->setText("Failed to serialize data.");
        return;
    }

    QFile file("person.bin");
    if (!file.open(QIODevice::WriteOnly)) {
        statusLabel->setText("Failed to open file for writing.");
        return;
    }

    file.write(serialized_data.c_str(), serialized_data.size());
    file.close();

    statusLabel->setText("Data serialized successfully.");
}

void MainWindow::deserializeData() {

    QFile file("person.bin");
    if (!file.open(QIODevice::ReadOnly)) {
        statusLabel->setText("Failed to open file for reading.");
        return;
    }

    // Чтение данных из файла
    QByteArray serialized_data = file.readAll();
    file.close();

    // Создание объекта Person и десериализация данных
    Person person;
    if (!person.ParseFromString(serialized_data.toStdString())) {
        statusLabel->setText("Failed to parse data.");
        return;
    }

    QFile serialized_file("person.txt");
    if (serialized_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&serialized_file);
        out << "Name: " << QString::fromStdString(person.name()) << "\n";
        out << "ID: " << person.id() << "\n";
        out << "Email: " << QString::fromStdString(person.email()) << "\n";
        serialized_file.close();
    } else {
        statusLabel->setText("Failed to open text file for writing.");
        return;
    }

    statusLabel->setText("Data deserialized successfully.");
}
//void MainWindow::deserializeData() {
//    QFile file("person.bin");
//    if (!file.open(QIODevice::ReadOnly)) {
//        statusLabel->setText("Failed to open file for reading.");
//        return;
//    }

//    QByteArray serialized_data = file.readAll();
//    file.close();

//    Person person;
//    if (!person.ParseFromString(serialized_data.toStdString())) {
//        statusLabel->setText("Failed to parse data.");
//        return;
//    }

//    nameLineEdit->setText(QString::fromStdString(person.name()));
//    idLineEdit->setText(QString::number(person.id()));
//    emailLineEdit->setText(QString::fromStdString(person.email()));

//    statusLabel->setText("Data deserialized successfully.");
//}
