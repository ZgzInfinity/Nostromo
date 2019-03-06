/*
 ∗ Autor del trabajo (escriba su nombre y apellidos ): 
 */
 
 /*
  * Fichero turno2.cc que almacena un programa que constituye una solucion al trabajo 
  * planteado en el turno 2 del examen practico de PROG1 celebrado el 31 de enero de 2018. 
  * Este programa, a partir de la informacion de un ﬁchero de texto con la informacion 
  * basica de los alumnos de un grupo y un ﬁchero binario con sus caliﬁcaciones , cuyos 
  * nombres son facilitados interactivamente por el operador, presenta por el dispositivo 
  * estandar de salida un listado con las caliﬁcaciones de todos los alumnos del grupo, 
  * agrupados segun su caliﬁcacion cualitativa . 
  * 
  */ 

#include <iostream> 
#include <iomanip> 
#include <cstring> 
#include <fstream>

using namespace std;

// En el modulo de biblioteca <grupo> se han deﬁnido los siguientes elementos: 
// −Constantes LIMITE NOMBRE, LIMITE APELLIDOS y LIMITE GRUPO 
// −Constantes MH, SB, NO, AP, SU y NP 
// −Tipos de datos Alumno, Grupo y Notas 
// −Colecciones de funciones para trabajar los datos de los tres tipos anteriores 

#include "../../biblioteca/GestionGrupos/grupo.h" 

/*
 ∗ Pre: El valor de <codigoNumerico> representa el codigo numerico de un alumno 
 ∗ universitario . El vector lasNotas[0,n−1] almacena las caliﬁcaciones de <n> 
 ∗ alumnos en una asignatura 
 ∗ Post: Si constan en el vector lasNotas[0,n−1] las caliﬁcaciones del alumno 
 ∗ <codigoNumerico> entonces devuelve la mejor de sus notas cuantitativas expresada 
 ∗ en decimas de punto (i.e.: un valor entre 0 y 100) o un valor negativo igual a 
 ∗ NO PRESENTADO si no se ha presentado a ninguna de las dos convocatorias. 
 ∗ Si no constan en el vector lasNotas[0,n−1] las caliﬁcaciones del alumno 
 ∗ <codigoNumerico> entonces devuelve un valor negativo igual a NO ENCONTRADA 
 */ 
void suMejorNota (const int codigoNumerico, const Notas lasNotas [], const int n, int& cual, int& cuan) {
	// Busqueda secuencial de las notas del alumno <codigoNumerico> en lasNotas[0,n−1]
	int i = 0; bool encontrado = false; 
	while (!encontrado && i < n) { 
		if (codigoAlumno(lasNotas[i]) == codigoNumerico){ 
			encontrado = true; 
		} 
		else {
			i = i + 1; 
		} 
	} if (encontrado) { 
		// Se han localizado las notas del alumno <codigoNumerico> 
		// Determina la caliﬁcacion en la primera convocatoria 
		int nota_cual , nota_cuan; 
		convocatoria1(lasNotas[i], nota_cual , nota_cuan); 
		// Asigna a <mejorNota> la nota cuantitiva en la primera convocatoria 
		cual = nota_cual;
		if (nota_cual != NP){ 
			cuan = nota_cuan; 
		} 
		else {
			const int NO_PRESENTADO = -1; 
			cuan = NO_PRESENTADO; 
		} 
		// ¿Cabe esperar una nota en la segunda convocatoria? 
		if (( nota_cual == SU) || (nota_cual == NP)){ 
			// Determina la caliﬁcacion en la segunda convocatoria 
			convocatoria2(lasNotas[i ], nota_cual , nota_cuan); 
			if (nota_cual != NP){ 
				cual = nota_cual; 
				// ¿Supera la nota de la segunda convocatoria a la nota de la primera? 
				if (nota_cuan > cuan) { 
					cuan = nota_cuan; 
				} 
			} 
			// Ha asignado a <mejorNota> la mejor nota cuantitiva de ambas convocatorias 
		}
	} 
	else {
		// Devuelve <NO ENCONTRADA> al no haber localizado en lasNotas[0,n−1] 
		// las notas del alumno <codigoNumerico> 
		const int NO_ENCONTRADA = -999; 
		cual = NO_ENCONTRADA; 
	}
} 

