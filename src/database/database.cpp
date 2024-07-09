#include "database.h"
#include <QDebug>
Database db;
Database::Database(QObject *parent) : QObject(parent)
{
    this->openDatabase("stock");
}

Database::~Database()
{
    closeDatabase();
}

bool Database::openDatabase(const QString &dbName)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);

    if (!db.open())
    {
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
    // Create orders table
    query.exec("CREATE TABLE IF NOT EXISTS orders("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "operator INT,"
               "price REAL,"
               "quantity INT"
               "symbol TEXT"
               "side INT");
    // Create user_stocks table
    query.exec("CREATE TABLE IF NOT EXISTS user_stocks ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "user_id INTEGER NOT NULL, "
               "symbol TEXT NOT NULL, "
               "name TEXT"
               "quantity INTEGER NOT NULL, "
               "FOREIGN KEY (user_id) REFERENCES users(id))");

    return true;
}

void Database::closeDatabase()
{
    if (db.isOpen())
    {
        db.close();
    }
}

// User operations
int Database::addUser(const QString &username, const QString &password, double balance)
{
    QSqlQuery query;
    // 检查是否有重复的用户名
    query.prepare("SELECT * FROM users WHERE username = ?");
    query.addBindValue(username);
    if (!query.exec() || query.next())
    {
        return -1;
    }
    query.prepare("INSERT INTO users (username, password, balance) VALUES (?, ?, ?)");
    query.addBindValue(username);
    query.addBindValue(password);
    query.addBindValue(balance);

    if (!query.exec())
    {
        qDebug() << "Failed to add user:" << query.lastError().text();
        return -1;
    }
    return query.lastInsertId().toInt();
}

