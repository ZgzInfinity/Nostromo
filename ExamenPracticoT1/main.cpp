/*
 * Autor del trabajo (escriba su nombre y apellidos ): 
 */ 
 
/*
 ∗ Este programa, a partir de la informacion de un ﬁchero de texto con la informaci´on 
 ∗ basica de los alumnos de un grupo y un ﬁchero binario con sus caliﬁcaciones , cuyos 
 ∗ nombres son facilitados interactivamente por el operador, presenta por el dispositivo 
 ∗ estandar de salida un listado con las caliﬁcaciones de todos los alumnos del grupo, 
 ∗ ordenados seg´un caliﬁcaciones decrecientes (comenzando por los alumnos con mejores 
 ∗ caliﬁcaciones y concluyendo con los que presentan peores caliﬁcaciones ). 
 */
 
#include <iostream> 
#include <iomanip> 
#include <cstring> 
#include <fstream>

using namespace std;
// En el m´odulo de biblioteca <grupo> se han deﬁnido los siguientes elementos: 
	// −Constantes LIMITE NOMBRE, LIMITE APELLIDOS y LIMITE GRUPO 
	// −Constantes MH, SB, NO, AP, SU y NP // −Tipos de datos Alumno, Grupo y Notas 
	// −Colecciones de funciones para trabajar los datos de los tres tipos anteriores 
#include "../../biblioteca/GestionGrupos/grupo.h" 

/*
 ∗ Pre: El valor de <codigoNumerico> representa el codigo num´erico de un alumno 
 ∗ universitario . El vector lasNotas[0,n−1] almacena las caliﬁcaciones de <n> 
 ∗ alumnos en una asignatura 
 ∗ Post: Si constan en el vector lasNotas[0,n−1] las caliﬁcaciones del alumno 
 ∗ <codigoNumerico> entonces devuelve la mejor de sus notas cuantitativas expresada 
 ∗ en dEcimas de punto (i.e.: un valor entre 0 y 100) o un valor negativo igual a 
 ∗ NO PRESENTADO si no se ha presentado a ninguna de las dos convocatorias. 
 ∗ Si no constan en el vector lasNotas[0,n−1] las caliﬁcaciones del alumno 
 ∗ <codigoNumerico> entonces devuelve un valor negativo igual a NO ENCONTRADO 
 */ 

int suMejorNota (const int codigoNumerico, const Notas lasNotas [], const int n) { 
	// B´usqueda secuencial de las notas del alumno <codigoNumerico> en lasNotas[0,n−1] 
	int i = 0; 
	bool encontrado = false; 
	while (!encontrado && i < n) { 
		if (codigoAlumno(lasNotas[i]) == codigoNumerico){ 
			encontrado = true; } 
		else {
			i = i + 1; 
		} 
	} 
	if (encontrado) { 
		// Se han localizado las notas del alumno <codigoNumerico> 
		// Determina la caliﬁcaci´on en la primera convocatoria 
		int cual, cuan; 
		convocatoria1(lasNotas[i], cual, cuan); 
		// Asigna a <mejorNota> la nota cuantitiva en la primera convocatoria 
		int mejorNota;
		if (cual != NP){ 
			mejorNota = cuan; 
		} 
		else {
			const int NO_PRESENTADO = -1; 
			mejorNota = NO_PRESENTADO; 
		} 
		// ¿Cabe esperar una nota en la segunda convocatoria? 
		if ((cual == SU) || (cual == NP)){ 
			// Determina la caliﬁcaci´on en la segunda convocatoria 
			convocatoria2(lasNotas[i], cual, cuan); 
			if (cual != NP){ 
				// ¿Supera la nota de la segunda convocatoria a la nota de la primera? 
				if (cuan > mejorNota){ 
					mejorNota = cuan; 
				} 
			} 
			// Ha asignado a <mejorNota> la mejor nota cuantitiva de ambas convocatorias 
		} // Devuelve la mejor nota cuantitiva de ambas convocatorias 
		return mejorNota;
	} 
	else {
		// Devuelve <NO ENCONTRADO> al no haber localizado en lasNotas[0,n−1] 
		// las notas del alumno <codigoNumerico> 
		const int NO_ENCONTRADO = -999; 
		return NO_ENCONTRADO; 
	}
} 

