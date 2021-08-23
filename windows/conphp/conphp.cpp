#define CURL_STATICLIB
#include <iostream>
#include <string>
#include "curl.h"
#include "json/json.h"
#include "empleados.h"
#pragma warning(disable:4996) //para jsoncpp 

using namespace std;

//para recibir contenido de curl  
string contents = "";

static size_t my_write_obtener(void* buffer, size_t size, size_t nmemb, void* param);
void obtenerPorId();
void obtenerPorNombre(string nom); 
void menu(void);
void consulta(int n); 

//----------------MAIN---------------
int main()
{
	menu();

	printf("\n");
	return 0;
}

//-----------------RESPONSE Y PRESENTACION--------------------
static size_t my_write_obtener(void* buffer, size_t size, size_t nmemb, void* param)
{
	//convirtiendo lo recibido 
	int numbytes = size * nmemb;
	char lastchar = *((char*)buffer + numbytes - 1);
	*((char*)buffer + numbytes - 1) = '\0';
	contents.append((char*)buffer);
	contents.append(1, lastchar);
	*((char*)buffer + numbytes - 1) = lastchar;

	return size * nmemb;
}

//---------------OBTENER POR ID------------------
void obtenerPorId()
{
	cout << endl;

	//convirtiendo y parseando json
	Json::Reader reader;
	Json::Value obj;
	reader.parse(contents, obj);

	empleados *emp = new empleados; 

	if (contents == "\"datos-no-encontrados\"")
		cout << "datos no encontrados" << endl;
	else
	{
		emp->setId(atoi(obj[0]["id"].asCString()));
		emp->setNombre(obj[0]["nombre"].asCString());
	
		cout << "ID:\t" << emp->getIde() << endl; 
		cout << "NOMBRE:\t" << emp->getNombre() << endl; 
	}

	delete emp;
}

//---------------OBTENER POR NOMBRE------------------
void obtenerPorNombre(string nom)
{
	cout << endl;

	//convirtiendo y parseando json
	Json::Reader reader;
	Json::Value obj;
	reader.parse(contents, obj);

	empleados* emp = new empleados;

	if (contents == "\"sin-datos\"")
		cout << "sin datos" << endl;
	else
	{
		emp->setId(atoi(obj[0]["id"].asCString()));
		emp->setNombre(obj[0]["nombre"].asCString());

		cout << "ID:\t" << emp->getIde() << endl;
		cout << "NOMBRE:\t" << emp->getNombre() << endl;
	}

	delete emp;
}

void menu(void)
{
	int n;
	cout << "ingrese opcion: (1)Obtener empleados - (2)Guardar empleado " << endl;
	cin >> n; 

	switch (n)
	{
	case 1:
		consulta(n);
		break;
	default:
		cout << "no es opcion valida" << endl;
		break;
	}
}

//-----------------CONSULTAR A LA BD-------------------
void consulta(int n)
{
	char* cstr;
	string aux;
	CURL* curl;
	CURLcode res;
	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
	if (curl) {
		
		
		switch (n)
		{
		case 1:
		{
			int m;
			string idenom;
			cout << "Obtener por (1)Id - (2)Nombre: "; 
			cin >> m; 
			switch (m)
			{
			case 1:
				cout << "ingrese id: ";
				cin >> idenom;
				aux = "tipo=id&ide=" + idenom;

				cstr = new char[aux.length() + 1];
				strcpy_s(cstr, aux.length() + 1, aux.c_str());

				curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.1.16/pruebas/inicio.php");
				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, cstr);
				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write_obtener);
				
				res = curl_easy_perform(curl);

				obtenerPorId();
				break; 
			case 2:
				cout << "ingrese nombre: "; 
				cin >> idenom;
				obtenerPorNombre(idenom);
			default:
				break;
			}

			
			if (CURLE_OK != res)
			{
				std::cerr << "CURL error: " << res << '\n';
				break;
			}

			break;
		}
		default:
			break;
		}
		
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}
