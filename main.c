//bibliotecas
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include <process.h>

 
#define UP 72  // 72 80 75 77
#define DOWN 80 //DEFINE A NUMERAÇAO DAS SETAS DO TECLADO
#define LEFT 75
#define RIGHT 77

int comprimento;
int dobrar_no;
int len;
char chave;
int vida;
void SalvarTXT();
void Tempo(long double);
void Andar();  
void Bonus();
int Pontuacao();
void Texto();
void gotoxy(int x, int y);
void GotoXY(int x,int y);
void Movimento();
void Borda();
void ParaBaixo();
void ParaEsquerda();
void ParaCima();
void ParaDireita();
void Sair();
int Pontos();
 
struct coordinate{
    int x;
    int y;
    int direcao;
};
 
typedef struct coordinate coordinate;
 
coordinate cabeca, dobrar[500],bonus,corpo[30];
 
int main()
{
    char chave;
    Texto();
    system("cls");
    comprimento=05;
    cabeca.x=25;
    cabeca.y=20;
    cabeca.direcao=RIGHT;
    Borda(); //situaçao de contato
    Bonus(); //gera as cordenadas primeiramente
    vida=1; //vidas
    dobrar[0]=cabeca;
    Andar();   //inicializa as cordenadas
    return 0;
 
}
void Andar()
{
    int a,i;
     do{
 
        Bonus();
        fflush(stdin); //LIMPA O BUFFER DO TECLADO
 
        len=0;
 
        for(i=0;i<30;i++)
 
        {
 
            corpo[i].x=0;
 
            corpo[i].y=0;
 
            if(i==comprimento)
 
            break;
 
        }
 
        Tempo(comprimento);
 
        Borda();
 
        if(cabeca.direcao==RIGHT)
 
             ParaDireita();
 
        else if(cabeca.direcao==LEFT)
 
            ParaEsquerda();
 
        else if(cabeca.direcao==DOWN)
 
            ParaBaixo();
 
        else if(cabeca.direcao==UP)
 
            ParaCima();
 
        Sair();
 
    }while(!kbhit());
 
    a=getch();
 
    if(a==27)
 
    {
 
        system("cls");
 
        exit(0);
 
    }
    chave=getch();
 
    if((chave==RIGHT&&cabeca.direcao!=LEFT&&cabeca.direcao!=RIGHT)||(chave==LEFT&&cabeca.direcao!=RIGHT&&cabeca.direcao!=LEFT)||(chave==UP&&cabeca.direcao!=DOWN&&cabeca.direcao!=UP)||(chave==DOWN&&cabeca.direcao!=UP&&cabeca.direcao!=DOWN))
 
    {
 
        dobrar_no++;
 
        dobrar[dobrar_no]=cabeca;
 
        cabeca.direcao=chave;
 
        if(chave==UP)
 
            cabeca.y--;
 
        if(chave==DOWN)
 
            cabeca.y++;
 
        if(chave==RIGHT)
 
            cabeca.x++;
 
        if(chave==LEFT)
 
            cabeca.x--;
 
        Andar();
 
    }
 
    else if(chave==27)
 
    {
 
        system("cls");
 
        exit(0);
 
    }
 
    else
 
    {
 
        printf("\a");
 
        Andar();
 
    }
}
 
void gotoxy(int x, int y)
{
 
 COORD coord;
 
 coord.X = x;
 
 coord.Y = y;
 
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
 
}
void GotoXY(int x, int y)
{
    HANDLE a;
    COORD b;
    fflush(stdout);
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a,b);
 }
