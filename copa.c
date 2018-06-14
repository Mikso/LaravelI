#include "copa.h"

/* cadastra as sele��es de um grupo */

void cad_selecao(){

    FILE * arquivo;
    arquivo = fopen(ARQ_SEL, "ab");
    int j = 0;

    char c;
    tselecao selecao;
    system("cls");

    printf("--------------------------------------------------------\n|\t\tCadastrar grupo e sele��es\t\t|");
        printf("\n--------------------------------------------------------\n");
    if(arquivo == NULL)
        printf("\t\tProblemas na abertura do arquivo!");
    else{
        do{

          /*  Atrav�s dessa op��o � poss�vel cadastrar as sele��es de um grupo
da Copa. O sistema deve solicitar o grupo (um caractere de �A� a �H�), caso as sele��es
deste grupo ainda n�o tenham sido cadastradas, o sistema deve solicitar o nome das 4
sele��es deste grupo. O identificador da sele��o (membro id da estrutura tselecao)
� um n�mero sequencial gerado automaticamente, sendo assim, o identificador da
primeira sele��o cadastrada ser� igual a 1, a da segunda igual a 2, e assim por diante,
at� o id 32. As sele��es (estruturas do tipo tselecao) devem ser gravadas em um
arquivo bin�rio cujo nome � definido pela constante ARQ_SEL.
            */

            //fflush(stdin);
            printf("\nInforme o grupo utilizando as letras de 'A' a 'H' : ");
            scanf(" %c", &selecao.grupo);
            fseek(arquivo, 0, SEEK_END);
            selecao.id = ftell(arquivo)/sizeof(tselecao)+1;
            printf("\nInforme o nome da %d� sele��o deste grupo %c : ",selecao.id, selecao.grupo);
            scanf(" %[^\n]", selecao.nome);
            fwrite(&selecao,sizeof(tselecao),1,arquivo);
            selecao.id = ftell(arquivo)/sizeof(tselecao)+1;
            for(j=0;j<3;j++){
                printf("\nId da selecao : %d\n", selecao.id);
                //fflush(stdin);
                printf("\nInforme o nome da %d� sele��o deste grupo %c : ",selecao.id, selecao.grupo);
                scanf(" %[^\n]", selecao.nome);
                fwrite(&selecao,sizeof(tselecao),1,arquivo);
                selecao.id++;
            }
            printf("\n\n<Cadastro realizado com sucesso!>");
            getch();
            system("cls");
            printf("--------------------------------------------------------\n|\t\tCadastrar grupo e sele��es\t\t|");
            printf("\n--------------------------------------------------------\n");
            printf("\n\n<Deseja continuar cadastrando as sele��es?\n  Digite S para sim ou N para n�o :  >");
            scanf(" %c",&c);
            if(c == 110 || c == 78)
                break;
        }while(selecao.id < 32);

        fclose(arquivo);
    }
    system("cls");

}

/* altera o nome de uma sele��o dado seu id

Alterar sele��o: esta funcionalidade deve ser implementada atrav�s da fun��o
alterar_selecao(). Atrav�s dessa op��o o usu�rio pode alterar o nome de uma das
sele��es cadastradas. Para isso, o sistema deve solicitar o id da sele��o, se este id for
v�lido (houver uma sele��o cadastrada com esse id), mostrar o nome da sele��o e
solicitar o nome correto desta sele��o. Se o id for inv�lido, o sistema deve exibir uma
mensagem de erro.*/
void alterar_selecao(){
    system("cls");
    FILE * arquivo;
    arquivo = fopen(ARQ_SEL, "r+b");
    int cont, n, pos=0;
    cont=1;
    tselecao selecao;

    if(arquivo == NULL)
        printf("\t\tProblemas na abertura do arquivo!");
    else{

        printf("--------------------------------------------------------\n|\t\tAlterar o nome da sele��o\t\t|");
        printf("\n--------------------------------------------------------\n");
        fflush(stdin);
        printf("\nInforme o Id da sele��o que pretende editar\n");
        scanf("%d",&n);
        fread(&selecao, sizeof(tselecao),1,arquivo);
        do{
            // Pega o id digitado e mostra a selecao que o representa
            if(n == selecao.id){
                printf("\nEste id se refere a sele��o %s : ",selecao.nome);
                pos = cont+1;
                break;
            }
            cont++;
        }while(fread(&selecao, sizeof(tselecao), 1, arquivo)==1);

        printf("\nCont = %d\n", cont);
        getch();

// Se nao exibido alguma id - selecao, retornara a msg
        if(pos == 0){
            system("cls");
            printf("Id n�o encontrado\n");
            getch();
            system("cls");
        }
        else{
                // Se encontrado o id correspondente, pedira o novo nome para a selecao
            fflush(stdin);
            printf("\nInforme o novo nome desta sele��o : ");
            scanf("%[^\n]", selecao.nome);
            fseek(arquivo, sizeof(tselecao) * (selecao.id-1), SEEK_SET);
            fwrite(&selecao,sizeof(tselecao),1,arquivo);
            system("cls");
            printf("\n\t<\tAltera��o realizada com sucesso!\t>");
            getch();
            system("cls");
        }

    }
    fclose(arquivo);
}

