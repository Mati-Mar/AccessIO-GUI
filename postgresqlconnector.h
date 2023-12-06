#ifndef POSTGRESQLCONNECTOR_H
#define POSTGRESQLCONNECTOR_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

//TODO: Se podría implementar un patrón Singleton para no tener que instanciar siempre esta clase.
//Una opcion que me gusta más es crearlo como un PostgreService y hacer como un método static la conexión a la base de datos
//Así se evitaría tener que crear la conexión mil veces. Parece una buena idea
class PostgreSQLConnector
{
public:
    PostgreSQLConnector(const QString& host,
                        const QString& databaseName,
                        const QString& schema,
                        const QString& username,
                        const QString& password);
    ~PostgreSQLConnector();
    bool abrirConexionBD();
    void cerrarConexionBD();
    QSqlQuery ejecutarQuery(const QString& query);
    QSqlError getError();
    const QString& getSchema();

private:
    QString hostname;
    QString databaseName;
    QString schema;
    QString username;
    QString password;
    QSqlDatabase db;

public:
    //DEBUG ONLY

    bool VerifyPass(QString pass, QString idOficina);
    bool VerifyUUID(QString UUID, QString LugarDeAcceso);


    QString getHostname() const;
    void setHostname(const QString &newHostname);
    QString getDatabaseName() const;
    void setDatabaseName(const QString &newDatabaseName);
    void setSchema(const QString &newSchema);

    QString getUsernameByOficina(QString Id);
    QString getUsernameById(QString Id);

    void setUsername(const QString &newUsername);
    QString getPassword(QString oficina);
    void setPassword(const QString &newPassword);
    bool isOpen();

};

#endif // POSTGRESQLCONNECTOR_H