/* 
 ∗ Pre: −− 
 ∗ Post: Ha devuelto <true> si y solo si <uno> precede alfabeticamente 
 ∗ a <otro> dando pripioridad, en primer lugar, a los apellidos , y, 
 ∗ para apellidos iguales, al nombre 
 */
bool esMenor (const Alumno uno,const Alumno otro) { 
	char nombre1[LIMITE_NOMBRE], nombre2[LIMITE_NOMBRE]; 
	char apellidos1 [LIMITE_APELLIDOS], apellidos2[LIMITE_APELLIDOS]; 
	nombreCompleto(uno, nombre1, apellidos1); 
	nombreCompleto(otro, nombre2, apellidos2 ); 
	if (strcmp( apellidos1 , apellidos2 ) < 0) { 
		// <apellidos1> precede alfab´eticamente a <apellidos2> 
		return true; 
	} 
	else if (strcmp( apellidos1 , apellidos2 ) == 0) { 
		// <apellidos1> coincide con <apellidos2> 
		// Los nombres son los que determinan, en este caso, el orden alfabetico 
		return strcmp(nombre1, nombre2) < 0; } 
	else { 
		// <apellidos1> es posterior alfabeticamente a <apellidos2> 
		return false; 
	} 
}


/* 
 ∗ Pre: uno = A y otro = B 
 ∗ Post: uno = B y otro = A 
 */
void permutar (Alumno &uno, Alumno &otro){
	Alumno aux = uno;
	uno = otro; 
	otro = aux;
} 


/* 
 ∗ Pre: n > 0 
 ∗ Post: T[0..n−1] es una permutacion de los datos iniciales de T[0..n−1] y todos 
 ∗ ellos est´an ordenados de forma que cada uno precede alfab´eticamente ( apellidos 
 ∗ y, en su caso, nombres) o coincide con siguiente en la tabla <T> 
 */ 
void ordenar (Alumno T[], const int n) { 
	// Ordenacion de T[0..n−1] por el metodo de seleccion 
	for (int i = 0; i < n -1; ++i) { 
		// Selecciona en <iMenor> el ındice del menor de los elementos de T[i,n−1] 
		int iMenor = i; 
		for (int j = i + 1; j < n; ++j) { 
			if (esMenor(T[j], T[iMenor])) { 
				iMenor = j; 
			} 
		} 
		// Permuta T[i] y T[iMenor]. Tras ello , en T[0.. i] estaran ubicados y ordenados 
		// los (i + 1) menores elementos que inicialmente habıa en la tabla 
		permutar(T[i], T[iMenor]); 
	} 
} 

/*
 ∗ Pre: <notaCualitativa> presenta uno de los siguientes valores: MH, SB, NO, AP, SU o NP 
 ∗ que representan cualiﬁcaciones cualitativas de una asignatura 
 ∗ Post: Ha escrito dos caracteres que describen la caliﬁcaci´on <notaCualitativa>: 
 ∗ ”MH”, SB”, NO”, AP”, SU” o ”NP”, respectivamente 
 */ 
void mostrarCalificacion (const int notaCualitativa ) { 
	if ( notaCualitativa == MH){
		cout << "MH";
	} 
	else if ( notaCualitativa == SB){ 
		cout << "SB";
	} 
	else if ( notaCualitativa == NO){
		cout << "NO";
	} 
	else if ( notaCualitativa == AP){ 
		cout << "AP";
	} 
	else if ( notaCualitativa == SU){ 
		cout << "SU";
	}
	else if ( notaCualitativa == NP){ 
		cout << "NP";
	} 
} 

