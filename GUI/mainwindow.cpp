#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ui_dialog.h"
#include "ui_dialog_2.h"
#include "dialog.h"
#include "dialog_2.h"
#include <fstream>
#include <iostream>
#include <QMessageBox>
#include <QFile>
#include <limits>
bool permlvl_3;
int num;
std::string efName;
std::string elName;
std::string eName;
std::string eSalary;
std::string eBonus;
std::string eBuilding;
std::string eOffice;
std::string eJob;
std::string decrypt_eName;
std::string decrypt_eSalary;
std::string decrypt_eBonus;
std::string decrypt_eBuilding;
std::string decrypt_eOffice;
std::string decrypt_eJob;
int key = 20;

char CODEX[] = { '0', '1', '2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h',
'i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E',
'F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','!','#',
'$','%','&','(',')','*','+',',',' ','-','.','/',':',';','<','=','>','?','@','[',']', '^',
'_','`','{', '|', '}','~' };

int find(char a[], int len, char find) {
    for (int i = 0; i < len; i++) {
        if (a[i] == find) {
            return i;
        }
    }
    return -1;
}
std::string encrypt(std::string s, int n) {
    int index = s.size();
    int x;
    for (int i = 0; i < index; i++) {
        x = find(CODEX, sizeof(CODEX), s[i]);
        s[i] = CODEX[(x + n) % sizeof(CODEX)];
    }
    return s;
}
std::string decrypt(std::string s, int n) {
    int index = s.size();
    int x;
    for (int i = 0; i < index; i++) {
        x = find(CODEX, sizeof(CODEX), s[i]);
        s[i] = CODEX[(sizeof(CODEX)+(x-n)) % sizeof(CODEX)];
    }
    return s;
}
class Employee {
public:
    int id;
    std::string firstName;
    std::string lastName;
    int permLevel;

    Employee(int id, std::string fName, std::string lName, int pl = 1) {
        this->id = id;
        firstName = fName;
        lastName = lName;
        permLevel = pl;
    }

    int getId() {
        return id;
    }

    std::string getFullName() {
        std::string fullname = firstName + " " + lastName;
        return fullname;
    }


    void setFirsttName(std::string fName) {
        firstName = fName;
    }

    void setLastName(std::string lName) {
        lastName = lName;
    }

    int getPermission() {
        return permLevel;
    }

    void setPermission(int p) {
        permLevel = p;
    }

};

class EmployeeLogin : public Employee {
    int id;
    std::string username;
    std::string password;
public:
    EmployeeLogin(int id, std::string fName, std::string lName, int p, std::string uName, std::string pWord) : Employee(id, fName, lName, p) {
        this->id = id;
        username = uName;
        password = pWord;
    }
    std::string getUsername() {
        return username;
    }
    std::string getPassword() {
        return password;
    }
    void setUsername(std::string newUsername) {
        username = newUsername;
    }
    void setPassword(std::string newPassword) {
        password = newPassword;
    }



};

class EmployeeInfo : public Employee {
    int id;
    int salary;
    int bonus;
    std::string name;
    std::string building;
    std::string office_loation;
    std::string jobTitle;
public:
    EmployeeInfo(int id, std::string fname, std::string lname, int plevel, int s, int b, std::string bdg, std::string ol, std::string jt) : Employee(id, fname, lname, plevel) {
        this->id = id;
        salary = s;
        bonus = b;
        name = fname + " " + lname;
        building = bdg;
        office_loation = ol;
        jobTitle = jt;
    };

  /*  void printInfo() {
        std:: cout << "DISPLAYING EMPLOYEE INFORMATION\n" << "EmployeeId: " << id << "\nFull Name: " << this->getFullName() << "\nPermission Level: " << this->getPermission() << "\nSalary: " << salary
             << "\nBonus: " << bonus << "\nBuilding Location: " << building << "\nOffice Location: " << office_loation << "\nJob Title: " << jobTitle << endl;
    }*/
    std::string getName(){
        return name;
    }
    int getSalary() {
        return salary;
    }

    int getBonus() {
        return bonus;
    }

    std::string getBuilding() {
        return building;
    }

    std::string getOfficeLocation() {
        return office_loation;
    }

    std::string getJobTitle() {
        return jobTitle;
    }

    void setSalary(int s) {
        salary = s;
    }

    void setBonus(int b) {
        bonus = b;
    }

