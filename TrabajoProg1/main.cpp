/*
 * ==============================
 * Trabajo de Programación 1 
 * Autor: Rubén Rodríguez Esteban
 * NIP : 737215
 * Fecha de entrega 28-1-2018
 * ==============================
 */
 
 
#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include "../../biblioteca/GestionGrupos/grupo.h"

using namespace std;

/* Declaración de constantes */

const int MAX_LONG_LINEA = 128;
const int MAX_LONG_NOTA_CUALITATIVA = 2;


/*
 * Pre:  n1 = X y n2 = Y
 * Post: n1 = Y y n2 = X
 */
void intercambiar(Notas& n1, Notas& n2){
    Notas aux;
	aux = n1;
	n1 = n2;
	n2 = aux;
}


/*
 * Pre: El flujo <f> está asociado a un fichero de texto que almacena la información de 
 *      las calificaciones de un grupo de alumnos de forma textual. El siguiente dato a 
 *      leer de él correponde a una calificación cualitativa.
 *      El flujo <g> está asociado a un fichero binario que almacena las calificaciones
 *      leídas hasta el momento del fichero asociado a <f>
 * Post: Ha leído una calificación del fichero asociado a <f>, la calificación cualitativa
 *       y, salvo que ésta sea NP, la calificación cuantitativa, ha almacenado en el 
 *       fichero asociado a <g> la calificación cualitativa leida y, en su caso, la 
 *       cuantitativa y ha asignado a <notaCual> el valor de la calificación cuantitativa
 */
void copiarNota (ifstream& f, ofstream& g, int& notaCual) {
    char nota[4];
    f >> nota;
    if (strcmp(nota, "NP") == 0) {
        notaCual = NP;
    }
    else if (strcmp(nota, "SU") == 0) {
        notaCual = SU;
    }
    else if (strcmp(nota, "MH") == 0) {
        notaCual = MH;
    }
    else if (strcmp(nota, "SB") == 0) {
        notaCual = SB;
    }
    else if (strcmp(nota, "NO") == 0) {
        notaCual = NO;
    }
    else {
        notaCual = AP;
    }
    g.write(reinterpret_cast<char *>(&notaCual), sizeof(int));
    if (notaCual != NP) {
        int notaCuan;
        f >> notaCuan;
        g.write(reinterpret_cast<char *>(&notaCuan), sizeof(int));
    }
}


/*
 * Pre: <notasTextuales> es un fichero de texto que almacena la información de las
 *      calificaciones de un grupo de alumnos de forma textual. Ejemplo:
 *         51730586 AP 64
 *         51809151 NP SU 32
 *         51868593 SU 33 NP
 *         51878868 AP 65
 *         71920840 SU 30 NO 71
 *              .  .  .
 *         51943339 NP AP 51
 *         51971113 NO 71
 * Post: Ha creado el fichero <notasBinarias> que almacena una información similar
 *       a la de <notasTextuales> con la diferencia de que todos los datos están 
 *       codificados en binario como datos de tipo <int>. Ejemplo:
 *         <51730586> <AP> <64> <51809151> <NP> <SU> <32> <51868593> <SU> <33> <NP>
 *         <51878868> <AP> <65> <71920840> <SU> <30> <NO> <71> ... <51943339> <NP> 
 *         <AP> <51> <51971113> <NO> <71>
 */
bool generarNotas (const char notasTextuales[], const char notasBinarias[]) {
    ifstream f(notasTextuales);
    if (f.is_open()) {
        ofstream g(notasBinarias, ios::binary);
        // Intenta leer el código numérico del primer alumno
        int codigo;
        f >> codigo;
        while (!f.eof()) {
            // Almacena en el fichero asociado a <g> el código numérico del alumno
            g.write(reinterpret_cast<char *>(&codigo), sizeof(int));
            // Lee del fichero asociado a <f> la calificación del alumno en la
            // primera convocatoria y la almacena en el fichero asociado a <g>
            int notaCual;
            copiarNota(f, g, notaCual);
            if ((notaCual == NP) || (notaCual == SU)) {
                // Lee del fichero asociado a <f> la calificación del alumno en la
                // primera convocatoria y la almacena en el fichero asociado a <g>
                copiarNota(f, g, notaCual);
            }
            // Intenta leer el código numérico de un nuevo alumno
            f >> codigo;
        }
        // Libera los ficheros a sociados a los flujos <f> y <g>
        f.close();  g.close();
        // Se han almacenado exitosamente las califiones en el fichero binario que ha
        // estado asociado a flujo <g>
        return true;
    }
    else {
        // No se ha podido acceder al fichero <notasTextuales>
        return false;
    }
}

