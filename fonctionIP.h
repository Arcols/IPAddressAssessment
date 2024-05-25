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
*  Nom du fichier : fonctionIP.h                                              *
*                                                                             *
******************************************************************************/

#ifndef FONCTIONIP_H
#define FONCTIONIP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h> // Pour isdigit
#include <stdint.h>

typedef struct {
    unsigned short octets[4];
    unsigned short mask;
} IP;

typedef struct {
    uint32_t network;
    uint32_t host;
} NetworkHostAddresses;


bool isValidIPv4(const char *ip);

void extractIPAddress(char *input, char *ip_address);

unsigned short validateCIDRMask(char *cidr_str, int *cidr_mask_int);

void decomposeIPv4(const char *ip, IP *result);

char analyseClass(IP *result);

int isPrivateIP(IP *ip);

NetworkHostAddresses* calculateNetworkAndHost(IP *ip);

const char* getIPAddressType(IP *ip);

#endif // FONCTIONIP_H