    void setBuilding(std::string newBuilding) {
        building = newBuilding;
    }

    void setOfficeLocation(std::string ol) {
        office_loation = ol;
    }

    void setJobTitle(std::string jt) {
        jobTitle = jt;
    }



};




static std::ifstream& go_to_line(std::ifstream& stream, unsigned int line) {
    stream.seekg(0, std::ios::beg);
    for (int i = 0; i < line - 1; ++i)
        stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return stream;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}



EmployeeLogin el[] = {
        EmployeeLogin(1, "John", "Smith", 3, "jsmith", "123abc456" ),
        EmployeeLogin(2, "Josh", "Wurtenberg", 3, "jwurtenberg", "654cba321")
};

EmployeeInfo ei[] = {
        EmployeeInfo(1, "John", "Smith", 1, 60000, 10000, "Library West", "210G", "Information Technology Specialist"),
        EmployeeInfo(2, "Josh", "Wurtenberg", 3, 60000, 10000, "Library West", "210H", "Senior Developer")
};
void MainWindow::on_pushButton_clicked()
{


    QString u = ui->lineEdit->text();
    QString p = ui->lineEdit_2->text();
    std::string uInput = u.toLocal8Bit().constData();
    std::string pInput = p.toLocal8Bit().constData();
    bool login = false;
for(int i = 0; i < 2; i++){
    if(((uInput == el[i].getUsername()) && (pInput == el[i].getPassword()))){
        QMessageBox::information(this, "Login", "Login information correct.");
        login = true;
        std::string eName = ei[i].getName();
        int ePerm = ei[i].getPermission();
        int eSalary = ei[i].getSalary();
        int eBonus = ei[i].getBonus();
        std::string eBuilding = ei[i].getBuilding();
        std::string eOffice = ei[i].getOfficeLocation();
        std::string eJob = ei[i].getJobTitle();
        QString employeeName = QString::fromStdString(eName);
        QString employeeSalary = QLocale().toString(eSalary);
        QString employeeBonus = QLocale().toString(eBonus);
        QString employeeBuilding = QString::fromStdString(eBuilding);
        QString employeeOffice = QString::fromStdString(eOffice);
        QString employeeJob = QString::fromStdString(eJob);
        if(ePerm == 3) {permlvl_3 = true;} else { permlvl_3 = false;}
        if(ePerm >= 2) {
            dialog2 = new Dialog_2(this);
            QString e1Name = QString::fromStdString(ei[0].getName());
            QString e2Name = QString::fromStdString(ei[1].getName());
            dialog2->ui->label->setText(e1Name);
            dialog2->ui->label_2->setText(e2Name);
            dialog2->show();
            return;
        } else{
            dialog = new Dialog(this);
            dialog->ui->label->setText(employeeName);
            dialog->ui->label_3->setText(employeeSalary);
            dialog->ui->label_4->setText(employeeBonus);
            dialog->ui->label_5->setText(employeeBuilding);
            dialog->ui->label_6->setText(employeeOffice);
            dialog->ui->label_7->setText(employeeJob);
            dialog->show();
        }
    }
}
    if(!login){
       QMessageBox::warning(this, "Login", "Login information incorrect.");
   }
}
void Dialog_2::on_pushButton_clicked(){
    std::ifstream john("john.txt");
    if (!john.is_open()) {
        std::cout << "error opening file" << std::endl;
        return;
    }
    num = 2;
    std::getline(go_to_line(john, 1), eName, '\n');
    std::getline(go_to_line(john, 2), eSalary, '\n');
    std::getline(go_to_line(john, 3), eBonus, '\n');
    std::getline(go_to_line(john, 4), eBuilding, '\n');
    std::getline(go_to_line(john, 5), eOffice, '\n');
    std::getline(go_to_line(john, 6), eJob, '\n');



    decrypt_eName = decrypt(eName,key);
    decrypt_eSalary = decrypt(eSalary,key);
    decrypt_eBonus = decrypt(eBonus,key);
    decrypt_eBuilding = decrypt(eBuilding,key);
    decrypt_eOffice = decrypt(eOffice,key);
    decrypt_eJob = decrypt(eJob,key);
    QString employeeName = QString::fromStdString(decrypt_eName);
    QString employeeSalary = QString::fromStdString(decrypt_eSalary);
    QString employeeBonus = QString::fromStdString(decrypt_eBonus);
    QString employeeBuilding = QString::fromStdString(decrypt_eBuilding);
    QString employeeOffice = QString::fromStdString(decrypt_eOffice);
    QString employeeJob = QString::fromStdString(decrypt_eJob);
    newDialog = new Dialog(this);
    newDialog->ui->label->setText(employeeName);
    newDialog->ui->label_3->setText(employeeSalary);
    newDialog->ui->label_4->setText(employeeBonus);
    newDialog->ui->label_5->setText(employeeBuilding);
    newDialog->ui->label_6->setText(employeeOffice);
    newDialog->ui->label_7->setText(employeeJob);
    newDialog->show();
}

