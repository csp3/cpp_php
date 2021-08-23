#include "empleados.h"

empleados::empleados()
{
	nombre = "";
	ide = 0;
}

empleados::~empleados()
{
	nombre = "";
	ide = 0;
}


std::string empleados::getNombre(void)
{
	return nombre;
}

int empleados::getIde(void)
{
	return ide;
}

std::string empleados::getApellidopaterno(void)
{
	return apellidopaterno;
}

std::string empleados::getFechaingreso(void)
{
	return fechaingreso;
}

float empleados::getSalario(void) 
{
	return salario;
}

void empleados::setNombre(std::string nom)
{
	nombre = nom;
}

void empleados::setId(int n)
{
	ide = n;
}