/*
 * Pre: <g> almacena el identificador, los nombres y apellidos relativos a
		un grupo de alumnos dispuestos de forma que están ordenados por
		orden alfabético de apellidos y <totalAlumnos> > 0
 * Post: La tabla lasNotas[0..totalAlumnos-1] almacena por orden alfabético 
 * 		 en sus <totalAlumnos> primeras componentes las calificaciones obtenidas 
 * 		 en la primera convocatoria, y en caso de no haber aprobado, de la segunda convcatoria
 * 		 por los alumnos registrados en el grupo de alumnos <g>
 */
void ordenAlfabeticoNotas (const Grupo g, Notas lasNotas[], const int totalAlumnos){
	/* Recorrido de los alumnos registrados en el grupo <g> */
	for (int i = 0; i < totalAlumnos; i++){
		/* Se obtiene el alumno i-ésimo registrado en el grupo
		 * y su correspondiente código de alumno */
		Alumno elAlumno = alumno(g,i);
		int elCodigo = codigo(elAlumno);
		/*
		 * Búsqueda sencuencial comenzando por el índice inferior
		 */
		int j = 0;
		bool encontrado = false;
		/* Todavía no se ha encontrado lo que se busca */
		while (!encontrado && j < totalAlumnos){
			/* No ha habido éxito tras buscar en lasNotas[0..j-1] */
			if (elCodigo == codigoAlumno(lasNotas[j])){
				/* Búsqueda concluida ya que el código de alumno
				 * del elemento lasNotas[j] es el dato buscado */
				encontrado = true;
			}
			else{
				/* La búsqueda debe continuar en el espacio lasNotas[j+1..totalAlumnos-1] */
				j++;
			}
			if (encontrado){
				/* Intercambio de las notas para ajutarlas 
				 * al ordenamiento en el que están dispuestos los alumnos */
				intercambiar(lasNotas[i],lasNotas[j]);
			}
		}
	}
	/* La tabla lasNotas[0..totalAlumnos-1] ha sido ordenada de acuerdo
	 * por orden alfabético de acuerdo con los alumnos registrados en <g> */
}

/*
 * Pre: <notaCual> >= -1 y <notaCual <= 4
 * Post: Devuelve en <nota> la correspondiente nota alfabética
 * 		 que equivale a la nota númerica <notaCual>
 */
void equivalencia (int& notaCual, char nota[]){
	if (notaCual == 4){
		strcpy(nota,"MH");
	}
	else if (notaCual == 3){
		strcpy(nota,"SB");
	}
	else if (notaCual == 2){
		strcpy(nota,"NO");
	}
	else if (notaCual == 1){
		strcpy(nota,"AP");
	}
	else if (notaCual == 0){
		strcpy(nota,"SU");
	}
	else{
		strcpy(nota,"NP");
	}
}

/*
 * Pre: <g> almacena el identificador, los nombres y apellidos relativos a
 *		un grupo de alumnos dispuestos de forma que están ordenados por
 * 		orden alfabético de apellidos. 
 * 		La tabla lasNotas[0..numAlumnos-1] almacena por orden alfabético 
 * 		en sus <numAlumnos> primeras componentes las calificaciones obtenidas 
 * 		en la primera convocatoria, y en caso de no haber aprobado, de la segunda convcatoria
 * 		por los alumnos registrados en el grupo de alumnos <g> y numAlumnos > 0
 * 
 * Post: Muestra por pantalla un listado con la información referente a las
 * 		 calificaciones obtenidas por los alumnos pertenecientes en el grupo <g> en la
 * 		 en la asignatura de Programación 1 en la primera convocatoria, 
 * 		 y en caso de no haber aprobado, en la segunda de acuerdo con el formato de
 * 		 salida especificado a continuación:
 * 
 * 					LISTADO DE CALIFICACIONES DE PROGRAMACION 1
 * 					===========================================
 * 
 * 
 * CODIGO  NOMBRE                  APELLIDOS                      FEBRERO   SEPTIEMBRE
 * ======  ======================= ============================== =======   ==========
 * 43762671 ANA ISABEL              ARTIGAS LOPEZ                  AP  6.7
 * 54042067 EULOGIO                 BENITO LACAMBRA                MH  9.7
 * 53424993 LAURA                   BESTEIRO CIFUENTES             NP        NO  8.5
 * 
 * 
 * 						.  .  .                           .  .  .
 * 
 * 
 * 5298222 NICOLAS                  BORAO GIMENO                    SU  4.2   SU  3.8
 * 52112820 ARTURO                  VELASCO DE LA FUENTE           NP        NP
 * 45161111 MARIA JOSE              ZARAGOZA SIERRA                NO  7.6
 * 
 * 
 */