// AQUI ESTA FUNCION NO SE USA
/*
 ∗ Pre: <codigoNumerico> deﬁnie el codigo numerico de un alumno 
 ∗ <lasNotas[0..n−1]> almacena las caliﬁcaciones de un grupo de alumnos 
 ∗ Post: Si el valor de <codigoNumerico> corresponde con uno de los alumnos del 
 ∗ grupo entonces ha escrito por pantalla la caliﬁcacion del alumno en 
 ∗ la primera convocatoria y, no si ha logrado aprobar en ella la asignatura, 
 ∗ la caliﬁcacion en segunda convocatoria y devuelve <true>. Ejemplos 
 ∗ de lo que puede escribir por pantalla: ”NP AP 6.5” y ”SB 9.2” 
 ∗ Si el valor de <codigoNumerico> no se corresponde con ninguno de los alumnos 
 ∗ del grupo entonces se ha limitado a devolver <false> 
 */ 
bool mostrarNotas (const int codigoNumerico, const Notas lasNotas [], const int n) { 
	int i = 0; 
	bool encontrado = false; 
	while (!encontrado && i < n) { 
		if (codigoAlumno(lasNotas[i]) == codigoNumerico){ 
			encontrado = true; 
		} 
		else {
			i = i + 1;
		}
	} 
	if (encontrado) { 
		// Se han localizado las caliﬁcaciones del alumno <codigoNumerico> en lasNotas[i] 
		// Presenta sus caliﬁcaciones en la primera convocatoria 
		int cual, cuan; 
		convocatoria1(lasNotas[i ], cual, cuan); 
		mostrarCalificacion (cual); 
		if (cual != NP){ 
			cout << fixed << right << setprecision(1) << setw(5) << cuan / 10.0 << ' '; 
		} 
		else { 
			cout << setw(6) << ' '; 
		} 
		if ((cual == SU) || (cual == NP)){ 
			// Presenta sus caliﬁcaciones en la segunda convocatoria 
			convocatoria2(lasNotas[i ], cual, cuan); 
			cout << setw(3) << ' '; 
			mostrarCalificacion (cual); 
			if (cual != NP){ 
				cout << fixed << right << setprecision(1) << setw(5) << cuan / 10.0; 
			} 
		} // Devuelve <true> por haber localizado las notas del alumno <codigoNumerico> 
		return true; 
	} 
	else {
		// Devuelve <false> al no haber localizado las notas del alumno <codigoNumerico> 
		return false; 
	}
}

 
/* 
 ∗ Pre: n > 0 y T[0..n−1] almacena los datos de <n> alumnos cuya caliﬁcacion es <nota> 
 ∗ y estan ordenados alfabeticamente . 
 ∗ Post: Ha presentado por el dipositivo estandar de salida un listado con los nombres 
 ∗ y apellidos , ordenados alfabeticamente , de los alumnos almacenados en T[0..n−1], 
 ∗ informando previamente de su caliﬁcaci´on cualitativa comun. Ejemplo: 
 ∗ 
 ∗ ALUMNOS CALIFICADOS CON APROBADO 
 ∗ 1. DOMINGUEZ GARRAPIZ, CLARA 
 ∗ 				. . . 
 ∗ 5. ZAMORA HORNILLOS, JARA 
 */
void mostrarListado (const Alumno T[], const int n, const char nota[]) { 
	cout << "Alumnos calificados con " << nota << endl; 
	for (int i = 0; i < n; ++i) { 
		char nombre[LIMITE_NOMBRE]; 
		char apellidos [LIMITE_APELLIDOS]; 
		nombreCompleto(T[i], nombre, apellidos ); 
		cout << setw(3) << i + 1 << ". "  << apellidos << ", " << nombre << endl; 
	} 
	cout << endl; 
} 