void Dialog_2::on_pushButton_2_clicked(){
    std::ifstream josh("joshua.txt");
    if (!josh.is_open()) {
        std::cout << "error opening file" << std::endl;
        return;
    }
    num = 1;
    std::getline(go_to_line(josh, 1), eName, '\n');
    std::getline(go_to_line(josh, 2), eSalary, '\n');
    std::getline(go_to_line(josh, 3), eBonus, '\n');
    std::getline(go_to_line(josh, 4), eBuilding, '\n');
    std::getline(go_to_line(josh, 5), eOffice, '\n');
    std::getline(go_to_line(josh, 6), eJob, '\n');
    decrypt_eName = decrypt(eName,key);
    decrypt_eSalary = decrypt(eSalary,key);
    decrypt_eBonus = decrypt(eBonus,key);
    decrypt_eBuilding = decrypt(eBuilding,key);
    decrypt_eOffice = decrypt(eOffice,key);
    decrypt_eJob = decrypt(eJob,key);
    QString employeeName = QString::fromStdString(decrypt_eName);
    QString employeeSalary = QString::fromStdString(decrypt_eSalary);
    QString employeeBonus = QString::fromStdString(decrypt_eBonus);
    QString employeeBuilding = QString::fromStdString(decrypt_eBuilding);
    QString employeeOffice = QString::fromStdString(decrypt_eOffice);
    QString employeeJob = QString::fromStdString(decrypt_eJob);
    newDialog = new Dialog(this);
    newDialog->ui->label->setText(employeeName);
    newDialog->ui->label_3->setText(employeeSalary);
    newDialog->ui->label_4->setText(employeeBonus);
    newDialog->ui->label_5->setText(employeeBuilding);
    newDialog->ui->label_6->setText(employeeOffice);
    newDialog->ui->label_7->setText(employeeJob);
    newDialog->show();

}

void Dialog::on_pushButton_clicked(){
    std::ofstream file;
    std::ofstream audit("audit_log.txt", std::ios::app);
    if(num == 1){
        file.open("joshua.txt", std::ios::trunc);
    } else if(num == 2){
        file.open("john.txt", std::ios::trunc);
    }
    if(permlvl_3){
        file << encrypt(ui->lineEdit->text().toStdString(), key) << "\n";
        audit << "Changed " << eName << " to " << encrypt(ui->lineEdit->text().toStdString(), key) << "\n";
        file << encrypt(ui->lineEdit_2->text().toStdString(), key) << "\n";
        audit << "Changed " << eSalary << " to " << encrypt(ui->lineEdit_2->text().toStdString(), key) << "\n";
        file << encrypt(ui->lineEdit_3->text().toStdString(), key) << "\n";
        audit << "Changed " << eBonus << " to " << encrypt(ui->lineEdit_3->text().toStdString(), key) << "\n";
        file << encrypt(ui->lineEdit_4->text().toStdString(), key) << "\n";
        audit << "Changed " << eBuilding << " to " << encrypt(ui->lineEdit_4->text().toStdString(), key) << "\n";
        file << encrypt(ui->lineEdit_5->text().toStdString(), key) << "\n";
        audit << "Changed " << eOffice << " to " << encrypt(ui->lineEdit_5->text().toStdString(), key) << "\n";
        file << encrypt(ui->lineEdit_6->text().toStdString(), key) << "\n";
        audit << "Changed " << eJob << " to " << encrypt(ui->lineEdit_6->text().toStdString(), key) << "\n";
        QMessageBox::information(this, "Admin", "Data updated successfully.");
        return;
    } else{
        QMessageBox::warning(this, "Admin", "You do not have permission to change employee data.");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
