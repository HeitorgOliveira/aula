#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operacoes.h"

#define max(a, b) ((a) > (b) ? (a) : (b))

// Soma de dois números representados por strings
char* add(char* str1, char* str2) {
    int tam = max(strlen(str1), strlen(str2));
    int carry = 0;
    int sum = 0;

    char* res = calloc(tam + 2, sizeof(char));

    // Adiciona zeros à esquerda para igualar o tamanho das strings
    char* tmp1 = calloc(tam + 1, sizeof(char));
    char* tmp2 = calloc(tam + 1, sizeof(char));
    memset(tmp1, '0', tam);
    memset(tmp2, '0', tam);
    strcpy(tmp1 + (tam - strlen(str1)), str1);
    strcpy(tmp2 + (tam - strlen(str2)), str2);

    for (int i = tam - 1; i >= 0; i--) {
        sum = carry + (tmp1[i] - '0') + (tmp2[i] - '0');
        res[i + 1] = (sum % 10) + '0';
        carry = sum / 10;
    }

    if (carry) {
        res[0] = carry + '0';
        free(tmp1);
        free(tmp2);
        return res;
    } else {
        free(tmp1);
        free(tmp2);
        return res + 1;
    }
}

// Subtração de dois números representados por strings
char* sub(char* str1, char* str2) {
    int tam1 = strlen(str1);
    int tam2 = strlen(str2);
    int tam = max(tam1, tam2); 

    char* res = calloc((tam + 2), sizeof(char));
    memset(res, '0', tam + 1);

    int empresta = 0, i = tam1 - 1, j = tam2 - 1, k = tam;

    while (i >= 0 || j >= 0 || empresta) {
        int digito1 = (i >= 0) ? str1[i--] - '0' : 0;
        int digito2 = (j >= 0) ? str2[j--] - '0' : 0;
        digito2 += empresta;

        if (digito1 < digito2) {
            digito1 += 10;
            empresta = 1;
        } else {
            empresta = 0;
        }

        res[k--] = (digito1 - digito2) + '0';
    }

    while (*res == '0' && *(res + 1)) res++;

    return res;
}

// Multiplica um número, representado por uma string, por uma potência de 10
char* potencia_de_10(const char* str, int potencia) {
    int tam = strlen(str);
    char* res = calloc(tam + potencia + 1, sizeof(char));

    strcpy(res, str);
    for (int i = 0; i < potencia; i++) {
        res[tam + i] = '0';
    }
    res[tam + potencia] = '\0';

    return res;
}

char *multiplicacao(const char* n1, const char* n2)
{

}