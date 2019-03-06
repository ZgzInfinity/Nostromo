/*
 * ==============================
 * Trabajo de Programación 1 
 * Autor: Rubén Rodríguez Esteban
 * NIP : 737215
 * Fecha de entrega 28-1-2018
 * ==============================
 */
 
#include <iostream>
#include <fstream>
#include <cstring>
#include "grupo.h"

using namespace std;

const char DELIMITADOR = ',';
const char SALTO_LINEA = '\n';

/*
 * Post: El alumno que ha devuelto tiene como código numérico <codigo> y su nombre 
 *       y apellidos son los definidos por las cadenas <nombre> y <apellidos>,
 *       respectivamente
 */
Alumno definir (const int codigo, const char nombre[], const char apellidos[]){
	Alumno a;
	a.codigoNumerico = codigo;
	strcpy(a.nombre, nombre);
	strcpy(a.apellidos, apellidos);
	return a;
}

/*
 * Post: Devuelve el código numérico del alumno <a>
 */
int codigo (const Alumno a){
	return a.codigoNumerico;
}


/*
 * Post: Ha asignado a <nombre> la cadena de caracteres con el nombre del alumno <a>
 *       y ha asignado a <apellidos> la cadena de caracteres con sus apellidos
 */
void nombreCompleto (const Alumno a, char nombre[], char apellidos[]){
	strcpy(nombre, a.nombre);
	strcpy(apellidos, a.apellidos);
}


/*
 * Pre: <nombreFichero> es el nombre del fichero de texto que almacena la información 
 *      de todos los alumnos de un grupo. cada línea del fichero define un alumno del
 *      grupo con el siguiente formato:
 *      555423 MARTIN PEREZ,LUIS CARLOS
 *      82552 LOPEZ DE LA IGLESIA,ANDREA
 *              .   .   .
 * Sintaxis BNF de los datos de este fichero:
 *      <ficheroAlumnos> ::= {  <alumno>  }
 *      <alumno> ::= <codigoNumerico> <blanco> <apellidos> <coma> <nombre> fin_linea
 *      <codigoNumerico> ::= literal_entero
 *      <apellidos> ::= literal_string
 *      <nombre> ::= literal_string
 *      <blanco> ::= " "
 *      <coma>   ::= ","
 * Post: Ha asignado a <g> un dato de tipo Grupo que gestiona la información de todos
 *       los alumnos que constan en el fichero <nombreFichero>
 */
void leerGrupo (const char nombreFichero[], Grupo& g){
	g.numAlumnos = 0;
	/* Declaración de un flujo de entrada de datos */
	ifstream f;
	f.open(nombreFichero);
	if(f.is_open()){
		/* Si se ha abierto el fichero bien */
		int codigoAlumno;
		f >> codigoAlumno;
		while (!f.eof()){
			char nombreAlumno[LIMITE_NOMBRE];
			char apellidosAlumno[LIMITE_APELLIDOS];
			
			/* Obtiene el identificador, el nombre y los apellidos del alumno */ 
			f.getline(apellidosAlumno, LIMITE_APELLIDOS, DELIMITADOR);
			f.getline(nombreAlumno, LIMITE_NOMBRE, SALTO_LINEA);
			Alumno a = definir(codigoAlumno, nombreAlumno, apellidosAlumno);
			
			/* El alumno leído es almacenado en el grupo */
			g.listado[g.numAlumnos + 1] = a;
			g.numAlumnos++;
			f >> codigoAlumno;
			
			/* El grupo ha sido creado con los alumnos
			 * almacenados en el fichero */
		}
		/* Cierre del flujo asociado al fichero */
		f.close();
		/*
		 * Ordenación del grupo por orden alfabético por el método de selección
		 */
		for (int i = 1; i <= g.numAlumnos - 1; i++){
			/* Los alumnos de g.listado[0..i-1] ya están ordenados alfabeticamente */
			/* Selecciona el menor alumno de g.listado[i..g.numAlumnos-1] alfabeticamente */
			int indiceMenor = i;
			char nombreMayor[LIMITE_NOMBRE];
			char apellidosMayor[LIMITE_APELLIDOS];
			Alumno alumnoMayor = alumno(g, i);
			nombreCompleto(alumnoMayor, nombreMayor, apellidosMayor);
			for (int j = i + 1; j <= g.numAlumnos; j++){
				/* g.listado[indiceMenor] es el menor de g.listado[i..j-1] en orden alfabético */
				char nombreNuevo[LIMITE_NOMBRE];
				char apellidosNuevo[LIMITE_APELLIDOS];
				Alumno alumnoNuevo = alumno(g,j);
				nombreCompleto(alumnoNuevo, nombreNuevo, apellidosNuevo);
				if (strcmp(apellidosNuevo, apellidosMayor) < 0){
					/* Comparación de los alumnos por apellido */
					indiceMenor = j;
					alumnoMayor = alumno(g, indiceMenor);
					nombreCompleto(alumnoMayor, nombreMayor, apellidosMayor);
				}
				else if (strcmp(apellidosNuevo, apellidosMayor) == 0){
					/* Comparación de los alumnos por nombre */
					if (strcmp(nombreNuevo, nombreMayor) < 0) 
					indiceMenor = j;
				}
				/* g.listado[indiceMenor] es el menor de g.listado[i..j] en orden alfabético */
			}
			/*g.listado[indiceMenor] es el menor de g.listado[i..g.numAlumnos-1] en orden alfabético */
			/* Permuta los alumnos */
			Alumno aux = g.listado[i];
			g.listado[i] = g.listado[indiceMenor];
			g.listado[indiceMenor] = aux;
		}
		/* Los alumnos del grupo <g> ya están ordenados por orden alfabético*/
	}
	else{
			/* Avierte del error al intentar abrir el fichero */
			cerr << "No se ha podido acceder al fichero " << nombreFichero << endl;
	}
}