/* 
 ∗ Pre: <g> gestiona los datos basicos de un grupo de alumnos y <nombreFicheroNotas> es 
 ∗ un ﬁchero binario que almacena las caliﬁcaciones de los alumnos del grupo 
 ∗ Post: Si no ha podido acceder al ﬁchero <nombreFicheroNotas> entonces se ha limitado 
 ∗ a devolver el valor <false> 
 ∗ Si ha podido acceder al ﬁchero <nombreFicheroNotas> entonces presenta por el
 ∗ dipositivo estandar de salida un listado de caliﬁcaciones de alumnos agrupados 
 ∗ en bloques segun su caliﬁcaci´on cualitativa y, dentro de cada bloque, ordenados 
 ∗ alfabeticamente por apellidos y, en caso de igualdad, por nombre. Ejemplo: 
 ∗ 
 ∗ ALUMNOS CALIFICADOS CON SOBRESALIENTE 
 ∗ 1. FONSECA CARPINTERO, PAULA 
 ∗ 2. MUNDO CASTELLANO, ROSA 
 ∗ ALUMNOS CALIFICADOS CON NOTABLE 
 ∗ 1. CARRO BADENES, ROLDAN 
 ∗ 2. GARCES GARRAPIZ, CONCEPCION 
 ∗ 3. ZARAGOZA ZABALZA, ANA ISABEL 
 ∗ ALUMNOS CALIFICADOS CON APROBADO 
 ∗ 1. DOMINGUEZ GARRAPIZ, CLARA 
 ∗ 				. . . 
 ∗ 5. ZAMORA HORNILLOS, JARA 
 ∗ ALUMNOS CALIFICADOS CON SUSPENSO 
 ∗ 1. ESPINOSA OLIVITO, ALICIA 
 ∗ 				. . . 
 ∗ 3. MELUS MELUS, GUILLERMO 
 ∗ ALUMNOS CALIFICADOS CON NO PRESENTADO 
 ∗ 1. DOMINGO BELMEZ, DAVID 
 */ 
bool listadoNotas (const Grupo& g,const char nombreFicheroNotas[]) { 
	const int NUM_NOTAS = 6; 
	const int NOTAS[] ={ MH, SB, NO, AP, SU, NP }; 
	const char NOMBRE_NOTAS[][3] ={"MH", "SB", "NO", "AP", "SU", "NP"}; 
	int numeroAlumnos = numAlumnos(g); 
	Notas lasNotas[LIMITE_GRUPO]; 
	int numNotas; 
	if (leerNotas(nombreFicheroNotas, lasNotas, numNotas)){ 
		for (int nota = 0; nota < NUM_NOTAS; ++nota){ 
			Alumno T[LIMITE_GRUPO]; 
			// Almacena en T[0..numeroAlumnos−1] los alumnos del grupo 
			int cuenta = 0; 
			for (int i = 1; i <= numeroAlumnos; ++i){ 
				int cual, cuan; 
				Alumno nuevo = alumno(g, i); 
				suMejorNota(codigo(nuevo), lasNotas, numNotas, cual, cuan); 
				if (cual == NOTAS[nota]){ 
					T[cuenta] = nuevo; 
					cuenta = cuenta + 1; 
				} 
			} 
			// cuenta = numeroAlumnos 
			if (cuenta > 0) { 
				// Ordena alfabeticamente de los alumnos de T[0..cuenta−1] 
				ordenar(T, cuenta); 
				// Presenta por el dispositivo estandar de salida un listado 
				// de los alumnos de T[0..cuenta−1] 
				mostrarListado(T, cuenta, NOMBRE_NOTAS[nota]); 
			} 
		} 
		return true; 
	} 
	else {
		return false; 
	} 
} 

/* 
 ∗ Pre: <nombre> almacena una cadena de caracteres
 ∗ Post: Devuelve <true> si y solo si exite un ﬁchero de nombre <nombre> accesible 
 ∗ para la lectura de sus datos 
 */ 
bool esAccesible (const char nombre[]) { 
	ifstream f(nombre); 
	if (f.is_open ()) { 
		f.close (); 
		return true; 
	} 
	else {
		return false; 
	} 
}

