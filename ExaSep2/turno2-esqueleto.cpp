/*
 * Autor del trabajo: Ruben Rodriguez Esteban
 * NIP: 737215
 */

#include <iostream>
using namespace std;

// Máximo número de dígitos que pueden llegar a integrar una secuencia de tipo SD
const int NUM_MAX_DIGITOS = 100;

/*
 * Un dato de tipo SD permite representar una secuencia de dígitos
 * de longitud menor o igual que NUM_MAX_DIGITOS
 */
struct SD {
    private:
        // Estructura interna de un dato de tipo SD
        int numDigitos;                          // Número de dígitos de la secuencia
        char digitos[NUM_MAX_DIGITOS];           // digitos[0..numDigitos]
    public:
        // Funciones para gestionar datos de tipo SD
        friend void definir (SD& sec, const char digitos[]);
        friend void concatenar (SD& sec, const SD& resto);
        friend void insertar (SD& sec, const char d);
        friend bool eliminar (SD& sec, const char d);
		friend void ordenarTramo(SD& sec, const int i1, const int i2);
        friend void organizar (SD& sec);
        friend void mostrar (const SD& sec);
};

/*
 * Pre: <digitos> almacena una cadena de caracteres todos los cuales son dígitos, es
 *      decir, caracteres del '0' al '9'. El número de dígitos de la cadena es menor
 *      o igual que NUM_MAX_DIGITOS
 * Post: Ha asignado a <sec> la secuencia de dígitos almacenada en <digitos>
 *       respetando su posición en <dígitos>
 * Ejemplo: Tras ejecutar definir(sec, "1230005621") <sec> almacena la secuencia de
 *          dígitos 1230005621
 */
void definir (SD& sec, const char digitos[]) {
	// La cadena inicialmente no posee ningun digito
    sec.numDigitos = 0;
	int i = 0;
	while (digitos[i] != '\0'){
		sec.digitos[sec.numDigitos] = digitos[i];
		i = i + 1;
		sec.numDigitos++;
	}
	sec.digitos[sec.numDigitos] = '\0';
}


/*
 * Pre: <sec> almacena una secuencia de dígitos y <resto> almacena otra secuencia
 *      de dígitos. La suma de las longitudes de ambas secuencia no exceden el valor
 *      de NUM_MAX_DIGITOS
 * Post: <sec> almacena la secuencia de dígitos resultante de concatenar la secuencia
 *       almacenada inicialmente en <sec> seguida de la secuencia almacenada inicialmente
 *       en <resto>
 * Ejemplo: Sea 9876 la secuencia que almacena <sec1> y sea 12345 la
 *          secuencia que almacena <sec2>. Tras ejecutar concatenar(sec1, sec2)
 *          entonces <sec1> almacenará la secuencia 987612345
 */
void concatenar (SD& sec, const SD& resto) {
	int i = 0;
	// Se verifica si la cadena puede o no concatenarse
    if (sec.numDigitos < NUM_MAX_DIGITOS){
		bool llena = false;
		// Se pueden añadir digito a la cadena
		// pero se debe determinar si podemos añadir todos
		while (resto.digitos[i] != '\0' && !llena){
			// No se excede la capacidad maxima y todavia podemos añadir digitos
			sec.digitos[i + sec.numDigitos] = resto.digitos[i];
			i = i + 1;
			// Verificacion de si se ha llenado la cadena
			// tras introducir el ultimo digito
			if (sec.numDigitos + i == NUM_MAX_DIGITOS){
				llena = true;
			}
		}
	}
	// Las cadenas se han concatenado correctamente
	// Se inserta el caracter nulo como caracter final de la
	// nueva cadena resultante
	sec.digitos[sec.numDigitos + i] = '\0';
	// Actualizacion del total de digitos que tiene ahora la cadena
	sec.numDigitos = sec.numDigitos + i;
}