/*
 ∗ Pre: −− 
 ∗ Post: Ha devuelto <true> si y solo si <uno> precede alfabeticamente 
 ∗ a <otro> dando prioridad, en primer lugar, a los apellidos , y,
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
		return strcmp(nombre1, nombre2) < 0; 
	} 
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
 ∗ Pre: n > 0, <T[0..n−1]> almacena los <n> alumnos de un grupo y <lasNotas[0..numNotas−1]> 
 ∗ almacena sus caliﬁcaciones en una asignatura. Las notas <lasNotas[i]> pueden 
 ∗ no corresponder al alumno <T[i]> 
 ∗ Post: T[0..n−1] es una permutacion de los datos iniciales de T[0..n−1] y todos 
 ∗ ellos est´an ordenados de forma que cada uno corresponde a un alumno cuya 
 ∗ nota en la asignatura es mayor o igual que la del siguiente en la tabla <T> 
 */
void ordenar (Alumno T[], const int n, const Notas lasNotas [], const int numNotas){ 
	// Ordenacion de T[0..n−1] por el m´etodo de seleccion 
	for (int i = 0; i < n-1; ++i) { 
		// Selecciona en <iMayor> el ındice del alumno de T[i,n−1] con la mejor nota 
		int iMayor = i; 
		int nota_iMayor = suMejorNota(codigo(T[i]), lasNotas, numNotas);
		for (int j = i + 1; j < n; ++j) { 
			int nota_j = suMejorNota(codigo(T[j]), lasNotas, numNotas); 
			if (nota_j > nota_iMayor) { 
				iMayor = j; 
				nota_iMayor = nota_j; 
			} 
			else if (nota_j == nota_iMayor) { 
				if (esMenor(T[j], T[iMayor])) {
					iMayor = j; 
					nota_iMayor = nota_j; 
				} 
			}
		} 
		// Permuta T[i] y T[iMayor]. Tras ello , en T[0.. i] estaran ubicados y ordenados 
		// los (i + 1) alumnos con mejores notas 
		permutar(T[i], T[iMayor]); 
	} 
} 

/*
 ∗ Pre: <notaCualitativa> presenta uno de los siguientes valores: MH, SB, NO, AP, SU o NP 
 ∗ que representan cualiﬁcaciones cualitativas de una asignatura 
 ∗ Post: Ha escrito dos caracteres que describen la caliﬁcacion <notaCualitativa>: 
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

/*
 ∗ Pre: <codigoNumerico> deﬁne el codigo numerico de un alumno 
 ∗ <lasNotas[0..n−1]> almacena las caliﬁcaciones de un grupo de alumnos 
 ∗ Post: Si el valor de <codigoNumerico> corresponde con uno de los alumnos del 
 ∗ grupo entonces ha escrito por pantalla la caliﬁcaci´on del alumno en 
 ∗ la primera convocatoria y, si no ha logrado aprobar en ella la asignatura,
 ∗ la caliﬁcaci´on en segunda convocatoria y devuelve <true>. Ejemplos 
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
		} else {
			i = i + 1; 
		} 
	} 
	if (encontrado) { 
		// Se han localizado las caliﬁcaciones del alumno <codigoNumerico> en lasNotas[i] 
		// Presenta sus caliﬁcaciones en la primera convocatoria 
		int cual, cuan; 
		convocatoria1(lasNotas[i], cual, cuan); 
		mostrarCalificacion(cual); 
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
			mostrarCalificacion(cual); 
			if (cual != NP){
				cout << fixed << right << setprecision(1) << setw(5) << cuan / 10.0;
			} 
		} 
		// Devuelve <true> por haber localizado las notas del alumno <codigoNumerico> 
		return true; 
	} 
	else {
		// Devuelve <false> al no haber localizado las notas del alumno <codigoNumerico> 
		return false; 
	} 
} 

/*
 ∗ Pre: n > 0 y T[0..n−1] almacena los datos de <n> alumnos cuya caliﬁcacion es <nota> 
 ∗ y est´an ordenados alfab´eticamente . 
 ∗ Post: Ha presentado por el dipositivo estandar de salida un listado con los nombres 
 ∗ y apellidos , ordenados alfabeticamente , de los alumnos almacenados en T[0..n−1], 
 ∗ informando previamente de su caliﬁcacion cualitativa com´un. Ejemplo: 
 ∗  ALUMNOS CALIFICADOS CON APROBADO 
 ∗    1. DOMINGUEZ GARRAPIZ, CLARA 
 *     		   . . .
 ∗    5. ZAMORA HORNILLOS, JARA 
 */ 