void mostrarResultados (const Grupo g, const Notas lasNotas[], const int numAlumnos){
	const double BASE = 10.0;
	/* Muestra por pantalla la cabecera del listado */
	cout << "                LISTADO DE CALIFICACIONES DE PROGRAMACION 1" << endl;
	cout << "              =============================================== " << endl;
	cout << endl << endl;
	cout << "    CODIGO " << setw(10) << " NOMBRE " << setw(16) << 
			" APELLIDOS " << setw(19) << " FEBRERO " << setw(13) << 
			" SEPTIEMBRE " << endl;
	cout << "   ========   =========    ================     =======   ==========" << endl;
	
	/* Recorrido de los alumnos recogidos en <g> y de sus correspondientes notas
	 * recogidas en la tabla <lasNotas> ambos ordenados con el mismp orden */
	for (int i = 0; i < numAlumnos; i++){
		/* Han sido mostrados por pantalla i-1 alumnos */
		
		/* Obtención de los datos correspondientes al alumno i-ésimo */
		int identificador = codigoAlumno(lasNotas[i]);
		Alumno elAlumno = alumno(g,i);
		char nombreAlumno[LIMITE_NOMBRE];
		char apellidoAlumno[LIMITE_APELLIDOS];
		nombreCompleto(elAlumno, nombreAlumno, apellidoAlumno);
		int cualitativa1, cuantitativa1;
		int cualitativa2, cuantitativa2;
		
		convocatoria1(lasNotas[i], cualitativa1, cuantitativa1);
		convocatoria2(lasNotas[i], cualitativa2, cuantitativa2);
		
		char laNota1[2]; char laNota2[2];
		equivalencia(cualitativa1, laNota1);
		equivalencia(cualitativa2, laNota2);
		
		/* Muestreo de las calificaciones obtenidas */
		if (cualitativa1 > 0){
			/* Alumno aprobado en primera convocatoria */
			cout << fixed << setw(3) << " " << 
				setw(11) << left << identificador << 
				setw(12) << left << nombreAlumno  << 
				setw(22) << left << apellidoAlumno << 
				setw(4) << left << laNota1 <<
				setw(4) << left <<
				setprecision(1) << cuantitativa1 / BASE << endl;
		}
		else if ((cualitativa1 == 0) && (cualitativa2 >= 0)){
			/* Alumno suspendido en la primera convocatoria
			 * y que en la segunda se ha presentado independientemente
			 * de la nota obtenida */
			cout << fixed << setw(3) << " " <<
				setw(11) << left << identificador <<
				setw(12) << left << nombreAlumno <<
				setw(22) << left << apellidoAlumno << 
				setw(4) << left << laNota1 << 
				setw(6) << left << setprecision(1) << cuantitativa1 / BASE << 
				setw(4) << left << laNota2 << 
				setw(4) << left << 
				setprecision(1) << cuantitativa2 / BASE << endl;
		}
		else if ((cualitativa1 == -1) && (cualitativa2 != -1)) {
			/* Alumno no presentado en la primera convocatoria
			 * y que en la segunda se ha presentado independientemente
			 * de la nota obtenida */
			cout << fixed << setw(3) << " " << 
				setw(11) << left << identificador  <<
				setw(12) << left << nombreAlumno <<
				setw(22) << left << apellidoAlumno << 
				setw(10) << left << laNota1 << 
				setw(4) << left << laNota2 <<
				setprecision(1) << cuantitativa2 / BASE << endl;
		}
		else if ((cualitativa1 == -1) && (cualitativa2 == -1)){
			/* Alumno no presentado en las dos convocatoria */
			cout << fixed << setw(3) << " " << 
				setw(11) << left << identificador  << 
				setw(12) << left << nombreAlumno <<
				setw(22) << left << apellidoAlumno << 
				setw(10) << left << laNota1 <<  
				setw(4) << left << laNota2 << endl;
		}
		else{
			/* Alumno suspendido en la primera convocatoria 
			 * y no presentado en la segunda */
			cout << fixed << setw(3) << " " <<
				setw(11) << left << identificador  << 
				setw(12) << left << nombreAlumno <<
				setw(22) << left << apellidoAlumno << 
				setw(4) << left << laNota1 << 
				setw(6) << left << cuantitativa1 / BASE << 
				setw(4) << left << laNota2 << endl;
		}
	}
	/* Se ha mostrado por pantalla el listado completo que recoge
	 * la información relativa un grupo de alumnos y sus correspondientes
	 * calificaciones obtendidas en la asignatura de Programación 1 */
}

