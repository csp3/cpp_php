//#pragma once
#include <string>

class empleados
{
protected:
	std::string nombre = "";
	int ide = 0;
	std::string apellidopaterno = "";
	std::string fechaingreso = "";
	float salario = 0;

public:	
	empleados();
	~empleados();

	std::string getNombre(void) ;
	int getIde(void);
	std::string getApellidopaterno(void);
	std::string getFechaingreso(void);
	float getSalario(void);

	void setNombre(std::string nom);
	void setId(int n); 
};

//------

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
