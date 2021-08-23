#pragma once
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
