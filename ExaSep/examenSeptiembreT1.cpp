/*
 * Autor del trabajo: Ruben Rodriguez Esteban
 * NIP: 737215
 */

/* 
 * Fichero examenSep.cc que almacena un programa que constituye una solución al trabajo
 * planteado en el examen práctico de PROG1 celebrado el 7 de septiembre de 2018.
 */
 
#include <iostream>

using namespace std;

// Máximo número de letras que pueden llegar a integrar una secuencia de tipo SL
const int NUM_MAX_LETRAS = 100;

/*
 * Un dato de tipo SL permite representar una secuencia de letras mayúsculas
 * de longitud menor o igual que NUM_MAX_LETRAS
 */
struct SL {
    private:
        // Estructura interna de un dato de tipo SL
        char cadenaLetras[NUM_MAX_LETRAS];
		int letrasTotales;
    public:
        // Funciones para gestionar datos de tipo SL
        friend void definir (SL& sec, const char cadena[]);
        friend void concatenar (SL& sec, const SL& anyadido);
        friend void insertar (SL& sec, const char c);
        friend void ordenar (SL& sec);
        friend void mostrar (const SL& sec);
};

/*
 * Pre: <letras> almacena una cadena de caracteres todos los cuales son letras mayúsculas.
 *      El número de caracteres de la cadena ha de ser menor o igual que NUM_MAX_LETRAS
 * Post: Ha asignado a <sec> la secuencia de letras mayúsculas almacenada en <letras>,
 *       respetando su posición en <letras>
 * Ejemplo: Tras ejecutar definir(sec, "ABCABCZYX"), <sec> almacena la secuencia de 
 *          caracteres ABCABCZYX
 */
void definir (SL& sec, const char letras[]) {
	// La cadena inicialmente no posee ninguna letra
    sec.letrasTotales = 0;
	int i = 0;
	while ((sec.letrasTotales <= NUM_MAX_LETRAS - 1) && (letras[i] != '\0')){
		sec.cadenaLetras[sec.letrasTotales] = letras[i];
		i = i + 1;
		sec.letrasTotales++;
	}
	sec.cadenaLetras[sec.letrasTotales] = '\0';
}

/*
 * Pre: <sec> y <anyadida> almacenan dos secuencias de letras mayúsculas. La suma  
 *      de las longitudes de ambas secuencias es menor o igual que NUM_MAX_LETRAS
 * Post: <sec> almacena la secuencia de letras mayúsculas resultante de concatenar
 *       la secuencia almacenada inicialmente en <sec> seguida de la secuencia 
 *       almacenada inicialmente en <anyadida>
 * Ejemplo: Sea PEREZ la secuencia que almacena <sec1> y sea GALDOS la secuencia que 
 *          almacena <sec2>. Tras invocar la ejecución de concatenar(sec1,sec2) entonces
 *          <sec1> almacenará la secuencia PEREZGALDOS
 */
void concatenar (SL& sec, const SL& anyadida) {
	int i = 0;
	// Se verifica si la cadena puede o no concatenarse
    if (sec.letrasTotales < NUM_MAX_LETRAS){
		bool llena = false;
		// Se pueden añadir caracteres a la cadena
		// pero se debe determinar si podemos añadir todos
		while (anyadida.cadenaLetras[i] != '\0' && !llena){
			// No se excede la capacidad maxima y todavia podemos añadir caracteres
			sec.cadenaLetras[i + sec.letrasTotales] = anyadida.cadenaLetras[i];
			i = i + 1;
			// Verificacion de si se ha llenado la cadena
			// tras introducir el ultimo caracter
			if (sec.letrasTotales + i == NUM_MAX_LETRAS){
				llena = true;
			}
		}
	}
	// Las cadenas se han concatenado correcatamente
	// Se inserta el caracter nulo como caracter final de la
	// nueva cadena resultante
	sec.cadenaLetras[sec.letrasTotales + i] = '\0';
	// Actualizacion del total de letras que tiene ahora la cadena
	sec.letrasTotales = sec.letrasTotales + i;
}


