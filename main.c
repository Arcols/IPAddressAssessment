/******************************************************************************
*  ASR => 4R2.04                                                              *
*******************************************************************************
*                                                                             *
*  N° de Sujet : 2                                                            *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Intitulé : Analyse de l'adresse IP                                         *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Nom-prénom1 : LACOSTE Maxime                                               *
*                                                                             *
*  Nom-prénom2 : COLSON Arthur                                                *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Nom du fichier : main.c                                                    *
*                                                                             *
******************************************************************************/

#include "fonctionIP.h"

#define MAX_INPUT_LENGTH 20

int main() {
    char input[MAX_INPUT_LENGTH];
    char ip_address[MAX_INPUT_LENGTH];
    int cidr_mask_int;
    IP recIP;

    printf("Entrez une adresse IPv4 avec un masque en notation CIDR (par exemple, 192.168.1.1/24): ");
    fgets(input, MAX_INPUT_LENGTH, stdin);

    // Ouverture du fichier en mode écriture
    FILE* output_file = fopen("informationsIP.txt", "w+");
    if (output_file == NULL) {
        printf("Erreur lors de l'ouverture du fichier informationsIP.txt\n");
        return 1;
    }

    fprintf(output_file, "Ouverture du programme\n");

    // Suppression du caractère de nouvelle ligne
    input[strcspn(input, "\n")] = '\0';

    // Extraction de l'adresse IP et du masque CIDR
    char *delimiter_position = strchr(input, '/');
    if (delimiter_position == NULL) {
        fprintf(output_file, "Format invalide.\n");
        fclose(output_file);
        return 1;
    }

    extractIPAddress(input, ip_address);
    char *cidr_str = delimiter_position + 1;

    unsigned short cidr_mask = validateCIDRMask(cidr_str, &cidr_mask_int);
    recIP.mask = cidr_mask;

    if (ip_address[0] == '\0' || cidr_mask == 0) {
        fprintf(output_file, "Erreur lors de la validation de l'adresse IP ou du masque CIDR.\n");
        fclose(output_file);
        return 1;
    }

    if (!isValidIPv4(ip_address)) {
        fprintf(output_file, "Adresse IPv4 invalide.\n");
        fclose(output_file);
        return 1;
    }

    fprintf(output_file, "Adresse IPv4: %s\n", ip_address);
    fprintf(output_file, "Masque CIDR: %hu\n", recIP.mask);

    decomposeIPv4(ip_address, &recIP);
    fprintf(output_file, "Décomposition de l'adresse IPv4 :\n");
    fprintf(output_file, "a = %hu\n", recIP.octets[0]);
    fprintf(output_file, "b = %hu\n", recIP.octets[1]);
    fprintf(output_file, "c = %hu\n", recIP.octets[2]);
    fprintf(output_file, "d = %hu\n", recIP.octets[3]);

    char classIP = analyseClass(&recIP);
    fprintf(output_file, "Cette adresse IP appartient à la classe : %c\n", classIP);
    
    const char* ipType = getIPAddressType(&recIP);
    fprintf(output_file, "Type de l'adresse IP : %s\n", ipType);

    NetworkHostAddresses *result = calculateNetworkAndHost(&recIP);
    if (result != NULL) {
        fprintf(output_file, "Adresse réseau: %u.%u.%u.%u\n",
                (result->network >> 24) & 0xFF,
                (result->network >> 16) & 0xFF,
                (result->network >> 8) & 0xFF,
                result->network & 0xFF);

        fprintf(output_file, "Adresse d'hôte: %u.%u.%u.%u\n",
                (result->host >> 24) & 0xFF,
                (result->host >> 16) & 0xFF,
                (result->host >> 8) & 0xFF,
                result->host & 0xFF);

        free(result);
    } else {
        fprintf(output_file, "Erreur lors du calcul des adresses réseau et hôte.\n");
    }

    fclose(output_file);
    return 0;
}