bool Database::removeUser(int userId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM users WHERE id = ?");
    query.addBindValue(userId);

    if (!query.exec())
    {
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

    if (!query.exec())
    {
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

    if (!query.exec() || !query.next())
    {
        qDebug() << "Failed to get user:" << query.lastError().text();
        return QVariantList();
    }

    QVariantList user;
    user << query.value("id") << query.value("username") << query.value("password") << query.value("balance");
    return user;
}
int Database::CheckUser(const QString &username, const QString &password)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = ? AND password = ?");
    query.addBindValue(username);
    query.addBindValue(password);

    if (!query.exec() || !query.next())
    {
        return -1;
    }
    return query.value("id").toInt();
}
// Stock operations
bool Database::addStock(const QString &symbol, const QString &name, double price)
{
    QSqlQuery query;
    query.prepare("INSERT INTO stocks (symbol, name, price) VALUES (?, ?, ?)");
    query.addBindValue(symbol);
    query.addBindValue(name);
    query.addBindValue(price);

    if (!query.exec())
    {
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

    if (!query.exec())
    {
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

    if (!query.exec())
    {
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

    if (!query.exec() || !query.next())
    {
        qDebug() << "Failed to get stock:" << query.lastError().text();
        return QVariantList();
    }

    QVariantList stock;
    stock << query.value("id") << query.value("symbol") << query.value("name") << query.value("price");
    return stock;
}
int Database::addOrder(int &operatorId, double price, int quantity,const QString &symbol, bool side)
{
    QSqlQuery query;
    query.prepare("INSERT INTO orders (operator,price, quantity,symbol,side) VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(operatorId);
    query.addBindValue(price);
    query.addBindValue(quantity);
    query.addBindValue(symbol);
    query.addBindValue(side);

    if (!query.exec())
    {
        qDebug() << "Failed to add order:" << query.lastError().text();
        return -1;
    }
    return query.lastInsertId().toInt();
}
bool Database::removeOrder(int orderId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM orders WHERE id = ?");
    query.addBindValue(orderId);

    if (!query.exec())
    {
        qDebug() << "Failed to remove order:" << query.lastError().text();
        return false;
    }
    return true;
}
bool Database::updateOrder(int orderId, int &operatorId, double price, int quantity,const QString &symbol, bool side)
{
    QSqlQuery query;
    query.prepare("UPDATE orders SET operator = ?, price = ?, quantity = ?, symbol=?, side=? WHERE id = ?");
    query.addBindValue(operatorId);
    query.addBindValue(price);
    query.addBindValue(quantity);
    query.addBindValue(symbol);
    query.addBindValue(side);

    if (!query.exec())
    {
        qDebug() << "Failed to update stock:" << query.lastError().text();
        return false;
    }
    return true;
}
QVariantList Database::getOrder(int orderId)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM orders WHERE id = ?");
    query.addBindValue(orderId);

    if (!query.exec() || !query.next())
    {
        qDebug() << "Failed to get order:" << query.lastError().text();
        return QVariantList();
    }

    QVariantList order;
    order << query.value("id") << query.value("operator") << query.value("price") << query.value("quantity") << query.value("symbol") << query.value("side");
    return order;
}
bool Database::addUserStock(int userId, const QString &symbol, const QString &name, int quantity)
{
    QSqlQuery query;
    query.prepare("INSERT INTO user_stocks (user_id, symbol, name,quantity) VALUES (?, ?, ?, ?)");
    query.addBindValue(userId);
    query.addBindValue(symbol);
    query.addBindValue(name);
    query.addBindValue(quantity);

    if (!query.exec())
    {
        qDebug() << "Failed to add user stock:" << query.lastError().text();
        return false;
    }
    return true;
}
bool Database::removeUserStock(int userId, const QString &symbol)
{
    QSqlQuery query;
    query.prepare("DELETE FROM user_stocks WHERE user_id = ? AND symbol = ?");
    query.addBindValue(userId);
    query.addBindValue(symbol);

    if (!query.exec())
    {
        qDebug() << "Failed to remove user stock:" << query.lastError().text();
        return false;
    }
    return true;
}
bool Database::updateUserStock(int userId, const QString &symbol, int quantity)
{
    QSqlQuery query;
    query.prepare("UPDATE user_stocks SET quantity = ? WHERE user_id = ? AND symbol = ?");
    query.addBindValue(quantity);
    query.addBindValue(userId);
    query.addBindValue(symbol);
    if (!query.exec())
    {
        qDebug() << "Failed to update user stock:" << query.lastError().text();
        return false;
    }
    return true;
}
QVariantList Database::getUserStocks(int userId)
{
    QSqlQuery query;
    query.prepare("SELECT symbol,name, quantity FROM user_stocks WHERE user_id = ?");
    query.addBindValue(userId);

    if (!query.exec())
    {
        qDebug() << "Failed to fetch user stocks:" << query.lastError().text();
        return QVariantList();
    }

    QVariantList result;
    while (query.next())
    {
        QVariantMap stock;
        stock["symbol"] = query.value("symbol");
        stock["name"] = query.value("name");
        stock["quantity"] = query.value("quantity");
        result.append(stock);
    }

    return result;
    // result存储了userId对应用户持有的股票信息，result[0].toMap()["name"].toString();可以获取用户持有的第一支股票的名称
    //result[用户的第x支股票].toMap()[要查询的股票信息，symbol、name或者quantity].toInt()或者toString()取决于查询信息的种类
}
/*My_stock *getMyStock(int userId)
{
    // todo:
}*/
std::vector<My_stock> Database::getMyStock(int userId)
{
    QSqlQuery query;
    query.prepare("SELECT symbol, name, quantity FROM user_stocks WHERE user_id = ?");
    query.addBindValue(userId);
    if (!query.exec())
    {
        qDebug() << "Failed to fetch user stocks:" << query.lastError().text();
        return std::vector<My_stock>();
    }
    else
    {
        std::vector<My_stock> result;
        while (query.next())
        {
            My_stock stock(query.value("symbol").toString().toStdString(), query.value("quantity").toInt());
            result.push_back(stock);
        }
        return result;
    }
}
std::vector<Stock> Database::getStocksList()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM stocks");
    if (!query.exec())
    {
        qDebug() << "Failed to fetch stocks:" << query.lastError().text();
        return std::vector<Stock>();
    }
    else
    {
        std::vector<Stock> result;
        while (query.next())
        {
            Stock stock(query.value("symbol").toString().toStdString(), query.value("price").toDouble());
            result.push_back(stock);
        }
        return result;
    }
}
std::vector<Order> Database::getOrdersList(QString symbol, bool side)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM orders WHERE symbol = ? AND side = ?");
    query.addBindValue(symbol);
    query.addBindValue(side);
    if (!query.exec())
    {
        qDebug() << "Failed to fetch orders:" << query.lastError().text();
        return std::vector<Order>();
    }
    else
    {
        std::vector<Order> result;
        while (query.next())
        {
            Order order(query.value("id").toInt(), query.value("operator").toString().toStdString(), query.value("price").toDouble(), query.value("quantity").toInt(), query.value("symbol").toString().toStdString(), query.value("side").toBool());
            result.push_back(order);
        }
        return result;
    }
}