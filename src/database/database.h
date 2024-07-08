#pragma once
#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QString>
#include <QVariantList>
#include <QObject>
#include "../implementation/Account.h"
#include "../implementation/order.h"
#include "../implementation/Stock.h"
#include "../implementation/My_stock.h"
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
    int CheckUser(const QString &username, const QString &password);
    QVariantList getUser(int userId);

    // operate stocks' information
    bool addStock(const QString &symbol, const QString &name, double price);
    bool removeStock(int stockId);
    bool updateStock(int stockId, const QString &symbol, const QString &name, double price);
    My_stock *getMyStock(int userId);
    QVariantList getStock(int stockId);

    // operate orders' information
    bool addOrder(int orderId, QString &operatorId, double price, int quantity, QString &symbol, bool side);
    bool removeOrder(int orderId);
    bool updateOrder(int orderId, QString &operatorId, double price, int quantity, QString &symbol, bool side);
    QVariantList getOrder(int orderId);

    // operate users' stock
    bool addUserStock(int userId, const QString &symbol, const QString &name, int quantity);
    bool removeUserStock(int userId, const QString &symbol);
    bool updateUserStock(int userId, const QString &symbol, int quantity);
    QVariantList getUserStocks(int userId);

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
