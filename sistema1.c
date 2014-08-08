#include<stdlib.h>
#include<string.h>
#include<stdio.h>

void userRegister();
void userModify();
//void userDelete();

typedef struct
{
    int code;
    int allocationStatus;
    int grade;
    char name[50];
    int activityStatus;
}user;

typedef struct
{
    int id;
    int iDay, iMonth, iYear, iHour;
    int fDay, fMonth, fYear, fHour;
    char responsible[20];
    int status;
}resource;

void userFunction()
{
    int choose = 0;
    printf("----------- Menu do Usuário -----------\n");
    printf("[1]Cadastro\n");
    printf("[2]Alterar\n");
    //printf("[3]Excluir\n");
    printf("[3]Voltar\n");
    scanf("%i", &choose);
    fflush(stdin);
    
    switch(choose)
    {
        case 1:
            userRegister(); break;
        case 2:
            userModify(); break;
        /*case 3:
            userDelete(); break;*/
        case 3:
            break;
        default:
            printf("Opção inválida:\n");
    }
}

/** Função de registro de usuário **/
void userRegister() 
{
    user *userVector;
    int n; //Quantidade de usuários
    FILE *usersFile;
    
    usersFile = fopen("User_Register.txt","r+b");
    
    if(usersFile == NULL) //Caso o arquivo não exista
    {
        usersFile = fopen("User_Register.txt","w+b");
        n = 0;
    }
    else //Caso exista, lê o vetor de usuários
    {
        fread(&n, sizeof(int), 1, usersFile);
        userVector = (user *) malloc(sizeof(user)*n);
        fread(userVector, sizeof(user), n, usersFile);
    }
    
    if(n==0) //Abre espaço na memória caso não exista usuário
    {
        userVector = (user *)malloc(sizeof(user));
    }
    else //Realoca espaço na memória para novo usuário
    {
        userVector = (user *)realloc(userVector, sizeof(user)*(n+1));
    }
    
    /** Menu na Tela **/
    printf("------ Menu Registro de Usuário ------\n");
    printf("\nUsuário %d", n);
    printf("\nNome: "); scanf("%s", userVector[n].name);
    fflush(stdin);
    printf("Selecione o Grau: \n");
    printf("[1]Aluno\n");
    printf("[2]Mestre\n");
    printf("[3]Doutor\n");
    printf("[4]Professor\n");
    printf("[5]Pesquisador\n");
    scanf("%i", &userVector[n].grade);
    fflush(stdin);
    userVector[n].code = n;
    printf("\nRegistro concluido!\n");
    
    n++;
    
    fclose(usersFile);
    
    usersFile = fopen("User_Register.txt", "r+b");
    
    fwrite(&n, sizeof(int), 1, usersFile);
    fwrite(userVector, sizeof(user), n, usersFile);
    
    fclose(usersFile);
    
    free(userVector);
}

void userModify()
{
    char name[50];
    int i;
    
    /** Menu da Tela **/
    printf("------ Menu Alteração de Usuário ------\n");
    
    user *userVector;
    FILE *usersFile;
    int n;
    
    usersFile = fopen("User_Register.txt", "r+b");
    
    if(usersFile == NULL)
    {
        usersFile = fopen("User_Register.txt", "w+b");
        n = 0;
    }
    else 
    {
        fread(&n, sizeof(int), 1, usersFile);
        userVector = (user *) malloc(sizeof(user)*n);
        fread(userVector, sizeof(user), n, usersFile);
        printf("Escreva o nome do usuário a ser alterado:\n");
        scanf("%s", name);
        
        for(i=0; i<n; ++i)
        {
            if(strcmp(name, userVector[i].name) == 0)
            {
                printf("\nUser %d", userVector[i].code);
                printf("\nNome: "); scanf("%s", userVector[i].name);
                fflush(stdin);
                printf("Selecione o Grau: \n");
                printf("[1]Aluno\n");
                printf("[2]Mestre\n");
                printf("[3]Doutor\n");
                printf("[4]Professor\n");
                printf("[5]Pesquisador\n");
                scanf("%i", &userVector[n].grade);
                fflush(stdin);
                printf("\nAlteração concluida!\n");
            }
        }
        fclose(usersFile);
        
        usersFile = fopen("User_Register.txt", "r+b");
        
        fwrite(&n, sizeof(int), 1, usersFile);
        fwrite(userVector, sizeof(user), n, usersFile);
        
        /** Problema para liberar a memória (free(userVector) **/
        fclose(usersFile);
    }
}

/*void userDelete()
{
    int n;
    int i;
    char name[50];
    int buffer;
    user *userVector;
    FILE *usersFile;
    
    usersFile = fopen("User_Register.txt", "r+b");
    
    if(usersFile == NULL)
    {
        usersFile = fopen("User_Register.txt", "w+b");
        n=0;
    }
    
    else 
    {
        fread(&n, sizeof(int), 1, usersFile);
        userVector = (user *) malloc(sizeof(user)*n);
        fread(userVector, sizeof(user), n, usersFile);
        
        printf("------ Menu Deletar Usuário ------\n");
        printf("Escreva o nome do usuário a ser alterado:\n");
        scanf("%s", name);
        fflush(stdin);
        
        for(i=0; i<n; ++i) 
        {
            if(strcmp(name, userVector[i].name) == 0)
            {
                printf("\nDeseja mesmo excluir o cliente %s? 1/0: \n", userVector[i].name);
                scanf("%d", &buffer);
                fflush(stdin);
                
                if(buffer == 1)
                {
                    userVector[i].name = 0;
                    printf("Usuário Excluido.\n");
                }
            }
            printf("saiu");
        }
    }
}*/

/** Função Principal **/
int main () 
{
    int choose = 0;
    while (choose !='4')
    {
        /** Menu da Tela **/
        printf("------ Selecione a opção pelo índice ------\n"); 
        printf("[1]Usuário\n");
        printf("[2]Recurso\n");
        printf("[3]Relatório\n");
        printf("[4]Sair\n");
        scanf("%i", &choose);
        fflush(stdin);
        
        switch(choose) 
        {
            case 1:
                userFunction(); break;
            case 2:
               /* resourceFunction(); break;
            case 3:
                report(); break;*/
            case 4:
                return;
            default: 
                printf("Opção inválida:\n");
        }
    }
    return 0;    
}