/*
 * Pre: <sec> almacena una secuencia de letras mayúsculas ordenadas alfabéticamente
 *      y el valor de <c> es el de una letra mayúscula. La longitud de la secuencia
 *      almacenada en <sec> es inferior a NUM_MAX_LETRAS
 * Post: <sec> almacena una secuencia de letras mayúsculas ordenadas alfabéticamente
 *       de longitud una unidad mayor que la longitud de la secuencia que almacenaba 
 *       inicialmente. En la nueva secuencia almacenada en <sec> forman parte todas 
 *       las letras de su secuencia inicial a las que se ha añadido un ejemplar de
 *       la letra <c>
 * Ejemplos: Sea ABCDEF la secuencia que almacena <sec>. Tras invocar la ejecución de
 *       insertar(sec,'C') entonces <sec> almacenará ABCCDEF
 *       Sea ABCDEF la secuencia que almacena <sec>. Tras invocar la ejecución de
 *       insertar(sec,'M') entonces <sec> almacenará ABCDEFM
 *       Sea ABCXYZ la secuencia que almacena <sec>. Tras invocar la ejecución de
 *       insertar(sec,'H') entonces <sec> almacenará ABCHXYZ
 */
void insertar (SL& sec, const char c) {
	// Se verifica si se puede añadir nuevos caracteres a la cadena
    if (sec.letrasTotales < NUM_MAX_LETRAS){
		int i = 0;
		bool hallado = false;
		// Obtencion del ascii de la letra a introducir
		int asciiLetraNueva = c -'A';
		// Busqueda de la primera letra de la palabra que es mayor que c
		while (!hallado && sec.cadenaLetras[i] != '\0'){
			// Obtencion del ascii de la letra actual
			int asciiLetraActual = sec.cadenaLetras[i] - 'A';
			if (asciiLetraActual >= asciiLetraNueva){
				// Si el ascii de la actual es mayor que la que queremos introducir
				// hemos encontrado el caracter
				hallado = true;
				// Desplazamos todas las letrad siguientes a la derecha
				// para dejar espacio para la letra c
				for (int j = sec.letrasTotales - 1; j >= i; j--){
					sec.cadenaLetras[j + 1] = sec.cadenaLetras[j];
				}
				// Introduccion de la letra c en la posicion correcta
				sec.cadenaLetras[i] = c;
			}
			else{
				// La letra con ascii mayor a c no se ha encontrado todavia
				i = i + 1;
			}
		}
		// Si no se ha encontrado ningun caracter
		if (!hallado){
			// Insercion del caracter c en la ultima posicion
			sec.cadenaLetras[sec.letrasTotales] = c;
		}
		// Se añade el caracter <<c>> a la secuencia de letras en ultima posicion
		// Se incrementa el numero de letras que componen la cadena
		sec.letrasTotales++;
	}
	// Se finaliza la cadena formada con el carater nulo 
	sec.cadenaLetras[sec.letrasTotales] = '\0';
}

/*
 * Pre: <sec> almacena una secuencia de letras mayúsculas
 * Post: <sec> almacena una secuencia de letras mayúsculas ordenadas alfabéticamente
 *       integrada por las mismas letras que formaban parte de su secuencia inicial
 * Ejemplo: Sea PEREZOSO la secuencia que almacena <sec>. Tras ejecutar ordenar(sec)
 *          <sec> almacenará la secuencia EEOOPRSZ
 */
void ordenar (SL& sec) {
	// Ordenacion de sec.cadenaLetras[0..sec.letrasTotales−1] por el metodo de seleccion 
	for (int i = 0; i < sec.letrasTotales - 1; i++){
		// Selecciona en <iMenor> el ındice de la letra de sec.cadenaletras[i,sec.letrasTotales−1] 
		// cuya posicion en el alfabeto es la mas pequeña
		int iMenor = i;
		// Obtencion del codigo ascii de la letra inicial
		int asciiLetraMenor = sec.cadenaLetras[i] - 'A';
		for (int j = i + 1; j < sec.letrasTotales; j++){
			// Obtencion del codigo ascii de la letra actual
			int asciiLetraNueva = sec.cadenaLetras[j] - 'A';
			if (asciiLetraNueva < asciiLetraMenor){
				// La letra actual es mas pequeña que la letra inicial
				// Actualizacion de los valores
				asciiLetraMenor = asciiLetraNueva;
				iMenor = j;
			}
		}
		// Permuta sec.cadenaletras[i] y sec.cadenaletras[iMayor].
		// Tras ello , en sec.cadenaletras[0..i] estaran ubicados y ordenados 
		// los (i + 1) letras con menores posiciones en el alfabeto 
		char aux = sec.cadenaLetras[iMenor];
		sec.cadenaLetras[iMenor] = sec.cadenaLetras[i];
		sec.cadenaLetras[i] = aux;
	}
}

