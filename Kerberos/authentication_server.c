#include "header_files.h"

struct 
{
    char IDc[100];
    char IDtgs[100];
}
c_to_as;

struct ticket_tgs
{
    char IDc[100];
    char ADc[100];
    char IDtgs[100];
    char TS1[100];
    char lt1[100];
};


int main()
{
    int sfd , nsfd;
    char Kc[] = "c_as key";
    int Kc_len = strlen(Kc);
    char Ktgs[] = "as_tgs key";
    int Ktgs_len = strlen(Ktgs);

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
    addr.sin_port = htons(2000);

    if( bind(sfd , (struct sockaddr *) &addr , sizeof(addr)) < 0 )
    {
        printf("Error in binding\n");
        fflush(stdout);
    }
   
    listen(sfd , 7);
    socklen_t cli_len = sizeof(struct sockaddr_in);
    struct sockaddr_in cli_addr;
    nsfd = accept(sfd , (struct sockaddr *) &cli_addr , &cli_len);

    if(nsfd < 0)
    {
        printf("\nerror in accept\n");
    }

    else
    {
        printf("\naccept successfully\n");
    }

    read(nsfd , &c_to_as , sizeof(c_to_as));
    

    struct ticket_tgs t_tgs;

    strcpy(t_tgs.IDc , c_to_as.IDc);
    rc4(t_tgs.IDc , Ktgs , Ktgs_len);
    rc4(t_tgs.IDc , Kc , Kc_len);

    char* ADc;
    ADc = inet_ntoa(cli_addr.sin_addr);
    strcpy(t_tgs.ADc , ADc);
    rc4(t_tgs.ADc , Ktgs , Ktgs_len);
    rc4(t_tgs.ADc , Kc , Kc_len);

    strcpy(t_tgs.IDtgs , c_to_as.IDtgs);
    rc4(t_tgs.IDtgs , Ktgs , Ktgs_len);
    rc4(t_tgs.IDtgs , Kc , Kc_len);    


    struct timeval t;
    gettimeofday(&t , NULL);

    sprintf(t_tgs.TS1 , "%d" , (int)(t.tv_sec));

    rc4(t_tgs.TS1 , Ktgs , Ktgs_len);
    rc4(t_tgs.TS1 , Kc , Kc_len);

    char lt1[] = "6000";
    strcpy(t_tgs.lt1 , lt1);
    rc4(t_tgs.lt1 , Ktgs , Ktgs_len);
    rc4(t_tgs.lt1 , Kc , Kc_len);   

    write(nsfd , &t_tgs , sizeof(t_tgs)); 
    while(1);

}