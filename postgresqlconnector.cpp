#include "postgresqlconnector.h"
//("localhost","AccessIO","postgres","accessio","root");

PostgreSQLConnector::PostgreSQLConnector(const QString& host,           //localhost
                                         const QString& databaseName,   //AccessIO
                                         const QString& username,       //postgres
                                         const QString& schema,         //accessio
                                         const QString& password)       //root
{
    this->hostname = host;
    this->databaseName = databaseName;
    this->username = username;
    this->password = password;
    this->schema = schema;
    if (QSqlDatabase::contains("accessio"))
    {
        QSqlDatabase::removeDatabase("accessio");
    }
    db = QSqlDatabase::addDatabase("QPSQL");

        db.setHostName("localhost");
        db.setPort(5432);
        db.setDatabaseName("accessio");
        db.setUserName("postgres");
        db.setPassword("root");
//    db.setHostName(host);
//    db.setPort(5432);
//    db.setDatabaseName(databaseName);
//    db.setUserName(username);
//    db.setPassword(password);
}

PostgreSQLConnector::~PostgreSQLConnector()
{
    cerrarConexionBD();
}

bool PostgreSQLConnector::abrirConexionBD()
{
    return db.open();
}
bool PostgreSQLConnector::isOpen()
{
    return db.isOpen();
}

void PostgreSQLConnector::cerrarConexionBD()
{

    QSqlDatabase::removeDatabase("accessio"); // correct

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

QString PostgreSQLConnector::getUsernameById(QString Id)
{
    if(!db.isOpen()){
        abrirConexionBD();
    }

    QSqlQuery *query = new QSqlQuery();

    query->exec("SELECT * FROM accessio.usuario WHERE uid='" + Id + "'");

    cerrarConexionBD();

    if(query->next()){
    return query->value(1).toString();
    }
    else
    return "";


}
QString PostgreSQLConnector::getUsernameByOficina(QString oficina){
    if(!db.isOpen()){
        abrirConexionBD();
    }

    QSqlQuery *query = new QSqlQuery(db);

    query->exec("SELECT * FROM accessio.usuario WHERE oficina='" + oficina + "'");

    query->next();
    cerrarConexionBD();

    if(query->next()){
        return query->value(1).toString();
    }
    else
        return "";}

void PostgreSQLConnector::setUsername(const QString &newUsername)
{
    username = newUsername;
        return;
}

QString PostgreSQLConnector::getPassword(QString oficina) {
    if(!db.isOpen()){
        abrirConexionBD();
    }

    QSqlQuery *query = new QSqlQuery(db);

    QString estring;
    estring = "SELECT * FROM accessio.usuario WHERE oficina='" + oficina + "'";
    query->exec(estring);

    cerrarConexionBD();

    if(query->next()){
        return query->value(3).toString();
    }
    else
        return "";}

void PostgreSQLConnector::setPassword(const QString &newPassword)
{
    password = newPassword;
}