void ParaBaixo()
{
    int i;
    for(i=0;i<=(cabeca.y-dobrar[dobrar_no].y)&&len<comprimento;i++)
    {
        GotoXY(cabeca.x,cabeca.y-i);
        {
            if(len==0)
                printf("v");
            else
                printf("*");
        }
        corpo[len].x=cabeca.x;cabeca;
        corpo[len].y=cabeca.y-i;
        len++;
    }
    Movimento();
    if(!kbhit())
        cabeca.y++;
}
void Tempo(long double k)//tempo que ele percorre pelo mapa
{
 
    Pontuacao();
    long double i;
    for(i=0;i<=(1000000);i++);
}
void Sair()
{
    int i,check=0;
    for(i=4;i<comprimento;i++)   //começa com 4 porque precisa de um mínimo de 4 elementos para tocar o próprio corpo  
    {                       
        if(corpo[0].x==corpo[i].x&&corpo[0].y==corpo[i].y)
        {
            check++;    //verifica se ta a cabeça da cobra ta na mesma linha que qualquer outra parte do corpo 
        }
        if(i==comprimento||check!=0)
            break;
    }
    if(cabeca.x<=10||cabeca.x>=70||cabeca.y<=10||cabeca.y>=30||check!=0)
    {
        vida--;
        if(vida>=0)
        {
            cabeca.x=25;
            cabeca.y=20;
            dobrar_no=0;
            cabeca.direcao=RIGHT;
            Andar();
        }
        else
        {
            system("cls");
            printf("\nPressione qualquer tecla para sair do jogo\n");
            SalvarTXT();
            exit(0);
        }
    }
}
void Bonus()
{
    if(cabeca.x==bonus.x&&cabeca.y==bonus.y)
    {
        comprimento++;
        time_t a;
        a=time(0);
        srand(a);
        bonus.x=rand()%70;
        if(bonus.x<=10)
            bonus.x+=11;
        bonus.y=rand()%30;
        if(bonus.y<=10)
 
            bonus.y+=11;
    }
    else if(bonus.x==0)/*to create food for the first time coz global variable are initialized with 0*/
    {
        bonus.x=rand()%70;
        if(bonus.x<=10)
            bonus.x+=11;
        bonus.y=rand()%30;
        if(bonus.y<=10)
            bonus.y+=11;
    }
}
void ParaEsquerda()
{
    int i;
    for(i=0;i<=(dobrar[dobrar_no].x-cabeca.x)&&len<comprimento;i++)
    {
        GotoXY((cabeca.x+i),cabeca.y);
       {
                if(len==0)
                    printf("<");
                else
                    printf("*");
        }
        corpo[len].x=cabeca.x+i;
        corpo[len].y=cabeca.y;
        len++;
    }
    Movimento();
    if(!kbhit())
        cabeca.x--;
 
}
void ParaDireita()
{
    int i;
    for(i=0;i<=(cabeca.x-dobrar[dobrar_no].x)&&len<comprimento;i++)
    {
        //GotoXY((head.x-i),head.y);
        corpo[len].x=cabeca.x-i;
        corpo[len].y=cabeca.y;
        GotoXY(corpo[len].x,corpo[len].y);
        {
            if(len==0)
                printf(">");
            else
                printf("*");
        }
        /*corpo[len].x=head.x-i;
        corpo[len].y=head.y;*/
        len++;
    }
    Movimento();
    if(!kbhit())
        cabeca.x++;
}
void Movimento() //dobrar com a cobra
{
    int i,j,diff;
    for(i=dobrar_no;i>=0&&len<comprimento;i--)
    {
            if(dobrar[i].x==dobrar[i-1].x)
            {
                diff=dobrar[i].y-dobrar[i-1].y;
                if(diff<0)
                    for(j=1;j<=(-diff);j++)
                    {
                        corpo[len].x=dobrar[i].x;
                        corpo[len].y=dobrar[i].y+j;
                        GotoXY(corpo[len].x,corpo[len].y);
                        printf("*");
                        len++;
                        if(len==comprimento)
                            break;
                    }
                else if(diff>0)
                    for(j=1;j<=diff;j++)
                    {
                        /*GotoXY(dobrar[i].x,(dobrar[i].y-j));
                        printf("*");*/
                        corpo[len].x=dobrar[i].x;
                        corpo[len].y=dobrar[i].y-j;
                        GotoXY(corpo[len].x,corpo[len].y);
                        printf("*");
                        len++;
                        if(len==comprimento)
                            break;
                    }
            }
        else if(dobrar[i].y==dobrar[i-1].y)
        {
            diff=dobrar[i].x-dobrar[i-1].x;
            if(diff<0)
                for(j=1;j<=(-diff)&&len<comprimento;j++)
                {
                    /*GotoXY((dobrar[i].x+j),dobrar[i].y);
                    printf("*");*/
                    corpo[len].x=dobrar[i].x+j;
                    corpo[len].y=dobrar[i].y;
                    GotoXY(corpo[len].x,corpo[len].y);
                        printf("*");
                   len++;
                   if(len==comprimento)
                           break;
               }
           else if(diff>0)
               for(j=1;j<=diff&&len<comprimento;j++)
               {
                   /*GotoXY((dobrar[i].x-j),dobrar[i].y);
                   printf("*");*/
                   corpo[len].x=dobrar[i].x-j;
                   corpo[len].y=dobrar[i].y;
                   GotoXY(corpo[len].x,corpo[len].y);
                       printf("*");
                   len++;
                   if(len==comprimento)
                       break;
               }
       }
   }
}
void Borda() //ESSE METODO CRIA A BORDA DO MAPA PARA A COLISAO
{
   system("cls");
   int i;
   GotoXY(bonus.x,bonus.y);   /*displaying food*/
       printf("X");//alimento da cobrinha
   for(i=10;i<71;i++)
   {
       GotoXY(i,10);
           printf("-");
       GotoXY(i,30);
           printf("-");
   }
   for(i=10;i<31;i++)
   {
       GotoXY(10,i);
           printf("!");
       GotoXY(70,i);
       printf("!");
   }
}
void Texto()
{
   //GotoXY(10,12);
   printf("\tBem vindo ao jogo 'Caixa de Minhoca'- ENTER\n");
   getch();
   system("cls");
   printf("\tComo jogar:\n");
   printf("\nUse as setas para fazer os movimentos com a cobra em busca da bonus que a faz crescer de tamanho | ENTER. \n");
   if(getch()==27)
   exit(0);
}
void SalvarTXT(){ //ESSE METODO GRAVA EM TXT OS JOGOS KA JOGADOS
   char plname[20],nplname[20],cha,c;
   int i,j,px;
   FILE *info;
   info=fopen("record.txt","a+");
   getch();
   system("cls");
   printf("Digite seu nicname: \n");
   scanf("%[^\n]",plname);
   //************************
   for(j=0;plname[j]!='\0';j++){ //to convert the first letter after space to capital
   nplname[0]=toupper(plname[0]);
   if(plname[j-1]==' '){
   nplname[j]=toupper(plname[j]);
   nplname[j-1]=plname[j-1];}
   else nplname[j]=plname[j];
   }
   nplname[j]='\0';
   //*****************************
   //sdfprintf(info,"\t\t\tPlayers List\n");
   fprintf(info,"Nome usuario: :%s\n",nplname);
    //for date and time
 
   time_t mytime;
  mytime = time(NULL);
  fprintf(info,"Data:%s",ctime(&mytime));
     //**************************
     fprintf(info,"Pontos:%d\n",px=Pontos());//call score to display score
     //fprintf(info,"\nLevel:%d\n",10);//call level to display level
   for(i=0;i<=50;i++)
   fprintf(info,"%c",'_');
   fprintf(info,"\n");
   fclose(info);
   info=fopen("record.txt","r");
   do{
       putchar(c=getc(info));
       }while(c!=EOF);
     fclose(info);
}
int Pontuacao() //mostra o quadro de pontos e vidas
{
   int score;
   GotoXY(20,8);
   score=comprimento-5;
   printf("Pontos : %d",(comprimento-5));
   score=comprimento-5;
   GotoXY(50,8);
   printf("Sua vida : %d",vida);
   return score;
}
int Pontos()
{
int score=Pontuacao();
system("cls");
return score;
}
void ParaCima()
{
   int i;
   for(i=0;i<=(dobrar[dobrar_no].y-cabeca.y)&&len<comprimento;i++)
   {
       GotoXY(cabeca.x,cabeca.y+i);
       {
           if(len==0)
               printf("^");//cabeça da cobra
           else
               printf("=");//corpo da cobra
                 }
       corpo[len].x=cabeca.x;
       corpo[len].y=cabeca.y+i;
       len++;
   }
   Movimento();
   if(!kbhit())
       cabeca.y--;
}