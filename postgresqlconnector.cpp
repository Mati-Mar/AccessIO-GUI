#include "postgresqlconnector.h"

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

    db.setHostName(host);
    db.setPort(5432);
    db.setDatabaseName(databaseName);
    db.setUserName(username);
    db.setPassword(password);
}

PostgreSQLConnector::~PostgreSQLConnector()
{
    cerrarConexionBD();
}

/*    query->exec("INSERT INTO contacts(uid, nombre, apellido, edad, acceso, secret_pass, oficina_id, ubicacion)" +
                " VALUES(250, 'Anderson', 'Jane', DEFAULT);");*/

void PostgreSQLConnector::CreateUser(QString uid,QString Acceso,QString Nombre,QString Apellido,QString Edad,QString Oficina){
    if(!db.isOpen()){
        abrirConexionBD();
    }

    //QSqlQuery *query = new QSqlQuery(db);
    QSqlQuery *guardar_s2= new QSqlQuery(db);
    guardar_s2->prepare("INSERT INTO accessio.usuario (uid, nombre, apellido, acceso, secret_pass, oficina_id, ubicacion) "
                       "VALUES (:uid, :Nombre, :Apellido, :Acceso, :pass, :Oficina, :ubi)");


    guardar_s2->bindValue(":uid", uid);
    guardar_s2->bindValue(":Nombre", Nombre);
    guardar_s2->bindValue(":Apellido", Apellido);
    guardar_s2->bindValue(":edad", Edad.toInt());
    guardar_s2->bindValue(":Acceso", Acceso);
    guardar_s2->bindValue(":pass", "0000");
    guardar_s2->bindValue(":Oficina", Oficina);
    guardar_s2->bindValue(":ubi", "A");

    //query->exec("INSERT INTO " + this->getSchema() + ".usuario (uid, nombre, apellido, edad, acceso, secret_pass, oficina_id, ubicacion) VALUES('" + uid +"', '"+ Nombre +"', '"+ Apellido +"', 21, '" + Acceso+"', '0000', '" + Oficina + "', 'A');");

    //query->exec("INSERT INTO accessio.usuario (uid, nombre, apellido, edad, acceso, secret_pass, oficina_id, ubicacion)VALUES('uid', 'Nombre', 'Apellido', 12, 'Acceso', '0000', 'Oficina', 'A');");
    if(guardar_s2->exec( ))
    {
        qDebug()<<"13.Los datos del parte se han guardado en la Solicitud de Trabajo";
    }
    else
    {
        qDebug()<<"13.ERROR. Los datos del parte no se han guardado en la Solicitud de Trabajo";
        qDebug()<<"13.ERROR:"<<guardar_s2->lastError();
    }    cerrarConexionBD();

    return;
}