/* lista no v�deo todas as sele��es cadastradas
Listar sele��es cadastradas: esta funcionalidade deve ser implementada atrav�s da
fun��o list_selecoes(). O sistema dever� exibir no v�deo o id, nome e grupo de
todas as sele��es cadastradas no formato de uma tabela. Caso n�o haja nenhuma
sele��o cadastrada, exibir uma mensagem de erro.*/
void list_selecoes(){

    FILE * arquivo;
    arquivo = fopen(ARQ_SEL, "rb");
    int j = 0;

    tselecao selecao;
    system("cls");
    printf("----------------------------------------------------------------\n|\t\tGrupos e sele��es cadastrados\t\t\t|");
        printf("\n----------------------------------------------------------------\n\n");
    if(arquivo == NULL)
        printf("\t\tProblemas na abertura do arquivo!");
    else{

        fread(&selecao, sizeof(tselecao), 1, arquivo);
    //Ira listar as selecoes de seus respectivos grupos
        do{
            printf("\n\t--------------------------------------------------------\n\t|\t\t\tGrupo %c   \t\t\t|", selecao.grupo);
            printf("\n\t--------------------------------------------------------\n\t|\t\t\t\t|\t\t\t|");
            printf("\n\t|Sele��es\t\t\t|\t  Id\t\t|");
            printf("\n\t|%-31s|\t  %d\t\t|", selecao.nome, selecao.id);
            for(j=0;j<3;j++){
                fread(&selecao, sizeof(tselecao), 1, arquivo);
                printf("\n\t|%-31s|\t  %d\t\t|", selecao.nome, selecao.id);

            }
            printf("\n\t---------------------------------------------------------\n\t\t\t\t\t");
            printf("\n");

        }while(fread(&selecao, sizeof(tselecao), 1, arquivo) == 1);
    }
    fclose(arquivo);
    printf("\n\n<Pressione 'Enter' para voltar ao menu principal!>");
    getch();
    system("cls");
}

/* lista no v�deo as sele��es de um grupo
Listar sele��es de um grupo: esta funcionalidade deve ser implementada atrav�s da
fun��o list_selecoes_grupo(). O sistema deve solicitar o grupo (um caractere de
�A� a �H�), caso as sele��es deste grupo j� tenham sido cadastradas, exibir no v�deo em
formato de tabela o id e nome de todas as sele��es do grupo informado. Caso as
sele��es do grupo n�o tenham sido cadastradas, exibir uma mensagem de erro.
*/
void list_selecoes_grupo(){

    FILE * arquivo;
    arquivo = fopen(ARQ_SEL, "rb");
    int j = 0 ;
    bool aux = false; // armazena se a funcao foi atingida = true
    char grupo;
    tselecao selecao;
    system("cls");
    printf("--------------------------------------------------------\n|\t\tListar sele��es por grupo\t\t|");
        printf("\n--------------------------------------------------------\n");
    if(arquivo == NULL)
        printf("\t\tProblemas na abertura do arquivo!");

    else{
        printf("\nInforme o grupo que deseja listar: ");
        scanf(" %c", &grupo);

        do{
                // Exibe as selecoes de um grupo
            fread(&selecao, sizeof(tselecao), 1, arquivo);
            if(selecao.grupo == grupo){
            printf("\n\t--------------------------------------------------------\n\t|\t\t\tGrupo %c   \t\t\t|", selecao.grupo);
            printf("\n\t--------------------------------------------------------\n\t|\t\t\t\t|\t\t\t|");
            printf("\n\t|Sele��es\t\t\t|\t  Id\t\t|");
            printf("\n\t|%-31s|\t  %d\t\t|", selecao.nome, selecao.id);
            for(j=0;j<3;j++){
                fread(&selecao, sizeof(tselecao), 1, arquivo);
                printf("\n\t|%-31s|\t  %d\t\t|", selecao.nome, selecao.id);
                aux = true;
            }
            printf("\n\t---------------------------------------------------------\n\t\t\t\t\t");
            printf("\n");
                break;
            }

        }while(fread(&selecao, sizeof(tselecao), 1, arquivo)==1);
    }

    if(aux == false){
    printf("\nGrupo n�o encontrado!");//Se exibido algum grupo, n�o dispara a msg
    }

    fclose(arquivo);

    printf("\n\n<Pressione 'Enter' para voltar ao menu principal!>");
    getch();
    system("cls");

}

