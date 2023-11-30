#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <limits>
#include <random>

using namespace std;

//Estructura para leer el archivo de guardianes
typedef struct Guardianes
{
    string Nombre;
    int Nivel_De_Poder;
    string Maestro;
    string Ciudad;
}Guardianes_Juego;

//Estructura para el nodo de jerarquia de guardianes
struct Nodo_Guardianes
{
    Guardianes guardian;
    vector<Nodo_Guardianes*> aprendices;
};

//Estructura para leer el archivo de ciudades
typedef struct Ciudades
{
    string Ciudad;
    vector<string> Ciudades_Conectadas;
    vector<Guardianes> Guardianes_Ciudad;
    Guardianes Guardian_Maestro;
    Ciudades(string& nombre)
    {
        Ciudad = nombre;
    }
    Ciudades()
    {
        Ciudad = "";
    }
}Ciudades_Juegos;

//Funcion para encontrar la posicion del guardian para la jerarquia
int Posicion_Guardian (vector<Guardianes>&guardian , Guardianes& Nombre_guardian)
{
    for (int i = 0; i < guardian.size(); i++)
    {
        if ( guardian[i].Nombre == Nombre_guardian.Nombre)
        {
            return i;
        }
    }
    return -1;
}

//Funcion para buscar recursivamente el nodo del guardian en la jerarquia
Nodo_Guardianes* Buscar_Nodo(Nodo_Guardianes* nodo, const Guardianes& guardian)
{
    if (nodo->guardian.Nombre == guardian.Maestro)
    {
        return nodo;
    }
    else
    {
        for (Nodo_Guardianes* aprendiz : nodo->aprendices)
        {
            Nodo_Guardianes* buscado = Buscar_Nodo(aprendiz, guardian);
            if (buscado != nullptr)
            {
                return buscado;
            }
        }
    }

    return nullptr;
}

//Funcion para construir la jerarquia
void Jerarquia_Guardianes(vector<Guardianes>& guardianes, Nodo_Guardianes* root)
{
    for (const Guardianes& guardian : guardianes)
    {
        if (guardian.Maestro.empty())
        {
            Nodo_Guardianes* node = new Nodo_Guardianes{guardian};
            root->aprendices.push_back(node);
        }
        else
        {
            Nodo_Guardianes* masterNode = Buscar_Nodo(root, guardian);
            if (masterNode != nullptr)
            {
                Nodo_Guardianes* Nodo_Aprendiz = new Nodo_Guardianes{guardian};

                masterNode->aprendices.push_back(Nodo_Aprendiz);
            }
        }
    }
}

//Funcion para comparar el nivel de poder de un guardian
bool Comparar_Guardianes(const Guardianes& A, const Guardianes& B)
{
    return A.Nivel_De_Poder > B.Nivel_De_Poder;
}

//Funcion para imprimir la informacion de las ciudades
void ImprimirCiudades(const unordered_map<string, Ciudades>& Ciudad)
{
    cout << "Informacion de Ciudades:" << endl;
    for (const auto& pair : Ciudad)
    {
        const Ciudades& ciudad = pair.second;
        cout << "Ciudad: " << ciudad.Ciudad << endl;
        cout << "Conectada a: ";
        for (const string& conectada : ciudad.Ciudades_Conectadas)
        {
            cout << conectada << " ";
        }
        cout << endl;
        cout << "Guardian Maestro: " << ciudad.Guardian_Maestro.Nombre << endl;
        cout << "Guardianes de la Ciudad:" << endl;
        for (const Guardianes& guardian : ciudad.Guardianes_Ciudad)
        {
            cout << "- " << guardian.Nombre << ", Nivel de Poder: " << guardian.Nivel_De_Poder << endl;
        }
        cout << endl;
    }
}

//Funcion para ordenar guardianes por su nivel de poder
void OrdenarGuardianesPorNivelDePoder(vector<Guardianes>& guardianes)
{
    sort(guardianes.begin(), guardianes.end(), Comparar_Guardianes);
}

//Funcion para imprimir la informacion de los candidatos a guardianes
void ImprimirGuardianesCandidatos(const vector<Guardianes>& guardianes)
{
    cout << "Informacion de Candidatos:" << endl;
    for (const Guardianes& guardian : guardianes)
    {
        if (guardian.Nivel_De_Poder >= 90 && guardian.Nivel_De_Poder <= 99) {
            cout << "Nombre: " << guardian.Nombre << ", Nivel de Poder: " << guardian.Nivel_De_Poder << endl;
        }
    }
    cout << endl;
}

