/*
 * ==============================
 * Trabajo de Programación 1 
 * Autor: Rubén Rodríguez Esteban
 * NIP : 737215
 * Fecha de entrega 28-1-2018
 * ==============================
 */
 

/*
 * Fichero de interfaz grupo.h del módulo grupo
 */

#ifndef GRUPO_H

#define GRUPO_H

// Los nombres de los alumnos han de tener menos de LIMITE_NOMBRE caracteres
const int LIMITE_NOMBRE = 20;
// Los apellidos de los alumnos han de tener menos de LIMITE_APELLIDOS caracteres
const int LIMITE_APELLIDOS = 24;
// Un grupo de alumnos ha de estar integrado por un número de alumnos que no
// sobrepase LIMITE_GRUPO
const int LIMITE_GRUPO = 180;

/*
 * Un dato de tipo Alumno permite representar la informacion básica de un alumno 
 * universitario: su código numérico, su nombre y sus apellidos
 */
struct Alumno {
    private:
		// EXPLICAR CAMPOS
        // Estructura interna de un dato de tipo Alumno
		int codigoNumerico;
        char nombre[LIMITE_NOMBRE];
		char apellidos[LIMITE_APELLIDOS];
    public:
        // Funciones para gestionar datos de tipo Alumno
        friend Alumno definir (const int codigo, const char nombre[], 
                                                 const char apellidos[]);
        friend int codigo (const Alumno a);
        friend void nombreCompleto (const Alumno a, char nombre[], char apellidos[]);
};

/*
 * Post: El alumno que ha devuelto tiene como código numérico <codigo> y su nombre 
 *       y apellidos son los definidos por las cadenas <nombre> y <apellidos>,
 *       respectivamente
 */
Alumno definir (const int codigo, const char nombre[], const char apellidos[]);
				
/*
 * Post: Devuelve el código numérico del alumno <a>
 */
int codigo (const Alumno a);

/*
 * Post: Ha asignado a <nombre> la cadena de caracteres con el nombre del alumno <a>
 *       y ha asignado a <apellidos> la cadena de caracteres con sus apellidos
 */
void nombreCompleto (const Alumno a, char nombre[], char apellidos[]);

/*
 * Un dato de tipo Grupo permite representar la informacion de un grupo de alumnos
 * universitarios
 */
struct Grupo {
    private:
		// EXPLICAR LOS CAMPOS
        // Estructura interna de un dato de tipo Alumno
        Alumno listado[LIMITE_GRUPO];
		int numAlumnos;
    public:
        // Funciones para gestionar datos de tipo Grupo
        friend void leerGrupo (const char nombreFichero[], Grupo& g);
        friend int numAlumnos (const Grupo& g);
        friend Alumno alumno (const Grupo& g, const int i);
};

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
void leerGrupo (const char nombreFichero[], Grupo& g);

/*
 * Post: Devuelve el número de alumnos del grupo <g>
 */
int numAlumnos (const Grupo& g);

/*
 * Pre: i >= 1 y i <= numAlumnos(g)
 * Post: Devuelve el <i>-ésimo alumno del grupo <g>
 */
Alumno alumno (const Grupo& g, const int i);

// Posibles calificaciones cualitativas de una asignatura en una convocatoria
const int MH = 4;       // matricula de honor
const int SB = 3;       // sobresaliente
const int NO = 2;       // notable
const int AP = 1;       // aprobado
const int SU = 0;       // suspenso
const int NP = -1;      // no presentado

/*
 * Un dato de tipo Notas permite representar las calificaciones obtenidas por un alumno
 * en una asignatura en las dos convocatorias de las que dispone en un curso académico
 */
struct Notas {
    private:
        // Estructura interna de un dato de tipo Notas
		int elCodigo;
		int laNotaCualC1;
		int laNotaCuanC1;
		int laNotaCualC2;
		int laNotaCuanC2;
    public:
        // Funciones para gestionar datos de tipo Notas
        friend bool leerNotas (const char nombreFichero[], Notas lasNotas[], int& numAlumnos);
        friend int codigoAlumno (const Notas& n);
        friend void convocatoria1 (const Notas& n, int& cualitativa, int& cuantitativa);
        friend void convocatoria2 (const Notas& n, int& cualitativa, int& cuantitativa);
};


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
bool leerNotas (const char nombreFichero[], Notas lasNotas[], int& numAlumnos);

/*
 * Post: Devuelve el código numérico del alumno cuyas calificaciones son <n>
 */
int codigoAlumno (const Notas& n);

/*
 * Pre: Las notas <n> presenta calificación en primera convocatoria
 * Post: Ha asignado a <cualitativa> la calificación cualitativa en primera convocatoria
 *       del alumno cuyas calificaciones son <n> y, si la calificación cualitativa no es
 *       la de "no presentado", entonces ha asignado a <cuantitativa> la calificación 
 *       cuantitativa en primera convocatoria
 */
void convocatoria1 (const Notas& n, int& cualitativa, int& cuantitativa);

/*
 * Pre: Las notas <n> presentan calificaciones en primera convocatoria (suspenso o no
 *      presentado) y en segunda convocatoria
 * Post: Ha asignado a <cualitativa> la calificación cualitativa en segunda convocatoria
 *       del alumno cuyas calificaciones son <n> y, si la calificación cualitativa no es
 *       la de "no presentado", entonces ha asignado a <cuantitativa> la calificación 
 *       cuantitativa en segunda convocatoria
 */
void convocatoria2 (const Notas& n, int& cualitativa, int& cuantitativa);

#endif
