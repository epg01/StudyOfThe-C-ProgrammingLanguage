/**
 *     *********************************************************************************************************************************
 *     *                Problemas resueltos del libro programming in C.                                                                *
 *     *                Exercise 1-12. Write a program that prints its input one word per line.                                        *
 *     *                                                                                                                               *
 *     *                Haremos este ejercicio con tres formas posibles, una guardando todo en un vector, luego utilizando puntero     *
 *     *                (esto es para imprimirlo con la funcion printf) luego utilizaremos la funcion putchar como                     *
 *     *                con el metodo que hicimos en la Section 1.5.4 (con macros) y tambien lo haremos con la solucion que nos dejo   *
 *     *                El libro.                                                                                                      *
 *     *                                                                                                                               *
 *     *********************************************************************************************************************************
 */

//IMPORTANTE: UN ERROR QUE AUN NO HE PODIDO SOLUCIONAR A SIDO EL DE ESCRIBIR ALGO Y LUEGO ESCRIBIR EOF, CLARAMENTE HAY UN ERROR AHI

#include <stdio.h>    // le decimos al compilar que incluya  la libreria stdio.h para poder utilizar el valor EOF y la funcion printf

// Aqui iran los prototipos de las funciones
void MetodoConMacros(void);
void MetodoDelLibro(void);
void MetodoConPunterosYArray(void);


int main(void)
{
        printf("Forma 1, el ejercicio que hice con macros\n");
	MetodoConMacros();
        printf("Forma 2, funcion Metodologia del libro\n");
	MetodoDelLibro();
	printf("Forma 3, funcion Metodologia arary puntero\n");
	MetodoConPunterosYArray();
	return (0);
}
// Utilice estas dos macros, para no ecribir todo estas condiciones en la sentencia del if.

#define IAMAWORD(x) (((x) != (' ')) && ((x) != ('\t')) && ((x) != ('\n')) && ((x) != ('\0')))
#define ESTOYFUERADEUNAPALABRA(y) (((y) == (' ')) || ((y) == ('\t')) || ((y) == ('\n')))

#define VALORPORDEFECTO  '\0'   /* Este valor lo tendra al iniciar el programa, para solucionar cierto errores
				   El cual consistia en: al escribir por ejemplo "    hola" daba un salto de linea, por el espacio en blanco
				   Con este valor por defecto solucione dicho error.*/
void MetodoConMacros(void)     // Se definio una funcion que no retorna ni recina nada.
{
	int c;                 // Esta variable tipo entera, sera el siguiente caracter de entrada (estara en el presente)
	int temp;              // Esta variable tipo entera, estara un paso atras de c, para evaluar si esta o no en una palabra.

 	temp = VALORPORDEFECTO;             // Inicializamos a la variable temp por defecto con la contante simbolica para solucionar el error antes dicho.
        while ((c = getchar()) != EOF)
	{
		if(IAMAWORD(temp) && ESTOYFUERADEUNAPALABRA(c))    /* Aqui pasa toda la magia, y no se imprimira una nueva linea hasta que temp este en una palabra
								      y c no sea parte de una palabra. */
			putchar('\n');
		else if (IAMAWORD(c))                              /* Con esta else if, se soluciono el problema de saltos de linea "agregados desde el teclado" */
			putchar(c);
		temp = c;                                          /* Temp estara un paso atras de C */
	}
	return ;
}

//  Se definieron dos constante simbolicas.

#define OUT  0             // Verificamos que getchar no esta dentro de una palabra
#define IN   1             // Getchar esta dentro de una palabra

void MetodoDelLibro(void)      // Se definio una funcion en donde el parametro de void y su retorno igual
{
	int c;                 // Almacenara el caracter que le entregue getchar
	int state;             // Verificamos el estado de getchar.

	state = OUT;           // Al inicio getchar no esta dentro de una palabra, ya que esta esperando una secuencia de caracteres que son enviados desde el teclado
	while ((c = getchar()) != EOF)
	{
		if (ESTOYFUERADEUNAPALABRA(c))     // Mientras la variable c sea igual a un espacio en blanco, tabulador o nueva linea no hara nada
		{                                  /* Esto es importante por que con esta condicion nos aseguramos que podemos escribir esto : "   HOLA MUNDO  " y 
						      el putchar del else no imprimira los espacio ni nuevas lineas ni tabuladores, SOLO IMPRIMIRA CARACTERES VISIBLES */
			if(state == IN)            /* Aqui esta la magia del programa, ya que con esta condicion solo imprimiremos saltos de lineas fin de palabra. */
				putchar('\n');
			state = OUT;
		}
		else if(state == OUT)
		{
			state = IN;
			putchar(c);              /* Este putchar es necesario aqui ta que sin este no imprimiriamos la primera letra de una palabra*/
		}
		else
			putchar(c);              /* Con este otro putchar imprimiremos el resto de las palabras */
	}
	return ;                    // Eso es optativo, no retornara nada o retornada basura si la funcion retorna algo diferente a void (creo).
}


// ESTE ULTIMO AUN NO ESTA TERMINADO.


/* Intentaremos hacer otro solucion del problema pero esta vez guardandolo todo en un vector y luego imprimiremos cada palabra en una linea 
   aqui tambien introduciremos la aritmetica de punteros, para trabajar con los dos de una vez y no hacer algo similar para otra funcion solo con punteros
   ya que es lo mismo en cierto punto. */

#define ALLOCSIZE 1000    // Se definio una constante simbolica, esta será utilizada para definir el tamaño del vector.
int array[ALLOCSIZE];
int *puntero = array;

void MetodoConPunterosYArray(void)
{
	int c;
	int i = 0;

	puntero++;
	while((c = getchar()) != EOF)
		array[i++] = c;
/*	if ((array[i] != EOF) && IAMAWORD(array[i])){
		array[i] = EOF;
		putchar('\n');
	}
*/
	array[i] = EOF;
	i = 0;
	while(*puntero != EOF)
	{
		if(IAMAWORD(*puntero) && ESTOYFUERADEUNAPALABRA(array[i++]))
		{
			puntero++;
			i++;
			putchar('\n');
		}
		else if (IAMAWORD(*puntero)){
			putchar(*puntero);
			puntero++;
			i++;
		}
	}
	return ;
}