/* 
 * El programa gestiona las calificaciones obtenidas por un grupo de
 * alumnos en la asignatura de Programación 1 en la primera, y en el caso
 * de no haberla aprobado, de la segunda convocatoria. Muestra por pantalla
 * un listado con el código, los nombres, los apellidos y las calificaciones
 * obtendidas por los alumnos registrados en el grupo. 
 * La información se obtiene, por medio de un fichero de texto que recoge 
 * los códigos de identificación y los datos personales de los 
 * alumnos y, por un fichero binario que contiene las correspondientes 
 * calificaciones de la asignatura.
 * El listado de los alumnos se muestra en orden alfabético de apellidos,
 * y en caso de coincidencias, en orden alfabético de nombres.
 */
int main() {
	char FICHERO_TEXTUAL_ALUMNOS[64];
	//Nombre del fichero de texto a introducir por el usuario
	
	char FICHERO_BINARIO_USUARIO[64];
	// Nombre del fichero binario de notas a introducir por el usuario 
    
	const char FICHERO_TEXTUAL_NOTAS[64] = "../../datos/notasGrupo.txt";
	// Nombre de un fichero de texto que almacena las calificaciones de los alumnos
    // de ese mismo grupo (modificar el nombre si el nombre del fichero es distinto)
	
    const char FICHERO_BINARIO_NOTAS[64] = "../../datos/notasGrupo.bin";
	// Nombre de un fichero binario que almacena las calificaciones de los alumnos
    // de ese mismo grupo (modificar el nombre si interesa que el nombre del fichero 
    // binario a crear sea diferente
	
	
	
    // Intenta generar el fichero binario de calificaciones <FICHERO_BINARIO_NOTAS> a
    // partir de los datos del fichero textual de calificaciones <FICHERO_TEXTUAL_NOTAS>

    bool continuar = generarNotas(FICHERO_TEXTUAL_NOTAS, FICHERO_BINARIO_NOTAS);
    
	/* Si el fichero binario de notas se ha generado con éxito */
	if (continuar){
		/* Petición al ususario de los ficheros los ficheros */
		cout << "Fichero de alumnos del grupo: " << flush;
		cin >> FICHERO_TEXTUAL_ALUMNOS;
		cout << "Fichero binario de notas del grupo: " << flush;
		cin >> FICHERO_BINARIO_USUARIO;
	

		Grupo g;
		/* Lectura del fichero de texto de alumnos y formación del grupo */
		leerGrupo(FICHERO_TEXTUAL_ALUMNOS, g);
			
		/* Declaración de un flujo de entrada de datos */
		ifstream f2;
		f2.open(FICHERO_BINARIO_USUARIO);
		/* Fichero asociado al flujo de lectura */
		if (f2.is_open()){
			/* Si el fichero existe */
			int n;
			Notas lasNotas[LIMITE_GRUPO];
			
			/* Lectura de las notas del fichero binario */
			leerNotas(FICHERO_BINARIO_USUARIO, lasNotas, n);
			ordenAlfabeticoNotas(g, lasNotas, n);
			cout << endl << endl;
			int total = numAlumnos(g);
			
			/* Muestreo de los resultados por salida estándar */
			if (total > 0){
				mostrarResultados(g, lasNotas, n);
			}
			f2.close();
			/* Cierre del flujo de lectura */
		}
		else{
			/* Advierte del error al intentar abrir el fichero */
			cerr << " No se ha podido acceder al fichero " << FICHERO_BINARIO_USUARIO << endl;
		}
	}
	return 0;
}