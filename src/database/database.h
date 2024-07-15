#pragma once
#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QString>
#include <QVariantList>
#include <QObject>
#include <vector>
#include "../implementation/Account.h"
#include "../implementation/order.h"
#include "../implementation/Stock.h"
#include "../implementation/My_stock.h"
#include "../implementation/StockPrice.h"
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
    std::vector<int> getBotslist();

    // operate stocks' information
    bool addStock(const QString &symbol, const QString &name, double price);
    bool removeStock(int stockId);
    bool updateStock(int stockId, const QString &symbol, const QString &name, double price);
    QVariantList getStock(int stockId);
    std::vector<Stock> getStocksList();

    // operate orders' information
    int addOrder(int &operatorId, double price, int quantity,const QString &symbol, bool side);
    bool removeOrder(int orderId);
    bool updateOrder(int orderId, int &operatorId, double price, int quantity,const QString &symbol, bool side);
    QVariantList getOrder(int orderId);
    std::vector<Order> getOrdersList(QString symbol, bool side);
    std::vector<Order> getMyOrdersList(int userId);
    // operate users' stock
    bool addUserStock(int userId, const QString &symbol, const QString &name, int quantity);
    bool removeUserStock(int userId, const QString &symbol);
    bool updateUserStock(int userId, const QString &symbol, int quantity);
    QVariantList getUserStocks(int userId);
    std::vector<My_stock> getMyStock(int userId);
    int getStockQuantity(int userId, const QString &symbol);
    bool addStockPrice(const QString &symbol, double price, int &time);
    std::vector<StockPrice> getStockPrice(const QString &symbol);
    int getNewestTime();

private:
    QSqlDatabase db;
};
extern Database db;
