#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operacoes.h"

char * karatsuba(char *str1, char *str2);
void dividirString(const char *str, char **primeiraMetade, char **segundaMetade);
char* intParaString(int num);
void pad_strings(char **str1, char **str2, int len1, int len2);
char* multiply_single_digits(const char* str1, const char* str2);

int main(void)
{
    char *n1 = malloc(9999 * sizeof(char));
    char *n2 = malloc(9999 * sizeof(char));
    scanf("%s %s", n1, n2);
    printf("%s", karatsuba(n1, n2));
    free(n1);
    free(n2);
    return (0);
}   

char *karatsuba(char *str1, char *str2)
{
    //Decide qual a maior string e assina seu tamanho em m
    int m = 1;
    int tamstr1 = strlen(str1);
    int tamstr2 = strlen(str2);
    if(tamstr1 > tamstr2)
    {
        m = tamstr1;
    }
    else
    {
        m = tamstr2;
    }
    int meio = m/2;
    //Caso os números sejam muito pequenos, a multiplicação é realizada normalmente
    if (m <= 3)
    {
        char *resultado = multiplicacao(str1, str2);
        return resultado;
        //intParaString(atof(resultado));
    }

    //iguala o tamanho dos numeros
    pad_strings(&str1, &str2, tamstr1, tamstr2);

    //Chama uma função que multiplica numeros de 1 digito, caso não sejam de um digito, retorna vazio
    char * digitos = multiply_single_digits(str1, str2);

    if (digitos != NULL)
    {
        return digitos;
    }

    //Separa os dois numeros em 4 metades
    char *inf1 = strndup(str1, meio);
    char *inf2 = strndup(meio + str1, meio);
    char *sup1 = strndup(str2, meio);
    char *sup2 = strndup(meio + str2, meio);
    
    char * z0 = karatsuba(inf1, inf2);

    //separa as operacoes
    char *soma1 = add(inf1, sup1);
    char *soma2 = add(inf2, sup2);

    //chama a funcao karatsuba
    char *z1 = karatsuba(soma1, soma2);
    char *z2 = karatsuba(sup1, sup2);

    //Novamente separa algumas operações em partes
    char *parte1 = potencia_de_10(z2, meio * 2);
    char *parte2 = sub(sub(z1, z2), z0);
    char *parte3 = add(potencia_de_10(parte2, meio), z0);
    char *somateste = add(parte1, parte3);
    /*if (strlen(somateste) >= strlen(str1) + strlen(str2))
    {
        int fim = strlen(somateste);
        printf("tam somateste: %i\ntam str1: %i\ntam str2: %i\n", strlen(somateste), strlen(str1), strlen(str2));
        char * hahaha = malloc((strlen(str1) + strlen(str2)) * sizeof(char));
        for(int i = 0; i < fim; i++)
        {
            if (i > strlen(str1) + strlen(str2))
            {
                printf("acabou o i\n");
                break;
            }
            hahaha[i] = somateste[i];
        }
        free(hahaha);
    }*/
    free(inf1);
    free(inf2);
    free(sup2);
    free(sup1);
    inf1 = NULL;
    inf2 = NULL;
    sup1 = NULL;
    sup2 = NULL;

    return (add(parte1, parte3));
}

void dividirString(const char *str, char **primeiraMetade, char **segundaMetade) {
    size_t comprimento = strlen(str);
    size_t metade = comprimento / 2;

    *primeiraMetade = (char *)malloc((metade + 1) * sizeof(char));
    *segundaMetade = (char *)malloc((comprimento - metade + 1) * sizeof(char));

    if (*primeiraMetade == NULL || *segundaMetade == NULL) {
        exit(EXIT_FAILURE);
    }

    strncpy(*primeiraMetade, str, metade);
    (*primeiraMetade)[metade] = '\0';

    strcpy(*segundaMetade, str + metade);
}


char* intParaString(int num) {
    size_t tamanho = snprintf(NULL, 0, "%d", num) + 1;

    char *resultado = (char *)malloc(tamanho);
    if (resultado == NULL) {
        perror("Falha ao alocar memória");
        exit(EXIT_FAILURE);
    }

    snprintf(resultado, tamanho, "%d", num);

    return resultado;
}

void pad_strings(char **str1, char **str2, int len1, int len2) {
    if (len1 == len2) {
        return;
    }

    if (len2 > len1) {
        while (len1 < len2) {
            for (int i = len1; i >= 0; i--) {
                (*str1)[i + 1] = (*str1)[i];
            }
            (*str1)[0] = '0';
            len1++;
        }
    }
    else {
        while (len2 < len1) {
            for (int i = len2; i >= 0; i--) {
                (*str2)[i + 1] = (*str2)[i];
            }
            (*str2)[0] = '0';
            len2++;
        }
    }
}

char* multiply_single_digits(const char* str1, const char* str2) {
    if(strlen(str1) == 1 && strlen(str2) == 1) {
        int product = (str1[0] - '0') * (str2[0] - '0');
        char *result_str = NULL;

        if (product >= 10) {
            result_str = (char *)malloc(3 * sizeof(char));
            result_str[0] = (product / 10) + '0';
            result_str[1] = (product % 10) + '0';
            result_str[2] = '\0';
        } else {
            result_str = (char *)malloc(2 * sizeof(char));
            result_str[0] = product + '0';
            result_str[1] = '\0';
        }
        return result_str;
    }
    return NULL;
}