/*
 * Post: Devuelve el número de alumnos del grupo <g>
 */
int numAlumnos (const Grupo& g){
	return g.numAlumnos;
}


/*
 * Pre: i >= 1 y i <= numAlumnos(g)
 * Post: Devuelve el <i>-ésimo alumno del grupo <g>
 */
Alumno alumno (const Grupo& g, const int i){
	return g.listado[i];
}


/*
 * Pre: <nombreFichero> es el nombre del fichero binario que almacena las calificaciones
 *      de todos los alumnos en la primera y, en caso de no habe aprobado, en la segunda 
 *      convocatoria con la siguiente sintaxis BNF:
 *          <ficheroNotas> ::= { <notas> }
 *          <notas> ::= <codigoAlumno> <cualitativa> <cuantitativa> 
 *                                     [ <cualitativa> <cuantitativa> ]
 *          <codigoAlumno> ::= <int>
 *          <cualitativa> ::= <int>
 *          <cuantitativa> ::= <int>
 *       Las calificaciones cualitativas pueden tomar únicamente los valores de las 
 *       constantes MH, SB, NO, AP, SU o NP.
 *       Las calificaciones cuantitativas se expresan en décimas de punto, pudiendo estar 
 *       comprendidas entre una calificación mínima de 0 (corresponde a una nota de 0.0) 
 *       y una calificación máxima de 100 (corresponde a una nota de 10.0).
 * Post: En el caso de que no se pueda acceder al fichero <nombreFichero> entonces ha
 *       devuelto <false>; si se puede acceder entonces ha asignado a <numNotas> el número 
 *       de alumnos cuyas calificaciones están almacenadas en el fichero <nombreFichero> 
 *       y ha asignado a lasNotas[0..numAlumnos-1] las calificaciones de dichos alumnos 
 *       y ha devuelto <true>
 */
bool leerNotas (const char nombreFichero[], Notas lasNotas[], int& numNotas){
	ifstream f;
	f.open(nombreFichero,ios::binary);
	numNotas = 0;
	if(f.is_open()){
		int codigoAlumno;
		f.read(reinterpret_cast <char*>(&codigoAlumno),sizeof(int));
		while (!f.eof()){
			lasNotas[numNotas].elCodigo = codigoAlumno;
			int notCualC1;
			f.read(reinterpret_cast <char*>(&notCualC1),sizeof(int));
			lasNotas[numNotas].laNotaCualC1 = notCualC1;
			if (notCualC1 != NP && notCualC1 <= SU){
				int notCuanC1;
				f.read(reinterpret_cast <char*>(&notCuanC1),sizeof(int));
				lasNotas[numNotas].laNotaCuanC1 = notCuanC1;
				int notCualC2;
				f.read(reinterpret_cast <char*>(&notCualC2),sizeof(int));
				lasNotas[numNotas].laNotaCualC2 = notCualC2;
				if (notCualC2 != NP){
					int notCuanC2;
					f.read(reinterpret_cast <char*>(&notCuanC2),sizeof(int));
					lasNotas[numNotas].laNotaCuanC2 = notCuanC2;
				}
			}
			else if (notCualC1 != NP && notCualC1 > SU){
				int notCuanC1;
				f.read(reinterpret_cast <char*>(&notCuanC1),sizeof(int));
				lasNotas[numNotas].laNotaCuanC1 = notCuanC1;
			}
			else if (notCualC1 == NP){
				int notCualC2;
				f.read(reinterpret_cast <char*>(&notCualC2),sizeof(int));
				lasNotas[numNotas].laNotaCualC2 = notCualC2;
				if (notCualC2 != NP){
					int notCuanC2;
					f.read(reinterpret_cast <char*>(&notCuanC2),sizeof(int));
					lasNotas[numNotas].laNotaCuanC2 = notCuanC2;
				}
			}
			numNotas++;
			f.read(reinterpret_cast <char*>(&codigoAlumno),sizeof(int));
		}
		f.close();
		return true;
	}
	else{
		cerr << "No se ha podido abrir el fichero " << nombreFichero << endl;
		return false;
	}
}


/*
 * Post: Devuelve el código numérico del alumno cuyas calificaciones son <n>
 */
int codigoAlumno (const Notas& n){
	return n.elCodigo;
}


/*
 * Pre: Las notas <n> presenta calificación en primera convocatoria
 * Post: Ha asignado a <cualitativa> la calificación cualitativa en primera convocatoria
 *       del alumno cuyas calificaciones son <n> y, si la calificación cualitativa no es
 *       la de "no presentado", entonces ha asignado a <cuantitativa> la calificación 
 *       cuantitativa en primera convocatoria
 */
void convocatoria1 (const Notas& n, int& cualitativa, int& cuantitativa){
	cualitativa = n.laNotaCualC1;
	cuantitativa = n.laNotaCuanC1;
}

/*
 * Pre: Las notas <n> presentan calificaciones en primera convocatoria (suspenso o no
 *      presentado) y en segunda convocatoria
 * Post: Ha asignado a <cualitativa> la calificación cualitativa en segunda convocatoria
 *       del alumno cuyas calificaciones son <n> y, si la calificación cualitativa no es
 *       la de "no presentado", entonces ha asignado a <cuantitativa> la calificación 
 *       cuantitativa en segunda convocatoria
 */
void convocatoria2 (const Notas& n, int& cualitativa, int& cuantitativa){
	cualitativa = n.laNotaCualC2;
	cuantitativa = n.laNotaCuanC2; 	
}
