#include <stdio.h>
#include <stdlib.h>

int power(int power) {
    return 1 << power;
}

void decimalTobinary(int num, int *arrayint) {
    for (int i = 7; i >= 0; i--) {
        arrayint[i] = (num & (1 << (7 - i))) ? 1 : 0;
    }
}

int binaryTodecimal(int *arrayint) {
    int num = 0;
    for (int i = 0; i < 8; i++) {
        num += arrayint[7 - i] * power(i);
    }
    return num;
}

void decode(int msb, int lsb, char *decoded) {
    int msb_bin[8], lsb_bin[8];
    decimalTobinary(msb, msb_bin);
    decimalTobinary(lsb, lsb_bin);

    int msb_nible[4] = {msb_bin[1], msb_bin[2], msb_bin[3], msb_bin[4]};
    int lsb_nible[4] = {lsb_bin[1], lsb_bin[2], lsb_bin[3], lsb_bin[4]};

    int combined_bin[8] = {msb_nible[0], msb_nible[1], msb_nible[2], msb_nible[3], lsb_nible[0], lsb_nible[1], lsb_nible[2], lsb_nible[3]};
    int combined_decimal = binaryTodecimal(combined_bin);

    decoded[0] = (char)combined_decimal;
    decoded[1] = '\0';
}

void finaldecoded(char *encodedfileName, char *decodedfileName) {
    FILE *encodedfile = fopen(encodedfileName, "rb");
    if (encodedfile == NULL) {
        perror("unable to open encoded file");
        return;
    }

    FILE *decodedfile = fopen(decodedfileName, "w");
    if (decodedfile == NULL) {
        perror("unable to open decoded file");
        fclose(encodedfile);
        return;
    }

    while (1) {
        char encoded[2];
        size_t read = fread(encoded, sizeof(char), 2, encodedfile);
        if (read < 2) {
            break;
        }
        char decoded[2];
        decode((unsigned char)encoded[0], (unsigned char)encoded[1], decoded);
        fputc(decoded[0], decodedfile);
    }

    fclose(encodedfile);
    fclose(decodedfile);
}

int main() {
    char *encodedfileName = "encodedfile";
    char *decodedfileName = "decodedfile";
    finaldecoded(encodedfileName, decodedfileName);
    return 0;
}
