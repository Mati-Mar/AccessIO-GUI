#include "postgresqlconnector.h"

PostgreSQLConnector::PostgreSQLConnector(const QString& host,
                                         const QString& databaseName,
                                         const QString& username,
                                         const QString& schema,
                                         const QString& password)
{
    this->hostname = host;
    this->databaseName = databaseName;
    this->username = username;
    this->password = password;
    this->schema = schema;

    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(host);
    db.setDatabaseName(databaseName);
    db.setUserName(username);
    db.setPassword(password);
}

PostgreSQLConnector::~PostgreSQLConnector()
{
    cerrarConexionBD();
}

bool PostgreSQLConnector::abrirConexionBD()
{
    return db.open();
}

void PostgreSQLConnector::cerrarConexionBD()
{
    db.close();
}

QSqlQuery PostgreSQLConnector::ejecutarQuery(const QString& query)
{
    QSqlQuery sqlQuery;
    sqlQuery.exec(query);
    return sqlQuery;
}

QSqlError PostgreSQLConnector::getError()
{
    return db.lastError();
}

const QString& PostgreSQLConnector::getSchema()
{
    return this->schema;
}

QString PostgreSQLConnector::getHostname() const
{
    return hostname;
}

void PostgreSQLConnector::setHostname(const QString &newHostname)
{
    hostname = newHostname;
}

QString PostgreSQLConnector::getDatabaseName() const
{
    return databaseName;
}

void PostgreSQLConnector::setDatabaseName(const QString &newDatabaseName)
{
    databaseName = newDatabaseName;
}

void PostgreSQLConnector::setSchema(const QString &newSchema)
{
    schema = newSchema;
}

QString PostgreSQLConnector::getUsername() const
{
    return username;
}

void PostgreSQLConnector::setUsername(const QString &newUsername)
{
    username = newUsername;
}

QString PostgreSQLConnector::getPassword() const
{
    return password;
}

void PostgreSQLConnector::setPassword(const QString &newPassword)
{
    password = newPassword;
}


