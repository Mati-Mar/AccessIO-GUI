#ifndef POSTGRESQLCONNECTOR_H
#define POSTGRESQLCONNECTOR_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

#include <QDebug>

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
    void setPasswordByUid(QString uid, QString pass);//Se podría cambiar el nombre a byOficinaID
    QString getPasswordByUid(QString uid); //Se podría cambiar el nombre a byOficinaID
    QString getOficinaByUUid(QString uid);
    QString getAccessByUid(QString UID);

    void setUsername(const QString &newUsername);
    QString getPassword(QString oficina);
    void setPassword(const QString &newPassword);
    bool isOpen();
    bool existUserByUid(QString uid);
    QString     getName(QString uid);
    QString     getUbicacionByUid(QString uid);
    QString     setUbicacionByUid(QString uid,QString ubic);
    void deleteUserByUid(QString uid);


    void     CreateUser(QString uid,QString Acceso,QString Nombre,QString Apellido,QString Edad,QString Oficina);

    unsigned int getUsuariosInRoom( QString room );
    QSqlTableModel* getModeloUsuarios(QObject *parent = nullptr);
    QSqlTableModel* getModeloUsuarioLocation(QObject *parent, QString nombre, QString apellido);
    bool ExistOficinaId( QString OficinaId);
    void setMovimientosUsuario(QString uid , QString ubicacion);

};

#endif // POSTGRESQLCONNECTOR_H
