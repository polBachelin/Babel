/*
** EPITECH PROJECT, 2021
** babel
** File description:
** main
*/

#include "class.hpp"

int main(int ac, char **av)
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    packet_t buffer = {0};
    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    buffer.code = 2;
    buffer.data_size = 6;
    buffer.magic = 12324342212;
    buffer.data = (void *)"salut";
    send(sock , &buffer , strlen(hello) , 0 );
    printf("Hello message sent\n");
    return 0;}