/* cadastra os jogos da 1� fase da Copa da R�ssia
Cadastrar jogos de um grupo: esta funcionalidade deve ser implementada atrav�s da
fun��o cad_jogos(). O sistema deve solicitar o grupo, data, est�dio e advers�rios de
um dos jogos da 1� fase da Copa. Sugere-se a interface mostrada na figura abaixo para
esta funcionalidade. Ap�s solicitar o grupo, data e est�dio do jogo, o sistema deve exibir
uma lista com o id e nome das sele��es do grupo e solicitar ao usu�rio o id da sele��o mandante,depois
fazer o mesmo para a sele��o visitante. A sele��o visitante n�o pode ser igual � sele��o
mandante. Deve ser poss�vel cadastrar v�rios jogos do mesmo grupo, at� o limite de 6.
Os jogos (estruturas do tipo tjogo) devem ser gravados no arquivo bin�rio cujo nome
� definido pela constante ARQ_JOGO.*/
void cad_jogo(void){
    FILE * arquivo, * arquivo2;
    arquivo = fopen(ARQ_SEL, "rb");
    arquivo2 = fopen(ARQ_JOGO, "ab");
    int i,j;
    i = 0;
    int aux = 0;
    char grupo;
    tselecao selecao;
    tjogo jogo;

    system("cls");
    printf("-----------------------------------------------------------------\n|\t   Cadastros de jogos de um grupo da 1� fase\t\t|");
    printf("\n-----------------------------------------------------------------\n\n");
    if(arquivo == NULL)
        printf("\t\tProblemas na abertura do arquivo!");
    else{
        printf("\nInforme o grupo que deseja listar: ");
        scanf(" %c", &grupo);
        // Aqui chama aquela fun��o que valida se as letras sao A a H

        do{
            fread(&selecao, sizeof(tselecao), 1, arquivo);
             if(selecao.grupo == grupo){
                do{
                        // Ira esperar a entrada da data e o mes, o estadio
                    jogo.grupo = selecao.grupo;
                    printf("\nInforme a data do jogo, no formato dd/mm, separando-os com 'Espa�o': ");
                    scanf(" %d %d", &jogo.data.dia, &jogo.data.mes);
                    printf("\nInforme o estadio do jogo: ");
                    scanf(" %s", jogo.estadio);
                    printf("\n\t--------------------------------------------------------\n\t|\t\t\t\t|\t\t\t|");
                    printf("\n\t|Sele��es\t\t\t|\t  Id\t\t|");
                    printf("\n\t|%-31s|\t  %d\t\t|", selecao.nome, selecao.id);
                    for(j=0;j<3;j++){
                        fread(&selecao, sizeof(tselecao), 1, arquivo);
                        printf("\n\t|%-31s|\t  %d\t\t|", selecao.nome, selecao.id);
                    }
                    // Cadastra a selecao mandante
                    printf("\n\t---------------------------------------------------------\n\t\t\t\t\t");
                    printf("\n");
                    printf("\n\nInforme o id do mandante do jogo: ");
                    scanf(" %d", &jogo.id_mandante);
                    fseek(arquivo, 0, SEEK_SET);
                    fseek(arquivo, sizeof(tselecao) * (jogo.id_mandante-1), SEEK_SET);
                    fread(&selecao,sizeof(tselecao),1,arquivo);
                    printf("\nMandante: %s\n\n", selecao.nome);



                    // Cadastra selecao visitante
                    printf("\n\t--------------------------------------------------------\n\t|\t\t\t\t|\t\t\t|");
                    printf("\n\t|Sele��es\t\t\t|\t  Id\t\t|");
                    printf("\n\t|%-31s|\t  %d\t\t|", selecao.nome, selecao.id);
                    for(j=0;j<3;j++){
                        fread(&selecao, sizeof(tselecao), 1, arquivo);
                        printf("\n\t|%-31s|\t  %d\t\t|", selecao.nome, selecao.id);
                    }
                    printf("\n\t---------------------------------------------------------\n\t\t\t\t\t");
                    printf("\n");
                    printf("\n\nInforme o id do visitante do jogo: ");
                    scanf(" %d", &jogo.id_visitante);
                    fseek(arquivo, 0, SEEK_SET);
                    fseek(arquivo, sizeof(tselecao) * (jogo.id_visitante-1), SEEK_SET);
                    fread(&selecao,sizeof(tselecao),1,arquivo);
                    printf("\nVisitante: %s", selecao.nome);
                    fwrite(&jogo,sizeof(tjogo),1,arquivo2);
                    i++;

                    printf("\n\n\tJogo gravado com sucesso!\n\n");

                    printf("\n\n<Deseja salvar a listagem acima em um arquivo de texto?\n  Digite 1 para sim ou 2 para n�o :  >");
                    scanf(" %d",&aux); // Armazena a opcao de continuar ou sair da funcao de cadastro
                    if(aux != 1){
                        //Continua com novos cadastros
                    }else{
                        aux = 1; // Encerra a funcao de cadastro
                        break;
                    }
                    system("cls");
                    printf("-----------------------------------------------------------------\n|\t   Cadastros de jogos de um grupo da 1� fase\t\t|");
                    printf("\n-----------------------------------------------------------------\n\n");
                }while(aux != 1);

             }
        }while(fread(&selecao, sizeof(tselecao), 1, arquivo) == 1 && aux != 1 );

    fclose(arquivo);
    fclose(arquivo2);
    printf("\n\n<Pressione 'Enter' para voltar ao menu principal!>");
    getch();
    system("cls");
    }
}

