#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decode.h"


char* readFile() {
    const char* filename = "message.txt";
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(fileSize + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Erro de alocação de memória\n");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0';

    fclose(file);

    return buffer;
}

char* base64(char* encoded_message) {
    const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    const int BASE64_ALPHABET_SIZE = 64;
    int encoded_len = strlen(encoded_message);

    if (encoded_len % 4 != 0) {
        fprintf(stderr, "Erro: A mensagem codificada em Base64 não tem um tamanho válido\n");
        return NULL;
    }

    int decoded_len = (encoded_len * 3) / 4;
    if (encoded_message[encoded_len - 1] == '=') {
        decoded_len--;
        if (encoded_message[encoded_len - 2] == '=') {
            decoded_len--;
        }
    }

    char* decoded_message = (char*)malloc(decoded_len + 1);
    if (decoded_message == NULL) {
        fprintf(stderr, "Erro de alocação de memória\n");
        return NULL;
    }

    int i, j;
    int index = 0;
    unsigned char sextet[4];
    for (i = 0; i < encoded_len; i += 4) {
        for (j = 0; j < 4; j++) {
            if (encoded_message[i + j] == '=') {
                sextet[j] = 0;
            }
            else {
                const char* ptr = strchr(base64_table, encoded_message[i + j]);
                if (ptr == NULL) {
                    fprintf(stderr, "Erro: Caractere inválido na mensagem codificada em Base64\n");
                    free(decoded_message);
                    return NULL;
                }
                sextet[j] = (unsigned char)(ptr - base64_table);
            }
        }

        decoded_message[index++] = (sextet[0] << 2) | (sextet[1] >> 4);
        if (encoded_message[i + 2] != '=') {
            decoded_message[index++] = (sextet[1] << 4) | (sextet[2] >> 2);
            if (encoded_message[i + 3] != '=') {
                decoded_message[index++] = (sextet[2] << 6) | sextet[3];
            }
        }
    }
    decoded_message[index] = '\0';

    return decoded_message;
}

char* reverse(char* decoded_message) {
    int len = strlen(decoded_message);
    char* reversed_message = (char*)malloc(len + 1);
    if (reversed_message == NULL) {
        fprintf(stderr, "Erro de alocação de memória\n");
        return NULL;
    }

    int i, j;
    for (i = len - 1, j = 0; i >= 0; i--, j++) {
        reversed_message[j] = decoded_message[i];
    }
    reversed_message[len] = '\0';

    return reversed_message;
}

int main() {
    char* encoded_message = readFile();
    if (encoded_message == NULL) {
        return 1;
    }

    char* decoded_message = base64(encoded_message);
    if (decoded_message == NULL) {
        return 1;
    }

    char* final_message = reverse(decoded_message);
    if (final_message == NULL) {
        free(decoded_message);
        return 1;
    }

    printf("Mensagem decodificada e revertida: %s\n", final_message);

    free(decoded_message);
    free(final_message);

    return 0;
}
