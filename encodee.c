#include <stdio.h>

int power(int power) {
    return 1 << power;
}

int check_even_odd(int *n) {
    return (n[0] == n[1]) ? 1 : 0;
}

int findpartybit(int *n) {
    if (check_even_odd(n)) {
        return n[0];
    }
    if (n[0] == n[1]) {
        return n[2];
    }
    if (n[0] == n[2]) {
        return n[1];
    }
    return 0;
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

void makenible(int number, int *msb, int *lsb) {
    int binarynumbers[8];
    decimalTobinary(number, binarynumbers);
    for (int i = 0; i < 4; i++) {
        msb[i] = binarynumbers[i];
    }
    for (int i = 4; i < 8; i++) {
        lsb[i - 4] = binarynumbers[i];
    }
}

int addparityTonible(int *nible) {
    int d0 = nible[3];
    int d1 = nible[2];
    int d2 = nible[1];
    int d3 = nible[0];

    int party0[3] = {d0, d1, d2};
    int party1[3] = {d0, d1, d3};
    int party2[3] = {d1, d2, d3};

    int p0 = findpartybit(party0);
    int p1 = findpartybit(party1);
    int p2 = findpartybit(party2);

    int finalbyte[8] = {0, d3, d2, d1, d0, p2, p1, p0};
    return binaryTodecimal(finalbyte);
}

void encode(int decimalnumber, char *encoded) {
    int msb[4], lsb[4];
    makenible(decimalnumber, msb, lsb);

    int partytomsb = addparityTonible(msb);
    int partytolsb = addparityTonible(lsb);

    encoded[0] = (char)partytomsb;
    encoded[1] = (char)partytolsb;
    encoded[2] = '\0';  // Corrected index for null terminator
    printf("Encoded %d -> [%d, %d]\n", decimalnumber, partytomsb, partytolsb);
}

void finalencoded(char *inputfileName, char *encodedfileName) {
    FILE *inputfile = fopen(inputfileName, "r");
    if (inputfile == NULL) {
        perror("unable to open input file");
        return;
    }

    FILE *encodedfile = fopen(encodedfileName, "wb");
    if (encodedfile == NULL) {
        perror("unable to open encoded file");
        fclose(inputfile);
        return;
    }

    while (1) {
        int value = fgetc(inputfile);
        if (value == EOF) {
            break;
        }
        char encoded[3];  // Corrected size for encoded array
        encode(value, encoded);
        fwrite(encoded, sizeof(char), 2, encodedfile);  // Corrected to write 2 chars
    }

    fclose(inputfile);
    fclose(encodedfile);
}

int main() {
    char *inputfileName = "inputfile";
    char *encodedfileName = "encodedfile";
    
    finalencoded(inputfileName, encodedfileName);
    return 0;
}