/* 
 ∗ Post: Presenta por el dispositivo est´andar de salida un listado con las caliﬁcaciones 
 ∗ de los alumnos de un grupo a partir de la informaci´on almacenada previamente de 
 ∗ dos ﬁcheros almacenados en la carpeta o directorio ../../ datos cuyos nombres 
 ∗ han de ser proporcionados interactivamente por el operador. 
 ∗ 1. Fichero de texto con la informacion basica de los alumnos del grupo 
 ∗ 2. Fichero binario de caliﬁcaciones de todos los alumnos del grupo 
 ∗ El listado se presenta por bloques. En cada bloque ﬁguran ordenados 
 ∗ alfabeticamente los alumno con una misma caliﬁcacioon cualitatva . Los bloques 
 ∗ se ordenan de mayor caliﬁcaci´on (MH, SB, ..) a menor caliﬁcacion (.., AP, SU, 
 ∗ NP). Un bloque sin ning´un alumno se omite en el listado : Ejemplo de listado : 
 ∗ ALUMNOS CALIFICADOS CON SOBRESALIENTE 
 ∗ 1. FONSECA CARPINTERO, PAULA 
 ∗ 2. MUNDO CASTELLANO, ROSA 
 ∗ ALUMNOS CALIFICADOS CON NOTABLE 
 ∗ 1. CARRO BADENES, ROLDAN 
 ∗ 2. GARCES GARRAPIZ, CONCEPCION 
 ∗ 3. ZARAGOZA ZABALZA, ANA ISABEL 
 ∗ ALUMNOS CALIFICADOS CON APROBADO 
 ∗ 1. DOMINGUEZ GARRAPIZ, CLARA 
 ∗ . . . 
 ∗ 5. ZAMORA HORNILLOS, JARA 
 ∗ ALUMNOS CALIFICADOS CON SUSPENSO 
 ∗ 1. ESPINOSA OLIVITO, ALICIA ∗ . . . 
 ∗ 3. MELUS MELUS, GUILLERMO 
 ∗ ALUMNOS CALIFICADOS CON NO PRESENTADO 
 ∗ 1. DOMINGO BELMEZ, DAVID 
 */ 
 
 
int main () { 
	// Almacenara el nombre de un ﬁchero de texto que almacena los datos basicos de 
	// los alumnos de un grupo (sus codigo num´ericos, sus apellidos y sus nombres) 
	char ficheroAlumnos[64] = "../../datos/";
	// Almacenara el nombre de un ﬁchero binario que almacena las caliﬁcaciones de 
	// los alumnos de ese mismo grupo 
	char ficheroNotas[64] = "../../datos/";
	// Deﬁnicion del nombre completo del ﬁchero de alumnos 
	char nombreFichero[64]; 
	cout << "Fichero de alumnos del grupo: " << ficheroAlumnos; 
	cin >> nombreFichero; 
	strcat (ficheroAlumnos, nombreFichero); 
	char linea[12]; 
	cin.getline (linea , 12); 
	if (esAccesible(ficheroAlumnos)) {
		// Deﬁnicion del nombre completo del ﬁchero de caliﬁcaciones 
		cout << "Fichero de notas del grupo: " << ficheroNotas; 
		cin >> nombreFichero; 
		strcat (ficheroNotas , nombreFichero); 
		cout << endl;
		// Deﬁne el grupo de alumnos <g> a partir de los datos almacenados en el ﬁchero 
		// de alumnos <ﬁcheroAlumnos> 
		Grupo g; 
		leerGrupo(ficheroAlumnos, g);
		// Intenta presentar un listado con las caliﬁcaciones de los alumnos del grupo <g> 
		// que est´an almacenadas en el ﬁchero binario de caliﬁcaciones <ﬁcheroNotas> 
		if (!listadoNotas (g, ficheroNotas )) { 
			// Informa de que el ﬁchero de caliﬁcaciones no es accesible 
			cout << "No se ha podido acceder al fichero " << ficheroNotas << endl; 
		}
	} 
	else { 
		cout << "No se ha podido acceder al fichero " << ficheroAlumnos << endl; 
	} 
	// El programa concluye normalmente 
	return 0;
}