/*
 * Pre: <sec> almacena una secuencia de dígitos ordenados de menor a mayor valor
 *      y el valor de <d> es un dígito comprendido entre '0' y '9'. La longitud
 *      de la secuencia de dígitos que almacena <sec> es inferior a NUM_MAX_DIGITOS
 * Post: <sec> almacena una secuencia de dígitos ordenados de menor a mayor valor
 *       de longitud igual a una unidad más que la almacenada inicialmente. De la
 *       nueva secuencia forman parte todas los dígitos de su secuencia inicial y,
 *       además, el dígito <d>
 * Ejemplos: Sea 22334488 la secuencia de dígitos que almacena <sec>. Tras ejecutar
 *       insertar(sec, '4') entonces <sec> almacenará 223344488
 *       Sea 223344488 la secuencia de dígitos que almacena <sec>. Tras ejecutar
 *       insertar(sec, '0') entonces <sec> almacenará 0223344488
 *       Sea 0223344488 la secuencia de dígitos que almacena <sec>. Tras ejecutar
 *       insertar(sec, '9') entonces <sec> almacenará 02233444889
 */
void insertar (SD& sec, const char d) {
	// Se verifica si se puede añadir nuevos digitos a la cadena
    if (sec.numDigitos < NUM_MAX_DIGITOS){
		int i = 0;
		bool hallado = false;
		// Obtencion del ascii del digito a introducir
		int asciiNumeroNuevo = d -'A';
		// Busqueda de la primer digito de la palabra que es mayor que d
		while (!hallado && sec.digitos[i] != '\0'){
			// Obtencion del ascii del digito actual
			int asciiNumeroActual = sec.digitos[i] - 'A';
			if (asciiNumeroActual >= asciiNumeroNuevo){
				// Si el ascii del actual es mayor que el que queremos introducir
				// hemos encontrado el digito
				hallado = true;
				// Desplazamos todos los digitos siguientes a la derecha
				// para dejar espacio para el digito d
				for (int j = sec.numDigitos - 1; j >= i; j--){
					sec.digitos[j + 1] = sec.digitos[j];
				}
				// Introduccion del digito d en la posicion correcta
				sec.digitos[i] = d;
			}
			else{
				// el digito con ascii mayor a d no se ha encontrado todavia
				i = i + 1;
			}
		}
		// Si no se ha encontrado ningun digito
		if (!hallado){
			// Insercion del digito d en la ultima posicion
			sec.digitos[sec.numDigitos] = d;
		}
		// Se añade el digito <<d>> a la secuencia de digitos en ultima posicion
		// Se incrementa el numero de digitos que componen la cadena
		sec.numDigitos++;
	}
	// Se finaliza la cadena formada con el carater nulo 
	sec.digitos[sec.numDigitos] = '\0';
}


/*
 * Pre: <sec> almacena una secuencia de dígitos ordenados de menor a mayor valor
 *      y el valor de <d> es un dígito comprendido entre '0' y '9'. La longitud
 *      de la secuencia de dígitos que almacena <sec> es inferior a NUM_MAX_DIGITOS
 * Post: <sec> almacena una secuencia de dígitos ordenados de menor a mayor valor
 *       de longitud igual a una unidad más que la almacenada inicialmente. De la
 *       nueva secuencia forman parte todas los dígitos de su secuencia inicial
 *       excepto una aparición del dígito <d>, si existía. Devuelve true si el dígito <d>
 *       estaba en la secuenca y ha sido eliminado una vez y false en caso cotrario.
 * Ejemplos: Sea 22334488 la secuencia de dígitos que almacena <sec>. Tras ejecutar
 *       eliminar(sec, '4') entonces <sec> almacenará 2233488 y habrá devuelto true
 *       Sea 2233488 la secuencia de dígitos que almacena <sec>. Tras ejecutar
 *       eliminar(sec, '0') entonces <sec> almacenará 2233488 y habrá devuelto false
 *       Sea 2233488 la secuencia de dígitos que almacena <sec>. Tras ejecutar
 *       eliminar(sec, '4') entonces <sec> almacenará 223388 y habrá devuelto true.
 */
bool eliminar(SD& sec, const char d) {
	bool encontrado = false;
	int i = 0;
	// Verificacion de si encontramos el caracter
	while (!encontrado && i < sec.numDigitos){
		// el caracter actual es igual al buscado
		if (sec.digitos[i] == d){
			// encontrado el caracter d
			encontrado = true;
		}
		else{
			// no se ha encontrado todavia el caracter d
			i = i + 1;
		}
	}
	if (encontrado){
		// Desplazamos todos los digitos siguientes a la izquierda
		// para eliminar el digito d
		for (int j = i; j < sec.numDigitos - 1; j++){
			sec.digitos[j] = sec.digitos[j + 1]; 
		}
		// Se decrementa el total de digitos que componen la secuencia
		sec.numDigitos--;
	}
	// Se devuelve si se ha encontrado
	return encontrado;
}

