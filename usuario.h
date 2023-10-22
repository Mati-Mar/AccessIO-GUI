#ifndef USUARIO_H
#define USUARIO_H
#include <QString>
#include <QList>

class usuario
{
public:
    usuario(unsigned int newId,
            QString newNombre,
            QString newApellido,
            unsigned int newEdad);
    ~usuario();
    int getId() const;
    void setId(int newId);
    QString getNombre() const;
    void setNombre(const QString &newNombre);
    QString getApellido() const;
    void setApellido(const QString &newApellido);
    unsigned int getEdad() const;
    void setEdad(unsigned int newEdad);

private:
    int id;
    QString nombre;
    QString apellido;
    int edad;
    void save(QString nombre, QString apellido, unsigned int edad);
    usuario getUsuario();
    QList<usuario> getUsuarios();


};

#endif // USUARIO_H
