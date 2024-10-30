#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXSTRING 100

typedef struct _word {
    char s[MAXSTRING];
    int count;
    struct _word *next;
} word;

void print_help() {
    fprintf(stderr, "wordcount imprime las palabras más frecuentes en un archivo de texto.\n");
    fprintf(stderr, "uso:\n");
    fprintf(stderr, " ./wordcount [-w <num palabras>] [-r] [<nombre archivo>]\n");
    fprintf(stderr, " ./wordcount -h\n");
    fprintf(stderr, "Opciones:\n");
    fprintf(stderr, " -h\t\t\tAyuda, muestra este mensaje\n");
    fprintf(stderr, " -w <num palabras>\tEspecifica el número de palabras a mostrar [default: 20]\n");
    fprintf(stderr, " -r\t\t\tMuestra frecuencia relativa\n");
}

int is_alpha(char c) {
    return isalpha((unsigned char)c);
}

void remove_non_alpha(char *s) {
    int i, j;
    for (i = 0, j = 0; s[i] != '\0'; i++) {
        if (is_alpha(s[i])) {
            s[j++] = tolower((unsigned char)s[i]);
        }
    }
    s[j] = '\0';
}

word *find_word(word *head, const char *s) {
    while (head != NULL) {
        if (strcmp(head->s, s) == 0) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

void insert_word(word **head, const char *s) {
    word *w = find_word(*head, s);
    if (w != NULL) {
        w->count++;
    } else {
        w = (word *)malloc(sizeof(word));
        if (w == NULL) {
            fprintf(stderr, "Error allocating memory\n");
            exit(EXIT_FAILURE);
        }
        strcpy(w->s, s);
        w->count = 1;
        w->next = *head;
        *head = w;
    }
}

void free_words(word *head) {
    while (head != NULL) {
        word *temp = head;
        head = head->next;
        free(temp);
    }
}

int wordcmp(const void *a, const void *b) {
    word *wa = *(word **)a;
    word *wb = *(word **)b;
    return wb->count - wa->count;
}

void print_words(word *head, int num_words, int relative, int total) {
    word **words_array;
    int i, n = 0;

    // Contar el número de palabras en la lista
    for (word *w = head; w != NULL; w = w->next) {
        n++;
    }

    // Alocar memoria para el array de palabras
    words_array = malloc(n * sizeof(word *));
    if (words_array == NULL) {
        fprintf(stderr, "Error allocating memory\n");
        exit(EXIT_FAILURE);
    }

    // Llenar el array de palabras con los elementos de la lista enlazada
    i = 0;
    for (word *w = head; w != NULL; w = w->next) {
        words_array[i++] = w;
    }

    // Ordenar el array de palabras en función de su frecuencia
    qsort(words_array, n, sizeof(word *), wordcmp);

    // Determinar cuántas palabras mostrar
    int words_to_print = (num_words > 0 && num_words <= n) ? num_words : 20;

    // Mostrar las palabras según las opciones seleccionadas
    for (i = 0; i < words_to_print; i++) {
        if (relative) {
            printf("%s\t%.3f\n", words_array[i]->s, (float)words_array[i]->count / total);
        } else {
            printf("%s\t%d\n", words_array[i]->s, words_array[i]->count);
        }
    }

    // Liberar la memoria utilizada por el array de palabras
    free(words_array);
}

int main(int argc, char *argv[]) {
    int num_words = 0, relative = 0;
    FILE *fp = stdin;
    word *head = NULL;
    char s[MAXSTRING];
    int total_words = 0;

    // Procesar los argumentos de línea de comandos
    if (argc == 1) {
        print_help();
        return EXIT_SUCCESS;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            print_help();
            return EXIT_SUCCESS;
        } else if (strcmp(argv[i], "-w") == 0) {
            if (i + 1 < argc && isdigit(*argv[i + 1])) {
                num_words = atoi(argv[++i]);
            } else {
                num_words = 20; // Establecer 20 como valor predeterminado
            }
        } else if (strcmp(argv[i], "-r") == 0) {
            relative = 1;
        } else {
            fp = fopen(argv[i], "r");
            if (fp == NULL) {
                fprintf(stderr, "Error: no se puede abrir el archivo %s\n", argv[i]);
                return EXIT_FAILURE;
            }
        }
    }

    // Leer el archivo o la entrada estándar y contar las palabras
    while (fscanf(fp, "%99s", s) == 1) {
        remove_non_alpha(s);
        if (s[0] != '\0') {
            insert_word(&head, s);
            total_words++;
        }
    }

    // Cerrar el archivo si se abrió
    if (fp != stdin) {
        fclose(fp);
    }

    // Imprimir las palabras más frecuentes según las opciones seleccionadas
    print_words(head, num_words, relative, total_words);

    // Liberar la memoria utilizada por la lista de palabras
    free_words(head);

    return EXIT_SUCCESS;
}
