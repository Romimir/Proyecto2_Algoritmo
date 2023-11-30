**The Guardians Battles**
Este programa es un juego de simulacion de batallas entre guardianes en diferentes ciudades. Cada guardian tiene su nombre, nivel de poder, maestro y la ciudad donde se ubican ademas de estar ordenados jerárquicamente.

~ Requisitos para ejecutar el programa

- Tener un compilador que admita el estándar C++
- Tener los siguientes archivos:
  - Ciudades_Juego.conf: Configuración de las ciudades y sus conexiones.
  - Guardianes_Juego.conf: Configuración de los guardianes, sus niveles de poder y ciudades asociadas.
    (Los archivos de configuración Ciudades_Juego.conf y Guardianes_Juego.conf deben seguir un formato específico para que el programa los lea correctamente.)

~ Instrucciones de compilación y ejecución

1. Clona el repositorio o descarga los archivos `TheGuandiansBattles.cpp`, `Ciudades_Juego.conf` y `Guardianes_Juego.conf`.
2. Abre una terminal y navega al directorio donde se encuentran los archivos.
3. Compila el programa con el siguiente comando: g++ -std=c++11 main.cpp -o guardians_battles
        y ejecuta el programa:
        ./guardians_battles
        Luego usa el programa
4. El programa presenta un menú interactivo con las siguientes opciones:

        Ver la lista de candidatos: Muestra una lista ordenada de guardianes candidatos.
        Ver y elegir a un guardián: Muestra la lista de todos los guardianes y permite seleccionar uno.
        Conocer el reino: Muestra información sobre las ciudades y sus conexiones, así como los guardianes asociados.
        Presenciar una batalla: Simula una batalla entre el guardián seleccionado y un rival local.
        Salir del programa: Finaliza la ejecución del programa.
Estructura del código
    El código está dividido en secciones que incluyen:

    Estructuras de datos para los guardianes y las ciudades.
    Funciones para la manipulación de datos y la simulación de batallas.
    Lectura de archivos de configuración para ciudades y guardianes.
    Menú interactivo en la función main.
    Notas adicionales
