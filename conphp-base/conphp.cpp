#define CURL_STATICLIB
#include <iostream>
#include <string>
#include "curl.h"
#include "json/json.h"
#pragma warning(disable:4996) //para jsoncpp 

using namespace std;

//para recibir contenido de curl  
string contents = "";
//

struct cliente
{
	string ruc = "";
	string dni = "";
	string nombre = "";
	string telefono = "";
	string email = "";
	string fechaingreso = "";
};

void presentacion(Json::Value obj); 
static size_t my_write(void* buffer, size_t size, size_t nmemb, void* param);

//----------------MAIN---------------
int main()
{
	CURL* curl;
	CURLcode res;
	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "http://localhost/pruebas/inicio.php"); 
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write);
		//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		res = curl_easy_perform(curl);
		if (CURLE_OK != res) {
			std::cerr << "CURL error: " << res << '\n';
		}

		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	
	printf("\n");
	return 0;
}

//---------------PRESENTACION------------------
void presentacion(Json::Value obj)
{
	struct cliente* clientes = (cliente*)malloc(sizeof(cliente)); 

	clientes->dni = obj[0]["dni"].asCString();
	clientes->ruc = obj[0]["ruc"].asCString();
	clientes->nombre = obj[0]["nombre"].asCString();
	clientes->fechaingreso = obj[0]["fechaingreso"].asCString();

	cout << "DNI:\t" << clientes->dni << endl;
	cout << "RUC:\t" << clientes->ruc << endl;
	cout << "NOMBRE:\t" << clientes->nombre << endl;

	free(clientes); 
}

//-----------------RESPONSE Y PRESENTACION--------------------
static size_t my_write(void* buffer, size_t size, size_t nmemb, void* param)
{
	//convirtiendo lo recibido 
	int numbytes = size * nmemb;
	char lastchar = *((char*)buffer + numbytes - 1);
	*((char*)buffer + numbytes - 1) = '\0';
	contents.append((char*)buffer);
	contents.append(1, lastchar);
	*((char*)buffer + numbytes - 1) = lastchar;

	//convirtiendo y parseando json
	Json::Reader reader;
	Json::Value obj;
	reader.parse(contents, obj);

	presentacion(obj); 

	return size * nmemb;
}
