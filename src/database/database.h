#pragma once
#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QString>
#include <QVariantList>
#include <QObject>
class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    ~Database();

    bool openDatabase(const QString &dbName);
    void closeDatabase();

    // operate users' information
    int addUser(const QString &username, const QString &password, double balance);
    bool removeUser(int userId);
    bool updateUser(int userId, const QString &username, const QString &password, double balance);
    bool CheckUser(const QString &username, const QString &password);
    QVariantList getUser(int userId);

    // operate stocks' information
    bool addStock(const QString &symbol, const QString &name, double price);
    bool removeStock(int stockId);
    bool updateStock(int stockId, const QString &symbol, const QString &name, double price);
    QVariantList getStock(int stockId);

    // operate orders' information
    bool addOrder(int orderId, QString &operatorId, double price, int quantity, QString &symbol, bool side);
    bool removeOrder(int orderId);
    bool updateOrder(int orderId, QString &operatorId, double price, int quantity, QString &symbol, bool side);
    QVariantList getOrder(int orderId);

private:
    QSqlDatabase db;
};
extern Database db;
/*
 * 先声明一个Database对象，
 * QSqlDatabase db;
 * 调用openDatabase函数（指定一个数据库名stock之类的），对数据库操作完毕后，调用closeDatabase函数
 * /
 */