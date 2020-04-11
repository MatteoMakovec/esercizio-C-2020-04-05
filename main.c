//scrivere un programma che legge da stdin una riga alla volta (la riga si considera terminata dal
//carattere \n).
//
//la lunghezza della riga è arbitraria, non fare ipotesi sulla massima lunghezza di riga.
//[in questo esercizio, occorre immagazzinare l'intera riga ed anche le precedenti].
//
//confrontare la riga appena letta con tutte le precedenti righe lette:
//il confronto parte dalla penultima riga e va a ritroso fino alla prima riga letta.
//
//se la riga appena letta ha un precedente, scrivere su stdout il messaggio
//"***questa riga è stata già letta %d righe fa***", dove viene indicata la posizione relativa della riga
//identica rispetto alla riga attuale
//(può accadere che una riga si ripresenti più di una volta; scrivere tutte le volte
//che si ripresenta)
//
//il programma termina in caso di EOF su stdin.
//
//esempio, I: significa input proveniente da stdin, O: indica l'output del programma su stdout
//
//I: xyz0000
//I: 1234
//I: 0000
//I: zzzzz
//I: 1234
//O: ***questa riga è stata già letta 3 righe fa***
//I: abcdefg
//I: 1234
//O: ***questa riga è stata già letta 2 righe fa***
//O: ***questa riga è stata già letta 5 righe fa***


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


typedef struct{
	char *char_array;
	int length;
} line;


void compareLines(line *lines, int size);
void letsCompare(char *array_toCompare, char *array_pattern, int length, int line);


int main(int argc, char *argv[]) {
	int ch;
	int count_lines = 1;
	int count_chars = 1;
	char *readLine = calloc(count_chars, sizeof(char));
	line *lines = calloc(count_lines, sizeof(line));

	while((ch = getchar()) != EOF){
		if(ch == '\n'){
			lines[count_lines - 1].char_array = readLine;
			lines[count_lines - 1].length = count_chars;
			compareLines(lines, count_lines);
			count_lines++;
			count_chars = 1;
			readLine = calloc(count_chars, sizeof(char));
			if (readLine == NULL) {
				perror("calloc readLine error!");
				exit(EXIT_FAILURE);
			}
			lines = realloc(count_lines, sizeof(line));
			if (lines == NULL) {
				perror("realloc lines error!");
				exit(EXIT_FAILURE);
			}
		}
		else{
			lines[count_lines -1].char_array = realloc(lines[count_lines -1].char_array, count_chars * sizeof(char));
			if (readLine == NULL) {
				perror("realloc readLine error!");
				exit(EXIT_FAILURE);
			}

			lines[count_lines -1].char_array[count_chars -1] = ch;
			lines[count_lines -1].length = count_chars;
			count_chars++;

		}
	}

	return EXIT_SUCCESS;
}


void compareLines(line *lines, int size) {
	for(int i = size-2; i > 0; i--){
		if(lines[i].length == lines[size-1].length){
			letsCompare(lines[i].char_array, lines[size-1].char_array, lines[i].length, size-i);
		}
	}
}

void letsCompare(char *array_toCompare, char *array_pattern, int length, int line) {
	if(strcmp(array_toCompare, array_pattern)){
		printf("***questa riga è stata già letta %d righe fa***", line);
	}
}