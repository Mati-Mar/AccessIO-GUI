#ifndef POSTGRESQLCONNECTOR_H
#define POSTGRESQLCONNECTOR_H

#include <QString>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

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
private:
    QString hostname;
    QString databaseName;
    QString schema;
    QString username;
    QString password;
    QSqlDatabase db;

public:
    bool VerifyPass(QString pass, QString idOficina);
    bool VerifyUUID(QString UUID, QString LugarDeAcceso);

    const QString& getSchema();
    QSqlError getError();

    QString getHostname() const;
    void setHostname(const QString &newHostname);
    QString getDatabaseName() const;
    void setDatabaseName(const QString &newDatabaseName);
    void setSchema(const QString &newSchema);

    QString getUsernameByOficina(QString Id);
    QString getUsernameByUID(QString Id);

    void setUsername(const QString &newUsername);
    QString getPassword(QString oficina);
    void setPassword(const QString &newPassword);
    bool isOpen();
    unsigned int getUsuariosInRoom( QString room );
    QSqlTableModel* getModeloUsuarios(QObject *parent = nullptr);
    QSqlTableModel* getModeloUsuarioLocation(QObject *parent, QString nombre, QString apellido);


};

#endif // POSTGRESQLCONNECTOR_H
