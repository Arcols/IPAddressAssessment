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
*  Nom du fichier : fonctionIP.c                                              *
*                                                                             *
******************************************************************************/

#include "fonctionIP.h"

// Fonction pour vérifier si une chaîne est une adresse IPv4 valide
bool isValidIPv4(const char *ip) {
    int num, dots = 0;
    int octet;
    const char *ptr = ip;

    if (!*ptr) return false;

    while (*ptr) {
        if (*ptr == '.') {
            if (dots == 3) return false;
            dots++;
            ptr++;
            continue;
        }
        if (!isdigit(*ptr)) return false;
        octet = 0;
        while (*ptr && *ptr != '.') {
            octet = octet * 10 + (*ptr - '0');
            ptr++;
        }
        if (octet < 0 || octet > 255) return false;
    }
    return (dots == 3);
}

// Fonction pour détecter le délimiteur '/' et extraire l'adresse IP
void extractIPAddress(char *input, char *ip_address) {
    char *delimiter_position = strchr(input, '/');
    if (delimiter_position != NULL) {
        *delimiter_position = '\0';
        strcpy(ip_address, input);
    }
}

// Fonction pour valider et convertir le masque CIDR
unsigned short validateCIDRMask(char *cidr_str, int *cidr_mask_int) {
    *cidr_mask_int = atoi(cidr_str);
    if (*cidr_mask_int < 0 || *cidr_mask_int > 32) {
        return 0;
    }
    return (unsigned short)(*cidr_mask_int);
}

void decomposeIPv4(const char *ip, IP *result) {
    sscanf(ip, "%hu.%hu.%hu.%hu", &result->octets[0], &result->octets[1], &result->octets[2], &result->octets[3]);
}

char analyseClass(IP *result){
    unsigned short a = result->octets[0];
    if (a >= 1 && a <= 127) {
        return 'A';
    } else if (a >= 128 && a <= 191) {
        return 'B';
    } else if (a >= 192 && a <= 223) {
        return 'C';
    } else if (a >= 224 && a <= 239) {
        return 'D';
    } else if (a >= 240 && a <= 255) {
        return 'E';
    }
    return '\0';
}

int isPrivateIP(IP *ip) {
    unsigned short a = ip->octets[0];
    unsigned short b = ip->octets[1];

    if (a == 10 || (a == 172 && b >= 16 && b <= 31) || (a == 192 && b == 168)) {
        return 1;  // Adresse IP privée
    }
    return 0;  // Adresse IP publique
}

// Fonction pour calculer l'adresse réseau et l'adresse hôte
NetworkHostAddresses* calculateNetworkAndHost(IP *ip) {
    uint32_t ip_addr = (ip->octets[0] << 24) | (ip->octets[1] << 16) | (ip->octets[2] << 8) | ip->octets[3];
    uint32_t mask = (0xFFFFFFFF << (32 - ip->mask)) & 0xFFFFFFFF;
    uint32_t network_addr = ip_addr & mask;
    uint32_t host_addr = ip_addr & ~mask;

    // On alloue la mémoire au résultat
    NetworkHostAddresses *result = malloc(sizeof(NetworkHostAddresses));
    result->network = network_addr;
    result->host = host_addr;

    return result;

}

const char* getIPAddressType(IP *ip) {
    unsigned short a = ip->octets[0];
    unsigned short b = ip->octets[1];
    unsigned short c = ip->octets[2];
    unsigned short d = ip->octets[3];

    if (a == 127) {
        return "Localhost";
    }

    if (a == 10 || (a == 172 && b >= 16 && b <= 31) || (a == 192 && b == 168)) {
        return "Privée";
    }

    if (a == 255 && b == 255 && c == 255 && d == 255) {
        return "Broadcast";
    }

    if (a >= 224 && a <= 239) {
        return "Multicast";
    }

    return "Publique";


}
