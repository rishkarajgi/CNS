#include "header_files.h"


struct ticket_tgs
{
    char IDc[100];
    char ADc[100];
    char IDtgs[100];
    char TS1[100];
    char lt1[100];
};


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
    char IDv[100];
    struct ticket_tgs t_tgs;
}
c_to_tgs;


int main()
{
    int sfd , nsfd;

    char Ktgs[] = "as_tgs key";
    int Ktgs_len = strlen(Ktgs);
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
    addr.sin_port = htons(3000);

    if( bind(sfd , (struct sockaddr *) &addr , sizeof(addr)) < 0 )
    {
        printf("Error in binding\n");
        fflush(stdout);
    }
   
    listen(sfd , 7);
    socklen_t cli_len = sizeof(struct sockaddr_in);
    struct sockaddr_in cli_addr;
    nsfd = accept(sfd , (struct sockaddr *) &cli_addr , &cli_len);


    read(nsfd , &c_to_tgs , sizeof(c_to_tgs));

    rc4(c_to_tgs.t_tgs.IDc , Ktgs , Ktgs_len);
    rc4(c_to_tgs.t_tgs.ADc , Ktgs , Ktgs_len);
    rc4(c_to_tgs.t_tgs.IDtgs , Ktgs , Ktgs_len);
    rc4(c_to_tgs.t_tgs.TS1 , Ktgs , Ktgs_len);
    rc4(c_to_tgs.t_tgs.lt1 , Ktgs , Ktgs_len);

    //printf("\nIDc = %s\n , ADc = %s\n IDtgs = %s \nTS1 = %s\nlt1 = %s\n" , c_to_tgs.t_tgs.IDc , c_to_tgs.t_tgs.ADc , c_to_tgs.t_tgs.IDtgs , c_to_tgs.t_tgs.TS1 , c_to_tgs.t_tgs.lt1);
    if(strcmp(c_to_tgs.t_tgs.IDc , c_to_tgs.IDc) == 0)
    {
        printf("\nclient ID inside the ticket is same as that outside\n");
    }

    else
    {
        printf("\nclient ID inside the ticket is NOT same as that outside\n");  
    }




    struct ticket_v t_v;
    
    strcpy(t_v.IDc , c_to_tgs.t_tgs.IDc);
    rc4(t_v.IDc , Kv , Kv_len);

    char* ADc;
    ADc = inet_ntoa(cli_addr.sin_addr);

    if(strcmp(c_to_tgs.t_tgs.ADc , ADc) == 0)
    {
        printf("\nclient IP address is verified\n");
    }

    else
    {
        printf("\nclient IP address different in ticket\n");
    }    


    strcpy(t_v.ADc , ADc);
    rc4(t_v.ADc , Kv , Kv_len);

    strcpy(t_v.IDv , c_to_tgs.IDv);
    rc4(t_v.IDv , Kv , Kv_len);

    struct timeval t;
    gettimeofday(&t , NULL);

    if((int)(t.tv_sec) < atoi(c_to_tgs.t_tgs.TS1) + atoi(c_to_tgs.t_tgs.lt1))
    {
        printf("the client can still use the tgs ticket . Its time stamp is not yet expired\n");
    }

    else
    {
        printf("\nthe client can not use the service because its timestamp is expired\n");
    }

    sprintf(t_v.TS2 , "%d" , (int)(t.tv_sec));
    rc4(t_v.TS2 , Kv , Kv_len);

    char lt2[] = "6000";
    strcpy(t_v.lt2 , lt2);

    rc4(t_v.lt2 , Kv , Kv_len);

    write(nsfd , &t_v , sizeof(t_v));
    while(1);
}