//Funcion para imprimir la informacion de los guardianes
void ImprimirGuardianes(const vector<Guardianes>& guardianes)
{
    cout << "Informacion de Guardianes:" << endl;
    for (const Guardianes& guardian : guardianes)
    {
        cout << "Nombre: " << guardian.Nombre << ", Nivel de Poder: " << guardian.Nivel_De_Poder
             << ", Maestro: " << guardian.Maestro << ", Ciudad: " << guardian.Ciudad << endl;
    }
    cout << endl;
}

//Funcion para imprimir la informacion del guardian selecionado
Guardianes ImprimirGuardian(const vector<Guardianes>& guardianes, const string& nombreGuardian)
{
    cout << "Informacion del Guardian '" << nombreGuardian << "':" << endl;
    
    for (const Guardianes& guardian : guardianes)
    {
        if (guardian.Nombre == nombreGuardian)
        {
            cout << "Nombre: " << guardian.Nombre << ", Nivel de Poder: " << guardian.Nivel_De_Poder
                      << ", Maestro: " << guardian.Maestro << ", Ciudad: " << guardian.Ciudad << std::endl;
            return guardian;
        }
    }
    cout << "Guardian no encontrado." << endl;
    cout << endl;
    return Guardianes{"", 0, "", ""};
}

//Funcion para simular una batalla entre guardian y algun rival local
void Batalla(const vector<Guardianes>& guardianes, const unordered_map<string, Ciudades>& ciudades, Guardianes& guardian)
{
    Guardianes guardian_rival;
    Ciudades ciudad_guardian;
    Ciudades ciudad_actual;
    string ciudad_destino;
    string rival;
    auto c_guardian = ciudades.find(guardian.Ciudad);
    if (c_guardian != ciudades.end())
    {
        ciudad_guardian = c_guardian->second;
        ciudad_actual = ciudad_guardian;
        cout << "Ciudad actual: " << ciudad_actual.Ciudad << endl;
    }
    else
    {
        cout << "Ciudad del Guardian no encontrada." << endl;
    }
    
    do
    {
        for(const string ciudad_conectada : ciudad_actual.Ciudades_Conectadas)
        {
            cout << ciudad_conectada << endl;
        }
        cout << "Seleccione ciudad de destino." << endl;
        getline(cin, ciudad_destino);
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        cout << ciudad_destino << endl;
        auto c_actual = ciudades.find(ciudad_destino);
        if (c_actual != ciudades.end())
        {
            ciudad_actual = c_actual->second;
            cout << "Ciudad nueva: " << ciudad_actual.Ciudad << endl;
        }
        else
        {
            cout << "Ciudad no encontrada." << endl;
        }

        cout << "Guardianes locales." << endl;
        for(const Guardianes guardianes : ciudad_actual.Guardianes_Ciudad)
        {
            cout << guardianes.Nombre << " Poder: " << guardianes.Nivel_De_Poder << endl;
        }
        cout << "Seleccione rival." << endl;
        getline(cin, rival);
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        for(const Guardianes guardianes : ciudad_actual.Guardianes_Ciudad)
        {
            if (guardianes.Nombre == rival)
            {
                guardian_rival = guardianes;
                break;
            }
        }

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, 6);
        int dado_resultado = dis(gen);

        if (dado_resultado < 5) {
            cout << "¡El rival ha ganado la batalla!" << endl;
            guardian.Nivel_De_Poder--;
        } 
        else 
        {
            cout << "¡Has ganado la batalla!" << endl;
            if(guardian_rival.Nombre == ciudad_actual.Guardian_Maestro.Nombre)
            {
                guardian.Nivel_De_Poder += 5;
            }
            else
            {
                guardian.Nivel_De_Poder += 3;
            }
            cout << guardian.Nivel_De_Poder << endl;
        }
        
    } while (guardian.Nivel_De_Poder < 90);

}