/*
 * Pre: <sec> almacena una secuencia de dígitos ordenados de menor a mayor valor
 *      y el valor de <d> es un dígito comprendido entre '0' y '9'. La longitud
 *      de la secuencia de dígitos que almacena <sec> es inferior a NUM_MAX_DIGITOS,
 *      <i1> y <i2> son posiciones de la cadena sec y 
 *      i1 < i2
 * Post: Devuelve la cadena <sec> resultante de haber ordenado todos los elementos de
 *       menor a mayor
 */
void ordenarTramo (SD&sec, const int i1, const int i2){
	// Ordenacion de sec.digitos[0..sec.numDigitos−1] por el metodo de seleccion 
	for (int j = i1; j < i2 - 1; j++){
		// Selecciona en <jMenor> el ındice del numero de sec.digitod[j,sec.numDigitos−1] 
		// cuya posicion en el alfabeto es la mas pequeña
		int jMenor = j;
		// Obtencion del codigo ascii del digito inicial
		int asciiNumeroMenor = sec.digitos[j] - '0';
		for (int k = j + 1; k < i2; k++){
			// Obtencion del codigo ascii del digito actual
			int asciiNumeroNuevo = sec.digitos[k] - '0';
			if (asciiNumeroNuevo < asciiNumeroMenor){
				// el digito actual es mas pequeño que el digito inicial
				// Actualizacion de los valores
				asciiNumeroMenor = asciiNumeroNuevo;
				jMenor = k;
			}
		}
		// Permuta sec.digitos[j] y sec.digitos[jMayor].
		// Tras ello , en sec.digitos[0..j] estaran ubicados y ordenados 
		// los (j + 1) letras con menores posiciones en el alfabeto 
		char aux = sec.digitos[jMenor];
		sec.digitos[jMenor] = sec.digitos[j];
		sec.digitos[j] = aux;
	}
}
/*
 * Pre: <sec> almacena una secuencia de dígitos
 * Post: <sec> almacena una secuencia de digitos integrada por los mismos que formaban
 *       parte de su secuencia inicial pero su orden es diferente ya que en primer lugar
 *       se sitúan los dígitos pares, ordenados de menor a mayor valor y, a continuación,
 *       se sitúan los dígitos impares, también ordenados de menor a mayor valor
 * Ejemplo: Sea 1632772630534312011 la secuencia que almacena inicialmente <sec>. Tras
 *       ejecutar organizar(sec), <sec> almacenará la secuencia 0022266411113333577
 */
void organizar (SD& sec) {
	// Inicio de la secuencia
	int inf = 0;
	// Fin de la secuencia
	int sup = sec.numDigitos - 1;
	while (inf != sup){
		// Obtencion de los codigos ascii de cada numero
		int digitoInf = sec.digitos[inf] - '0';
		int digitoSup = sec.digitos[sup] - '0';
		if (digitoInf % 2 == 0){
			// el digito es par y no lo debemos tocar
			inf++;
		}
		else if (digitoSup % 2 != 0){
			// el digito es impar y no lo debemos tocar
			sup--;
		}
		else{
			// los digitos estan mal posicionados y se 
			// deben permutar sus posiciones
			char aux = sec.digitos[inf];
			sec.digitos[inf] = sec.digitos[sup];
			sec.digitos[sup] = aux;
			inf++;
			sup--;
		}
	}
	// Todos los digitos pares preceden a los impares
	int i = 0;
	bool primerImparHallado = false;
	// Busqueda del primer digito impar si existe
	while (!primerImparHallado && i < sec.numDigitos){
		// Obtencion del ascii del digito actual
		int asciiNumero = sec.digitos[i] - '0';
		if (asciiNumero % 2 != 0){
			// comprobacion de que el digito es par
			primerImparHallado = true;
		}
		else {
			// el primer digito impar todavia no se ha hallado
			i = i + 1;
		}
	}
	
	// Ordenacion de los fragmentos de la cadena
	ordenarTramo(sec,0,i);
	ordenarTramo(sec,i,sec.numDigitos);
}

/*
 * Post: Presenta por el dispositivo estándar de salida la secuencia de dígitos
 *       almacenada en <sec>, sin acabar la línea en curso
 */