void mostrarListado (const Alumno T[], const int n, const char nota[]) { 
	cout << "Alumnos caliﬁcados con " << nota << endl; 
	for (int i = 0; i < n; ++i) { 
		char nombre[LIMITE_NOMBRE]; 
		char apellidos [LIMITE_APELLIDOS]; 
		nombreCompleto(T[i], nombre, apellidos ); 
		cout << setw(3) << i + 1 << ". " << apellidos << ", " << nombre << endl; 
	} 
	cout << endl; 
}

/* 
 ∗ Pre: <g> gestiona los datos basicos de un grupo de alumnos y <nombreFicheroNotas> es 
 ∗ un ﬁchero binario que almacena las caliﬁcaciones de los alumnos del grupo 
 ∗ Post: Si no ha podido acceder al ﬁchero <nombreFicheroNotas> entonces se ha limitado 
 ∗ a devolver el valor <false> 
 ∗ Si ha podido acceder al ﬁchero <nombreFicheroNotas> entonces presenta por el 
 ∗ dipositivo estandar de salida un listado ordenado alfabeticamente por apellidos 
 ∗ (y, en caso de coinciencia de los apellidos , por nombres) con las caliﬁcaciones 
 ∗ obtenidas por los alumnos del grupo a razon de un alumno por lınea y ha devuelto 
 ∗ el valor <true>. Ilustracion del formato del listado presentado: 
 ∗ ∗ 		LISTADO DE CALIFICACIONES DE PROGRAMACION 1 
 ∗ 			=========================================== 
 ∗  CODIGO 		  NOMBRE 			  APELLIDOS 		 FEBRERO 	 SEPTIEMBRE 
 ∗ ======== 	===========		 ==================== 	 =======	 ========== 
 ∗ 19223455 		MARIA 		 ABADIA DE LAIGLESIA 		NP 			AP 5.4
 ∗ 5602288 		JOSE MANUEL 	 BERMUDEZ LISBOA 		  NO 8.4 
 ∗ 								. . . 
 ∗ 75099800 		PEDRO 		 TARRAGONA PEREZ 		  SU 2.2 		SU 3.0 
 */
