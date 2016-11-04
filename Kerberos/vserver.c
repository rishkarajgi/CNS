#include "header_files.h"

struct ticket_v
{
    char IDc[100];
    char ADc[100];
    char IDv[100];
    char TS2[100];
    char lt2[100];
};


struct
{
    char IDc[100];
    struct ticket_v t_v;
}
c_to_v;

int main()
{
    int sfd , nsfd;

    char Kv[] = "tgs_v key";
    int Kv_len = strlen(Kv);

    sfd = socket(AF_INET , SOCK_STREAM , 0);

    if(sfd < 0)
    {
        printf("Error in creating socket\n");
        fflush(stdout);   
    }

    struct sockaddr_in addr;
    bzero((char*)&addr , sizeof(addr));

    addr.sin_family = AF_INET ;
    addr.sin_addr.s_addr = INADDR_ANY ;
    addr.sin_port = htons(4000);

    if( bind(sfd , (struct sockaddr *) &addr , sizeof(addr)) < 0 )
    {
        printf("Error in binding\n");
        fflush(stdout);
    }
   
    listen(sfd , 7);
    socklen_t cli_len = sizeof(struct sockaddr_in);
    struct sockaddr_in cli_addr;
    nsfd = accept(sfd , (struct sockaddr *) &cli_addr , &cli_len);

    read(nsfd , &c_to_v , sizeof(c_to_v));

    rc4(c_to_v.t_v.IDc , Kv , Kv_len);
    rc4(c_to_v.t_v.ADc , Kv , Kv_len);
    rc4(c_to_v.t_v.IDv , Kv , Kv_len);
    rc4(c_to_v.t_v.TS2 , Kv , Kv_len);
    rc4(c_to_v.t_v.lt2 , Kv , Kv_len);

    //printf("\nIDc is - %s\nADc is - %s\nIDv is = %s\nTS2 is - %s\nlt2 is - %s\n" , c_to_v.t_v.IDc , c_to_v.t_v.ADc , c_to_v.t_v.IDv , c_to_v.t_v.TS2 , c_to_v.t_v.lt2);

    if(strcmp(c_to_v.t_v.IDc , c_to_v.IDc) == 0)
    {
        printf("\nclient ID inside the ticket is same as that outside\n");
    }

    else
    {
        printf("\nclient ID inside the ticket is NOT same as that outside\n");  
    }

    char* ADc;
    ADc = inet_ntoa(cli_addr.sin_addr);

    if(strcmp(c_to_v.t_v.ADc , ADc) == 0)
    {
        printf("\nclient IP address is verified\n");
    }

    else
    {
        printf("\nclient IP address different in ticket\n");
    }

    struct timeval t;
    gettimeofday(&t , NULL);

    if((int)(t.tv_sec) < atoi(c_to_v.t_v.TS2) + atoi(c_to_v.t_v.lt2))
    {
        printf("the client can still use the v ticket . Its time stamp is not yet expired\n\nThe client is authenticated\n");
        write(nsfd , "You have been authenticated successfully\n" , 100);
    }

    else
    {
        printf("\nthe client can not use the service because its timestamp is expired\n");
        write(nsfd , "Authentication failed" , 100);
    }
    
   

    while(1);
}