void mostrar (const SD& sec) {
	// Muetreo por pantalla de las letras que conforman la 
	// secuencia de caracteres sec
	for (int i = 0; i < sec.numDigitos; i++){
		// Se han mostrado por pantalla los sec.cadenasLetras[0..i] 
		cout << sec.digitos[i];
	}
	// Los caracteres localizados en sec.cadenasLetras[i + 1,sec.letrasTotales - 1]
	//estan pendientes de ser mostrados
}


/********************************  Pruebas  ********************************/

/*
 * Función de prueba del comportamiento de la función concatenar(...). Presenta por el
 * dispositivo estándar de salida las secuencias de dígitos almacenadas inicialmente
 * en <sec1> y en <sec2>, así como la secuencia resultante de concatenar en <sec1> las
 * dos secuencias anteriores tras invocar la ejecución de concatenar(sec1, sec2).
 */
void pruebaConcatenar (SD& sec1, const SD& sec2) {
    mostrar(sec1);
    cout << " & ";
    mostrar(sec2);
    cout << " = ";
    concatenar(sec1, sec2);
    mostrar(sec1);
    cout << endl;
}

/*
 * Función de prueba del comportamiento de la función insertar(...). Presenta por el
 * dispositivo estándar de salida la secuencia de dígitos almacenada inicialmente
 * en <sec>, así como la secuencia resultante de insertar en <sec> el dígito <d>
 * tras invocar la ejecución de insertar(sec, d).
 */
void pruebaInsertar (SD& sec, const char d) {
    cout << "El resultado de insertar " << d << " en ";
    mostrar(sec);
    cout << " es ";
    insertar(sec, d);
    mostrar(sec);
    cout << endl;
}

/*
 * Función de prueba del comportamiento de la función eliminar(...). Presenta por el
 * dispositivo estándar de salida la secuencia de dígitos almacenada inicialmente
 * en <sec>, así como la secuencia resultante de eliminar de <sec> el dígito <d>
 * y el resultado de invocar a eliminar(sec, d).
 */
void pruebaEliminar (SD& sec, const char d) {
    cout << "El resultado de eliminar " << d << " de ";
    mostrar(sec);
    cout << " es ";
    bool resultado = eliminar(sec, d);
    mostrar(sec);
    cout << " y ha devuelto " << boolalpha << resultado;
    cout << endl;
}

/*
 * Función de prueba del comportamiento de la función ordenar(...). Presenta por
 * el dispositivo estándar de salida la secuencia de dígitos almacenada inicialmente
 * en <sec> así como la secuencia almacenada en <sec> como resultado de "organizar"
 * los caracteres de esta, tras invocar la ejecución de ordenar(sec).
 */
void pruebaOrganizar (SD& sec) {
    cout << "Antes de ordenar :   ";
    mostrar(sec);
    organizar(sec);
    cout << endl << "Despues de ordenar : ";
    mostrar(sec);
    cout << endl;
}

int main() {

    SD secuencia1, secuencia2;
    definir(secuencia1, "12345");
    definir(secuencia2, "678");

	mostrar(secuencia1);
	cout << endl;
	mostrar(secuencia2);
	cout << endl;
	
    pruebaConcatenar(secuencia1, secuencia2);
    pruebaConcatenar(secuencia2, secuencia1);
    mostrar(secuencia1);
    cout << endl;

    definir(secuencia1, "");
    pruebaInsertar(secuencia1, '5');
    pruebaInsertar(secuencia1, '3');
    pruebaInsertar(secuencia1, '3');
    pruebaInsertar(secuencia1, '1');
    pruebaInsertar(secuencia1, '9');
    pruebaInsertar(secuencia1, '8');
    pruebaInsertar(secuencia1, '3');

    pruebaEliminar(secuencia1, '1');
    pruebaEliminar(secuencia1, '8');
    pruebaEliminar(secuencia1, '7');
    pruebaEliminar(secuencia1, '9');
    pruebaEliminar(secuencia1, '0');
    pruebaEliminar(secuencia1, '3');
    pruebaEliminar(secuencia1, '3');
    pruebaEliminar(secuencia1, '9');
    pruebaEliminar(secuencia1, '3');
    pruebaEliminar(secuencia1, '5');
    pruebaEliminar(secuencia1, '1');

    definir(secuencia1, "12345678901234567890");
	pruebaOrganizar(secuencia1);

    return 0;
}