int main ()
{
    int Opcion;
    string Nombre_Guardian;
    Guardianes Guardian_Seleccionado;
    unordered_map<string, Ciudades> ciudades;
    ifstream CargaCiudades("./Ciudades_Juego.conf");
    vector<Guardianes> guardianes;
    Nodo_Guardianes* root = new Nodo_Guardianes{};

//Verificacion de que el archivo de ciudades se carga correctamente
    if (!CargaCiudades)
    {
        cout << "Hubo un error al cargar el archivo de ciudades" << endl;
        return 1;
    }
    string lineciudades;

    while (getline(CargaCiudades, lineciudades)) 
    {
        istringstream iss(lineciudades);
        string Ciudad_Nombre, Ciudad_Conectada;
        getline(iss, Ciudad_Nombre, ',');
        getline(iss, Ciudad_Conectada);

        if (ciudades.count(Ciudad_Nombre) == 0) 
        {
            ciudades[Ciudad_Nombre] = Ciudades(Ciudad_Nombre);
        }
            if (ciudades.count(Ciudad_Conectada) == 0) 
        {
            ciudades[Ciudad_Conectada] = Ciudades(Ciudad_Conectada);
        }

        ciudades[Ciudad_Nombre].Ciudades_Conectadas.push_back(Ciudad_Conectada);

        ciudades[Ciudad_Conectada].Ciudades_Conectadas.push_back(Ciudad_Nombre);
    }

    CargaCiudades.close();

    ifstream CargaGuardianes("./Guardianes_Juego.conf");
    if (!CargaGuardianes)
    {
        cout << "Hubo un error al cargar el archivo de ciudades" << endl;
        return 1;
    }

    string lineguardianes;
    
    while (getline(CargaGuardianes, lineguardianes))
    {
        Guardianes guardian;
        istringstream iss (lineguardianes);
        getline(iss, guardian.Nombre, ',');
        iss >> guardian.Nivel_De_Poder;
        iss.ignore();
        getline(iss, guardian.Maestro, ',');
        getline(iss, guardian.Ciudad);

        if (guardian.Nivel_De_Poder <= 100)
        {
            guardianes.push_back(guardian);

            if(ciudades.find(guardian.Ciudad) != ciudades.end())
            {
                Ciudades& ciudad = ciudades[guardian.Ciudad];
                if (ciudad.Guardian_Maestro.Maestro.empty() || guardian.Nivel_De_Poder > guardianes[Posicion_Guardian(guardianes, ciudad.Guardian_Maestro)].Nivel_De_Poder)
                {
                    ciudad.Guardian_Maestro = guardian;
                }
                ciudad.Guardianes_Ciudad.push_back(guardian);

                sort(ciudad.Guardianes_Ciudad.begin(), ciudad.Guardianes_Ciudad.end(),Comparar_Guardianes);
            }
        }
        else
        {
            //si el guardian tiene un nivel de poder mayor a 100 el poder queda en 100
            cout << "El guardian tiene un nivel de poder mayor a 100: " << guardian.Nombre << endl;
            cout << "El nivel del guardian fue cambiado a 100" << endl;
            guardian.Nivel_De_Poder == 100;
            guardianes.push_back(guardian);
        }
    }

    //do-while para el menu para que siga ejecutandose hasta que ingresen la opcion 5
    CargaGuardianes.close();
    do
    {
        cout << "***********************************************************" << endl;
        cout << "*     Porfavor ingrese una de las siguientes opciones     *" << endl;
        cout << "*        Para ver la lista de candidatos ingrese 1        *" << endl;
        cout << "*        Para ver y elegir a un guardian ingrese 2        *" << endl;
        cout << "*             Para conocer el reino ingrese 3             *" << endl;
        cout << "*          Para presenciar una batalla ingrese 4          *" << endl;
        cout << "*            Para salir del programa ingrese 5            *" << endl;
        cin >> Opcion;
        cout << "***********************************************************" << endl;

        //se llaman las funciones antes creadas
        switch (Opcion)
        {
            case 1:                 
                cout << "*             Esta es la lista de candidatos:             *" << endl;
                OrdenarGuardianesPorNivelDePoder(guardianes);
                ImprimirGuardianesCandidatos(guardianes);
                cout << "***********************************************************" << endl;
                break;
            case 2:
                cout << "*             Esta es la lista de Guardianes:             *" << endl;
                ImprimirGuardianes(guardianes);
                cout << "*           Por favor seleccione a un guardian            *" << endl;
                cin >> Nombre_Guardian;
                Guardian_Seleccionado = ImprimirGuardian(guardianes, Nombre_Guardian);
                cout << " Usted selecciono a " << Guardian_Seleccionado.Nombre << endl;
                cout << "***********************************************************" << endl;

                break;
            case 3:
                cout << "*           Estas son las ciudades disponibles:           *" << endl;
                ImprimirCiudades(ciudades);
                cout << "***********************************************************" << endl;
                break;
            case 4:
                cout << "*          Ahora estas presenciando una batalla           *" << endl;
                Batalla(guardianes, ciudades, Guardian_Seleccionado);
                cout << "***********************************************************" << endl;
                break;
        }
        
    }
    while (Opcion != 5);

    cout << "Gracias por jugar The Guardians Battles" << endl;
    exit(0);

    return 0;
}
