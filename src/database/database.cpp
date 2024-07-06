/*
#include "database.h"
#include <QDebug>
void databaseInitialize()
{
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        db = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("stockDb");
        db.setUserName("user");
    }
    if (!db.open())
    {
        qDebug() << "Error: Failed to connect database." << db.lastError();
    }
    else
    {

    }
}


Database::Database(QObject *parent) : QObject(parent)
{
}

Database::~Database()
{
    closeDatabase();
}

bool Database::openDatabase(const QString &dbName)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);

    if (!db.open()) {
        qDebug() << "Failed to open database:" << db.lastError().text();
        return false;
    }

    QSqlQuery query;
    // Create users table
    query.exec("CREATE TABLE IF NOT EXISTS users ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "username TEXT, "
               "password TEXT, "
               "balance REAL)");

    // Create stocks table
    query.exec("CREATE TABLE IF NOT EXISTS stocks ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "symbol TEXT, "
               "name TEXT, "
               "price REAL)");
    //todo:Create order table

    return true;
}

void Database::closeDatabase()
{
    if (db.isOpen()) {
        db.close();
    }
}

// User operations
bool Database::addUser(const QString &username, const QString &password, double balance)
{
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password, balance) VALUES (?, ?, ?)");
    query.addBindValue(username);
    query.addBindValue(password);
    query.addBindValue(balance);

    if (!query.exec()) {
        qDebug() << "Failed to add user:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::removeUser(int userId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM users WHERE id = ?");
    query.addBindValue(userId);

    if (!query.exec()) {
        qDebug() << "Failed to remove user:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::updateUser(int userId, const QString &username, const QString &password, double balance)
{
    QSqlQuery query;
    query.prepare("UPDATE users SET username = ?, password = ?, balance = ? WHERE id = ?");
    query.addBindValue(username);
    query.addBindValue(password);
    query.addBindValue(balance);
    query.addBindValue(userId);

    if (!query.exec()) {
        qDebug() << "Failed to update user:" << query.lastError().text();
        return false;
    }
    return true;
}

QVariantList Database::getUser(int userId)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE id = ?");
    query.addBindValue(userId);

    if (!query.exec() || !query.next()) {
        qDebug() << "Failed to get user:" << query.lastError().text();
        return QVariantList();
    }

    QVariantList user;
    user << query.value("id") << query.value("username") << query.value("password") << query.value("balance");
    return user;
}

// Stock operations
bool Database::addStock(const QString &symbol, const QString &name, double price)
{
    QSqlQuery query;
    query.prepare("INSERT INTO stocks (symbol, name, price) VALUES (?, ?, ?)");
    query.addBindValue(symbol);
    query.addBindValue(name);
    query.addBindValue(price);

    if (!query.exec()) {
        qDebug() << "Failed to add stock:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::removeStock(int stockId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM stocks WHERE id = ?");
    query.addBindValue(stockId);

    if (!query.exec()) {
        qDebug() << "Failed to remove stock:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::updateStock(int stockId, const QString &symbol, const QString &name, double price)
{
    QSqlQuery query;
    query.prepare("UPDATE stocks SET symbol = ?, name = ?, price = ? WHERE id = ?");
    query.addBindValue(symbol);
    query.addBindValue(name);
    query.addBindValue(price);
    query.addBindValue(stockId);

    if (!query.exec()) {
        qDebug() << "Failed to update stock:" << query.lastError().text();
        return false;
    }
    return true;
}

QVariantList Database::getStock(int stockId)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM stocks WHERE id = ?");
    query.addBindValue(stockId);

    if (!query.exec() || !query.next()) {
        qDebug() << "Failed to get stock:" << query.lastError().text();
        return QVariantList();
    }

    QVariantList stock;
    stock << query.value("id") << query.value("symbol") << query.value("name") << query.value("price");
    return stock;
}
bool addOrder(const QString &symbol, const QString &name, double price)
{

}
bool removeOrder(int stockId)
{

}
bool updateOrder(int stockId, const QString &symbol, const QString &name, double price)
{

}
QVariantList getOrder(int stockId)
{

}

*/