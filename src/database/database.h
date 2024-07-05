#pragma once
#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QString>
#include <QVariantList>
#include <QObject>
/*
QSqlDatabase db;//database
class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    ~Database();

    bool openDatabase(const QString &dbName);
    void closeDatabase();

    // operate users' information
    bool addUser(const QString &username, const QString &password, double balance);
    bool removeUser(int userId);
    bool updateUser(int userId, const QString &username, const QString &password, double balance);
    QVariantList getUser(int userId);

    // operate stocks' information
    bool addStock(const QString &symbol, const QString &name, double price);
    bool removeStock(int stockId);
    bool updateStock(int stockId, const QString &symbol, const QString &name, double price);
    QVariantList getStock(int stockId);

private:
    QSqlDatabase db;
};*/