bool listadoNotas (const Grupo& g,const char nombreFicheroNotas[]) { 
	Notas lasNotas[LIMITE_GRUPO]; 
	int n; 
	if (leerNotas(nombreFicheroNotas, lasNotas, n)) { 
		Alumno T[LIMITE_GRUPO]; 
		// Almacena en T[0..numeroAlumnos−1] los <numeroAlumnos> alumnos del grupo 
		int numeroAlumnos = numAlumnos(g); 
		for (int i = 1; i <= numeroAlumnos; ++i){ 
			T[i-1] = alumno(g, i); 
		} // Ordena los alumnos de T[0..numeroAlumnos−1] segun caliﬁcaciones decrecientes 
		ordenar(T, numeroAlumnos, lasNotas, n); 
		// Prsenta un listado de los alumnos de T[0..numeroAlumnos−1] 
		cout << endl; 
		cout << setw(12) << ' ' << "LISTADO DE CALIFICACIONES DE PROGRAMACION 1" << endl;
		cout << setw(12) << ' ' << "===========================================" << endl << endl; 
		cout << left << " CODIGO " << ' ' << left << setw(LIMITE_NOMBRE) 
			 << "NOMBRE" << setw(LIMITE_APELLIDOS) << "APELLIDOS" << setw(8) 
			 << "FEBRERO   " << setw(9) << "SEPTIEMBRE" << endl; 
		cout << internal << setw(8) << "========" << ' '; 
		
		for (int i = 1; i < LIMITE_NOMBRE - 1; ++i){ 
			cout << '='; 
		} 
		cout << "  "; 
		for (int i = 1; i < LIMITE_APELLIDOS - 1; ++i){ 
			cout << '='; 
		} 
		cout << "  "; 
		for (int i = 1; i < 8; ++i) { 
			cout << '='; 
		} 
		cout << "   "; 
		for (int i = 1; i <= 10; ++i) { 
			cout << '='; 
		} 
		cout << endl; 
		for (int i = 0; i < numeroAlumnos; ++i){ 
			char nombre[LIMITE_NOMBRE]; 
			char apellidos [LIMITE_APELLIDOS]; 
			nombreCompleto(T[i], nombre, apellidos ); 
			cout << right << setw(8) << codigo(T[i]) << ' ' << left << setw(LIMITE_NOMBRE) 
				 << nombre << setw(LIMITE_APELLIDOS) << apellidos; 
			mostrarNotas(codigo(T[i]), lasNotas, n); 
			cout << endl; 
		} 
		// Devuelve <true> tras haber presentado el listado 
		return true; 
	} else {
		// Devuelve <false> por no haber podido presentar el listado 
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
	if (f.is_open()) { 
		f.close (); 
		return true; 
	} 
	else {
		return false; 
	} 
} 

/* 
 ∗ Post: Presenta por el dispositivo estandar de salida un listado con las caliﬁcaciones 
 ∗ de los alumnos de un grupo a partir de la informacion almacenada previamente de 
 ∗ dos ﬁcheros almacenados en la carpeta o directorio ../../ datos cuyos nombres 
 ∗ han de ser proporcionados interactivamente por el operador. 
 ∗ 1. Fichero de texto con la informacion basica de los alumnos del grupo 
 ∗ 2. Fichero binario de caliﬁcaciones de todos los alumnos del grupo 
 ∗ El listado se presenta con los alumnos ordenados segun caliﬁcaciones decrecientes , 
 ∗ y en caso de coincidir la caliﬁcacion , alfabeticamente . El formato del listado 
 ∗ se ilustra a continuaci´on: ∗ 
 ∗ 				LISTADO DE CALIFICACIONES DE PROGRAMACION 1 
 ∗			    ===========================================  
 ∗ 		CODIGO 			NOMBRE 				APELLIDOS 			FEBRERO 	SEPTIEMBRE 
 ∗ 		======== 	  =========== 	  ==================== 		======= 	========== 
 ∗ 		19223455 		MARIA 		   ABADIA DE LAIGLESIA 		   NP          AP 5.4 
 ∗		5602288 	  JOSE MANUEL 	   BERMUDEZ LISBOA 			  NO 8.4 
 ∗ 									. . . 
 ∗ 		75099800 PEDRO TARRAGONA PEREZ SU 2.2 SU 3.0 
 */
int main () { 
	 // Almacenara el nombre de un ﬁchero de texto que almacena los datos basicos de 
	 // los alumnos de un grupo (sus c´odigo num´ericos, sus apellidos y sus nombres) 
	 char ficheroAlumnos[64] = "../../datos/"; 
	 // Almacenara el nombre de un ﬁchero binario que almacena las caliﬁcaciones de 
	 // los alumnos de ese mismo grupo 
	 char ficheroNotas[64] = "../../datos/"; 
	 // Deﬁnici´on del nombre completo del ﬁchero de alumnos 
	 char nombreFichero[64]; 
	 cout << "Fichero de alumnos del grupo: " << ficheroAlumnos;
	 cin >> nombreFichero;
	 strcat (ficheroAlumnos, nombreFichero); 
	 char linea [12]; 
	 cin. getline (linea , 12); 
	 if (esAccesible(ficheroAlumnos)) { 
		 // Deﬁnicion del nombre completo del ﬁchero de caliﬁcaciones 
		 cout << "Fichero de notas del grupo: " << ficheroNotas; 
		 cin >> nombreFichero; 
		 strcat (ficheroNotas , nombreFichero); 
		 // Deﬁne el grupo de alumnos <g> a partir de los datos almacenados en el ﬁchero
		// de alumnos <ﬁcheroAlumnos> 
		Grupo g; 
		leerGrupo(ficheroAlumnos, g); 
		// Intenta presentar un listado con las caliﬁcaciones de los alumnos del grupo <g> 
		// que estan almacenadas en el ﬁchero binario de caliﬁcaciones <ﬁcheroNotas>

		if (! listadoNotas (g, ficheroNotas )) { 
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