#include "usuario.h"

usuario::usuario(   unsigned int newId,
                    QString newNombre,
                    QString newApellido,
                    unsigned int newEdad)
{
    this->id = newId;
    this->nombre = newNombre;
    this->apellido = newApellido;
    this->edad = newEdad;
}

usuario::~usuario()
{

}

int usuario::getId() const
{
    return id;
}

void usuario::setId(int newId)
{
    id = newId;
}

QString usuario::getNombre() const
{
    return nombre;
}

void usuario::setNombre(const QString &newNombre)
{
    nombre = newNombre;
}

QString usuario::getApellido() const
{
    return apellido;
}

void usuario::setApellido(const QString &newApellido)
{
    apellido = newApellido;
}

unsigned int usuario::getEdad() const
{
    return edad;
}

void usuario::setEdad(unsigned int newEdad)
{
    edad = newEdad;
}

void usuario::save(QString nombre, QString apellido, unsigned int edad)
{

}

usuario usuario::getUsuario()
{

}

QList<usuario> usuario::getUsuarios()
{

}