/* lista no v�deo/arquivo os jogos de um grupo
Listar jogos de um grupo: esta funcionalidade deve ser implementada atrav�s da
fun��o list_jogos_grupo(). O sistema deve solicitar um grupo e exibir no v�deo a
data, est�dio e advers�rios de todos os jogos do grupo. Depois o sistema deve
perguntar ao usu�rio se ele deseja gerar a mesma listagem em um arquivo, caso
afirmativo, o sistema deve gerar a listagem em um arquivo do tipo texto cujo nome �
definido pela constante ARQ_LIST_JOGOS.*/
void list_jogos_grupo(void){
    FILE * arquivo, * arquivo2;
    arquivo = fopen(ARQ_SEL, "rb");
    arquivo2 = fopen(ARQ_JOGO, "rb");
    int i = 0, n = 0;
    char grupo;
    tselecao selecao;
    tjogo jogo;
    system("cls");
    printf("-----------------------------------------------------------------\n|\t  Lista de jogos cadastros  de um grupo da 1� fase\t|");
    printf("\n-----------------------------------------------------------------\n\n");
    if(arquivo == NULL)
        printf("\t\tProblemas na abertura do arquivo!");
    else{
        do{
            printf("\nInforme o grupo que deseja listar:  ");
            scanf(" %c", &grupo);
            fread(&jogo, sizeof(tjogo), 1, arquivo2);
            n = ftell(arquivo2)/sizeof(tjogo)+1;
            char mandante[31], visitante[31];

            //Lista os jogos de um grupo
             if(jogo.grupo == grupo){
                printf("-----------------------------------------------------------------\n|\t\tJogos do grupo %c da 1� fase\t\t\t|", jogo.grupo);
                printf("\n-----------------------------------------------------------------\n\n");
                do{
                    printf("\t-------------------------------------------------\n\t|\t           Data: %d/ %d/2018\t\        |", jogo.data.dia, jogo.data.mes);
                    printf("\n\t-------------------------------------------------\n\n");

                    printf("\t-------------------------------------------------\n\t|\t\t  Estadio : %-15s\t|", jogo.estadio);
                    printf("\n\t-------------------------------------------------\n\n");


                    fseek(arquivo, sizeof(tselecao) * (jogo.id_mandante-1), SEEK_SET);
                    fread(&selecao,sizeof(tselecao),1,arquivo);
                    strcpy(mandante,selecao.nome);
                    fseek(arquivo, sizeof(tselecao) * (jogo.id_visitante-1), SEEK_SET);
                    fread(&selecao,sizeof(tselecao),1,arquivo);
                    strcpy(visitante,selecao.nome);
                    printf("\-------------------------------------------------------------------------\n|       Mandante => %-15s X %15s <= Visitante \t|", mandante, visitante);
                    printf("\n\-------------------------------------------------------------------------\n\n");

                    fread(&jogo, sizeof(tjogo), 1, arquivo2);
                    i++;
                }while(fread(&jogo, sizeof(tjogo), 1, arquivo2)==1);
            }

            char c;
            printf("\n\n<Deseja salvar a listagem acima em um arquivo de texto?\n  Digite S para sim ou N para n�o :  >");
            scanf(" %c",&c);
            if(c == 115 || c == 83){
                FILE * arquivo3;
                arquivo3 = fopen(ARQ_LIST_JOGOS, "a");
                if(arquivo3 == NULL)
                    printf("\t\tProblemas na abertura do arquivo!");
                else{
                    fseek(arquivo2, 0, SEEK_SET);
                    fseek(arquivo, 0, SEEK_SET);
                    fprintf(arquivo3, "    Jogos do grupo %c\n\n",jogo.grupo);
                    do{

                        fseek(arquivo, sizeof(tselecao) * (jogo.id_mandante-1), SEEK_SET);
                        fread(&selecao,sizeof(tselecao),1,arquivo);
                        strcpy(mandante,selecao.nome);
                        fseek(arquivo, sizeof(tselecao) * (jogo.id_visitante-1), SEEK_SET);
                        fread(&selecao,sizeof(tselecao),1,arquivo);
                        strcpy(visitante,selecao.nome);
                        fprintf(arquivo3,"Data : %d/ %d/ 2018\nEstadio: %s\nMandante: %s\nVisitante: %s\n\n\n",
                                jogo.data.dia,
                                jogo.data.mes, jogo.estadio, mandante, visitante);
                    }while(fread(&jogo, sizeof(tjogo), 1, arquivo2)==1);

                    printf("\nOk, o arquivo de texto foi gerado com sucesso!");
                }
                fclose(arquivo3);
            }
            else{
                printf("\nOk, o arquivo de texto N�o ser� gerado!");
            }
            fclose(arquivo);
            fclose(arquivo2);

            printf("\n\n<Pressione 'Enter' para voltar ao menu principal!>");
            getch();
            system("cls");
        }while(fread(&jogo, sizeof(tjogo), 1, arquivo2)==1);

    }
}
/* lista no v�deo os jogos de uma data
Listar jogos de uma data: esta funcionalidade deve ser implementada atrav�s da
fun��o list_jogos_data(). O sistema deve solicitar uma data e exibir no v�deo o
grupo, est�dio e advers�rios de todos os jogos que ocorrem na data informada pelo
usu�rio.*/
void list_jogos_data(void){
    FILE * arquivo, * arquivo2;
    arquivo = fopen(ARQ_SEL, "rb");
    arquivo2 = fopen(ARQ_JOGO, "rb");
    int i = 0;

    tselecao selecao;
    tjogo jogo;
    system("cls");

    printf("-----------------------------------------------------------------\n|\t  Lista de jogos da 1� fase por data\t\t\t|");
    printf("\n-----------------------------------------------------------------\n\n");

    if(arquivo == NULL)
        printf("\t\tProblemas na abertura do arquivo!");
    else{
        printf("\nInforme uma data, no formato dd 'Espa�o' mm,  para visualizar os jogos deste dia:  ");
        scanf(" %d", &i);

        // Exibe os jogos da data se houver algum
        do{
            fread(&jogo, sizeof(tjogo), 1, arquivo2);
            char mandante[31], visitante[31];
            if(i == jogo.data.dia){
                printf("-----------------------------------------------------------------\n|\t\tJogo do dia %d/ %d/2018 da 1� fase\t\t|",
                       jogo.data.dia, jogo.data.mes);
                    printf("\n-----------------------------------------------------------------\n\n");
                    printf("\t-------------------------------------------------\n\t|\t\t  Estadio : %-15s\t|", jogo.estadio);
                    printf("\n\t-------------------------------------------------\n\n");


                    fseek(arquivo, sizeof(tselecao) * (jogo.id_mandante-1), SEEK_SET);
                    fread(&selecao,sizeof(tselecao),1,arquivo);
                    strcpy(mandante,selecao.nome);
                    fseek(arquivo, sizeof(tselecao) * (jogo.id_visitante-1), SEEK_SET);
                    fread(&selecao,sizeof(tselecao),1,arquivo);
                    strcpy(visitante,selecao.nome);
                    printf("\n-------------------------------------------------------------------------\n|       Mandante => %-15s X %15s <= Visitante \t|", mandante, visitante);
                    printf("\n-------------------------------------------------------------------------\n\n");

                    fread(&jogo, sizeof(tjogo), 1, arquivo2);
            }
        }while(fread(&jogo, sizeof(tjogo), 1, arquivo2)==1);
        fclose(arquivo);
        fclose(arquivo2);
        printf("\n\n<Pressione 'Enter' para voltar ao menu principal!>");
        getch();
        fflush(stdin);
        system("cls");
    }
}