bool PostgreSQLConnector::existUserByUid(QString uid){

    if(!db.isOpen()){
        abrirConexionBD();
    }

    QSqlQuery *query = new QSqlQuery(db);

    query->exec("SELECT * FROM " + this->getSchema() + ".usuario WHERE uid='" + uid + "'");
    cerrarConexionBD();

    if(query->next()){
        return true; //Nombre más apellido
    }
    else
        return false;

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

bool PostgreSQLConnector::ExistOficinaId( QString OficinaId)
{
    if(!db.isOpen()){
        abrirConexionBD();
    }

    QSqlQuery *query = new QSqlQuery(db);

    query->exec("SELECT oficina_id FROM " + this->getSchema() + ".usuario WHERE oficina_id='" + OficinaId + "'");
    cerrarConexionBD();

    if(query->next()){
        return true; //Nombre más apellido
    }
    else
        return false;}


QString PostgreSQLConnector::getUsernameByUID(QString uid)
{
    if(!db.isOpen()){
        abrirConexionBD();
    }

    QSqlQuery *query = new QSqlQuery();

    query->exec("SELECT * FROM " + this->getSchema() + ".usuario WHERE uid='" + uid + "'");
    //TODO: Me parece que se podría poner nombre, apellido en lugar de *
    cerrarConexionBD();

    if(query->next()){
        return (query->value(2).toString()) + (query->value(3).toString());
    }
    else
        return "";
}
QString PostgreSQLConnector::getName(QString uid)
{
    if(!db.isOpen()){
        abrirConexionBD();
    }

    QSqlQuery *query = new QSqlQuery();

    query->exec("SELECT * FROM " + this->getSchema() + ".usuario WHERE uid='" + uid + "'");
    //TODO: Me parece que se podría poner nombre, apellido en lugar de *
    cerrarConexionBD();

    if(query->next()){
        return (query->value(2).toString());
    }
    else
        return "";
}
QString PostgreSQLConnector::getUsernameByOficina(QString oficina){
    if(!db.isOpen()){
        abrirConexionBD();
    }

    QSqlQuery *query = new QSqlQuery(db);

    query->exec("SELECT * FROM " + this->getSchema() + ".usuario WHERE oficina_id='" + oficina + "'");
    cerrarConexionBD();

    if(query->next()){
        return (query->value(2).toString()) + " " + (query->value(3).toString()); //Nombre más apellido
    }
    else
        return "";
}

void PostgreSQLConnector::setUsername(const QString &newUsername)
{
    username = newUsername;
}

QString PostgreSQLConnector::getPassword(QString oficinaId) { //Se podría cambiar el nombre a byOficinaID
    if(!db.isOpen()){
        abrirConexionBD();
    }

    QSqlQuery *query = new QSqlQuery(db);
    query->exec("SELECT secret_pass FROM " + this->getSchema() + ".usuario WHERE oficina_id='" + oficinaId + "'");
    cerrarConexionBD();

    if(query->next()){
        return query->value(0).toString();
    }
    else
        return "";
}

QString PostgreSQLConnector::getPasswordByUid(QString uid) { //Se podría cambiar el nombre a byOficinaID
    if(!db.isOpen()){
        abrirConexionBD();
    }

    QSqlQuery *query = new QSqlQuery(db);
    query->exec("SELECT * FROM " + this->getSchema() + ".usuario WHERE uid='" + uid + "'");
    //TODO: Acá en lugar de usar * se podría poner secret_pass y listo
    cerrarConexionBD();

    if(query->next()){
        return query->value(6).toString();
    }
    else
        return "";
}

void PostgreSQLConnector::setPasswordByUid(QString uid, QString pass) { //Se podría cambiar el nombre a byOficinaID
    if(!db.isOpen()){
        abrirConexionBD();
    }

    QSqlQuery *query = new QSqlQuery(db);
    query->exec("UPDATE " + this->getSchema() + ".usuario  SET secret_pass=" + pass +" WHERE uid='" + uid + "'");
    //TODO: Acá en lugar de usar * se podría poner secret_pass y listo
    cerrarConexionBD();

    return;
}
void PostgreSQLConnector::setPassword(const QString &newPassword)
{
    password = newPassword;
}

unsigned int PostgreSQLConnector::getUsuariosInRoom( QString room ) {

    if (!db.isOpen())
        abrirConexionBD();

    QSqlQuery *query = new QSqlQuery(db);
    unsigned int cantidadPersonas = 0;
    query->exec("SELECT * FROM " + this->getSchema() + ".usuario WHERE ubicacion = '" + room + "'" );

    while (query->next())
        cantidadPersonas++;
    return cantidadPersonas;
}

QSqlTableModel* PostgreSQLConnector::getModeloUsuarios(QObject *parent)
{
    //QSqlQuery *query = new QSqlQuery(db);
    //query->exec("SELECT * FROM " + this->getSchema() + ".usuario WHERE oficina='" + oficinaId + "'");

    QSqlTableModel *modelo = new QSqlTableModel(parent, db);
    modelo->setTable(this->getSchema() + ".usuario");
    modelo->select(); // Selecciona todos los registros
    return modelo;
}

QSqlTableModel* PostgreSQLConnector::getModeloUsuarioLocation(QObject *parent, QString nombre, QString apellido)
{
    if (!db.isOpen())
        abrirConexionBD();

    QSqlQuery *query = new QSqlQuery(db);
    QSqlTableModel *modelo = new QSqlTableModel(parent, db);
    QString uid = "usuario_uid='";
    modelo->setTable(this->getSchema() + ".usuario_location");

    query->exec("SELECT uid FROM " + this->getSchema() + ".usuario WHERE nombre='" + nombre + "' AND apellido='" + apellido + "'");
    if(query->next()){
        uid += query->value(0).toString();
    }
    uid += "'";
    modelo->setFilter(uid);
    modelo->sort(modelo->fieldIndex("hora"), Qt::SortOrder::AscendingOrder);
    modelo->select(); // Selecciona todos los registros
    return modelo;
}