/*
 * Post: Presenta por el dispositivo estándar de salida la secuencia de caracteres 
 *       almacenada en <sec>, sin acabar la línea en curso
 */
void mostrar (const SL& sec) {
	// Inicializacion del recorrido 
    int i = 0;
	// Muetreo por pantalla de las letras que conforman la 
	// secuencia de caracteres sec
	while (sec.cadenaLetras[i] != '\0'){
		// Se han mostrado por pantalla los sec.cadenasLetras[0..i] 
		cout << sec.cadenaLetras[i];
		i = i + 1;
		// Los caracteres localizados en sec.cadenasLetras[i + 1,sec.letrasTotales - 1]
		//estan pendientes de ser mostrados
	}
}

/********************************  Pruebas  ********************************/

/*
 * Función de prueba del comportamiento de la función concatenar(...). Presenta por el
 * dispositivo estándar de salida las secuencias de caracteres almacenadas inicialmente 
 * en <sec1> y en <sec2>, así como la secuencia resultante de concatenar en <sec1> las 
 * dos secuencias anteriores tras invocar la ejecución de concatenar(sec1, sec2).
 */
void pruebaConcatenar (SL& sec1, const SL& sec2) {
    mostrar(sec1);
    cout << " o ";
    mostrar(sec2);
    cout << " = ";
    concatenar(sec1, sec2);
    mostrar(sec1);
    cout << endl;
}

/*
 * Función de prueba del comportamiento de la función insertar(...). Presenta por el
 * dispositivo estándar de salida la secuencia de caracteres almacenada inicialmente 
 * en <sec>, así como la secuencia resultante de insertar en <sec> el carácter <c>
 * tras invocar la ejecución de insertar(sec, c).
 */
void pruebaInsertar (SL& sec, const char c) {
    cout << "El resultado de insertar " << c << " en ";
    mostrar(sec);
    cout << " es ";
    insertar(sec, c);
    mostrar(sec);
    cout << endl;
}

/*
 * Función de prueba del comportamiento de la función ordenar(...). Presenta por 
 * el dispositivo estándar de salida la secuencia de caracteres almacenada inicialmente 
 * en <sec> así como la secuencia almacenada en <sec> como resultado de ordenar 
 * alfabéticamente los caracteres de ésta, tras invocar la ejecución de ordenar(sec).
 */
void pruebaOrdenar (SL& sec) {
    cout << "Antes de ordenar :   ";
    mostrar(sec);
    ordenar(sec);
    cout << endl << "Despues de ordenar : ";
    mostrar(sec);
    cout << endl;
}

/*
 * Función principal de un programa de prueba del comportamiento de las cinco funciones 
 * definidas para gestionar datos de tipo SL
 */
int main () {
    // Se va a trabajar con dos variables de tipo SL
   // Se va a trabajar con dos variables de tipo SL
    SL sec1, sec2;
    // Se definen valores de ambas varibles
    definir(sec1, "AEIOU"); 
    definir(sec2, "BCDFGHIJKLMNPQRSTVWXYZ");
    // Un par de pruebas de la función concatenar(sec,anyadida)
    pruebaConcatenar(sec2, sec1);
    pruebaConcatenar(sec1, sec2);
    cout << endl;
    // Un par de pruebas de la función ordenar(sec)
    pruebaOrdenar(sec1);
    pruebaOrdenar(sec2);
    cout << endl;
    // Se define un nuevo valor para <sec1>
    definir(sec1, "ABCDEF"); 
    // Tres pruebas de la función insertar(sec,c)
    pruebaInsertar(sec1, 'A');
    pruebaInsertar(sec1, 'C');
    pruebaInsertar(sec1, 'J');
    cout << endl;
    // Se define un nuevo valor para <sec1>, una secuencia de longitud 0
    definir(sec1, "");
    // Tres pruebas adicionales de la función insertar(sec,c)
    pruebaInsertar(sec1, 'J');
    pruebaInsertar(sec1, 'C');
    pruebaInsertar(sec1, 'J');
    // El programa de prueba concluye normalmente
    return 0;
}