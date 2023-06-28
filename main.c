#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define TAM 36
#define path "alunos.txt"
#define intervaloMenor 2022000
#define intervaloMaior 2022999

typedef struct {
    int matricula;
    double notas[4];
    char nome[100];
    int codigoTurma;
    int faltas;
} Aluno;

int cadastrarAluno(Aluno aluno, FILE *file); // Função que cadastra o aluno no arquivo "alunos.txt"

int removerAluno(int indice, Aluno *alunos, FILE *file); // Função que remove o aluno do arquivo "alunos.txt"

void atualizarAluno(Aluno aluno, Aluno *alunos, int indice); // Funcao que realiza a atualizacao do aluno

void ordenarVetor(int tipoOrdem, int ordem, Aluno *alunos,
                  int alunosCadastrados); // Funcao para ordernar de acordo com a escolha do usuario

void atualizarArquivo(Aluno *alunos, FILE *file); // Funcao responsavel por atualizar o arquivo a partir do vetor alunos

void
atualizarVetor(FILE *file, Aluno *alunos); // Função responsavel por ler o arquivo e adicionar as informacoes no vetor

void zerarVetor(Aluno *alunos); // Função que zera o vetor "alunos" colocando as matriculas para "-1"

void exibirMenu(); // Funcao que exibe o menu de opcoes

void limpaTela(); // Funcao que limpa o terminal

int verificarExitencia(int matricula,
                       Aluno *alunos); // funcao que verifica se a matricula existe no vetor e retorna o indice

int numeroDeAlunos(Aluno *alunos); // Função que verifica a quantidade de alunos existentes no vetor

void HLine();

int main(void) {
    int i, j, c;
    int alunosCadastrados = 0;
    int cont, codigoTurma;
    int matricula = 0;
    int escolha = 0;
    int escolhaTipo, escolhaOrdem;
    char temp[100];
    double media;
    Aluno aluno;
    Aluno alunos[TAM];
    FILE *file;

    file = fopen(path, "r");
    if (file == NULL) {
        fclose(file);
        file = fopen(path, "w");
        fprintf(file, "");
    }
    fclose(file);


    zerarVetor(alunos);


    while (escolha != 10) {
        zerarVetor(alunos);
        atualizarVetor(file, alunos);
        alunosCadastrados = numeroDeAlunos(alunos);

        sleep(2);

        exibirMenu();
        fflush(stdin);
        fgets(temp, 100, stdin);
        escolha = atoi(temp);

        switch (escolha) {

            case 1:
                if (alunosCadastrados >= TAM) {
                    printf("Numero maximo de alunos atingido\n");
                }


                printf("Digite a matricula do aluno [2022000 - 2022999]: \n");
                
                fgets(temp, 100, stdin);
                aluno.matricula = atoi(temp);

                if (verificarExitencia(aluno.matricula, alunos) != -1) {
                    printf("Matricula ja existente\n");
                    break;
                }
                else if (aluno.matricula < intervaloMenor || aluno.matricula > intervaloMaior)
                {
                    printf("Matricula invalida\n");
                    break;
                }
                


                printf("Digite o nome do aluno: \n");

                
                fgets(temp, 100, stdin);
                //Retirando o /n da leitura do nome
                temp[strlen(temp) - 1] = '\0';
                strcpy(aluno.nome, temp);


                fflush(stdin);
                for (i = 0; i < 4; i++) {
                    printf("Digite a %d nota: \n", i + 1);

                    fgets(temp, 100, stdin);
                    aluno.notas[i] = atof(temp);
                    
                    while (aluno.notas[i] < 0 || aluno.notas[i] > 10) {
                        printf("Nota invalida, por favor digite novamente: \n");
                        fgets(temp, 100, stdin);
                        aluno.notas[i] = atof(temp);
                    }
                }

                printf("Digite o codigo da Turma: \n");
                scanf("%d", &aluno.codigoTurma);
                printf("Digite o numero de faltas: \n");
                scanf("%d", &aluno.faltas);
                while (aluno.faltas < 0 || aluno.faltas > 36) {
                    printf("Numero de faltas invalido, tente novamente: \n");
                    scanf("%d", &aluno.faltas);
                }
                cadastrarAluno(aluno, file);
                printf("Aluno Cadastrado com sucesso\n");


                break;

            case 2:

                printf("Digite a matricula do aluno\n");
                scanf("%d", &matricula);
                if (verificarExitencia(matricula, alunos) != -1) {
                    printf("Removendo aluno...\n");
                    removerAluno(verificarExitencia(matricula, alunos), alunos, file);
                    sleep(2);
                    printf("Aluno removido com sucesso\n");


                } else if (matricula < intervaloMenor || matricula > intervaloMaior)
                {
                    printf("Matricula invalida\n");
                    break;
                }
                else{
                    printf("Aluno nao encontrado\n");
                }
                

                break;

            case 3:
                printf("Digite o numero da matricula: \n");
                fgets(temp, 100, stdin);
                aluno.matricula = atoi(temp);

                int indice = verificarExitencia(aluno.matricula, alunos);
                if (indice == -1) {
                    printf("Aluno Inexistente\n");
                } else {
                    printf("Iniciando atualizacao de aluno\n");
                    sleep(2);


                    printf("Digite o nome do aluno: \n");

                    
                    fgets(temp, 100, stdin);
                    //Retirando o /n da leitura do nome
                    temp[strlen(temp) - 1] = '\0';
                    strcpy(aluno.nome, temp);

                    fflush(stdin);
                    for (i = 0; i < 4; i++) {
                        printf("Digite a %d nota: \n", i + 1);
                        scanf("%lf", &aluno.notas[i]);
                        while (aluno.notas[i] < 0 || aluno.notas[i] > 10) {
                            printf("Nota invalida, por favor digite novamente: \n");
                            scanf("%lf", &aluno.notas[i]);
                        }
                    }

                    printf("Digite o codigo da Turma: \n");
                    scanf("%d", &aluno.codigoTurma);
                    printf("Digite o numero de faltas: \n");
                    scanf("%d", &aluno.faltas);
                    while (aluno.faltas < 0 || aluno.faltas > 36) {
                        printf("Numero de faltas invalido, tente novamente: \n");
                        scanf("%d", &aluno.faltas);
                    }

                    atualizarAluno(aluno, alunos, indice); // Atualiza o vetor de alunos
                    atualizarArquivo(alunos, file); // Atualiza o arquivo alunos
                    printf("Aluno atualizado com sucesso\n");

                }


                break;


            case 4:
                atualizarVetor(file, alunos);
                cont = 0;

                printf("Digite o codigo da turma:  (-1 para todas) \n");
                scanf("%d", &codigoTurma);

                printf("Buscando alunos\n");
                sleep(1);
                printf("...\n");
                sleep(1);

                HLine();

                for (i = 0; i < TAM; i++) {

                    aluno = alunos[i];
                    if (aluno.matricula == -1) {
                    } else {
                        if (aluno.codigoTurma == codigoTurma || codigoTurma == -1) {
                            printf("Matricula: %d\n", aluno.matricula);
                            printf("Nome: %s\n", aluno.nome);
                            printf("Nota 1: %.2lf | Nota 2: %.2lf\n", aluno.notas[0], aluno.notas[1]);
                            printf("Nota 3: %.2lf | Nota 4: %.2lf\n", aluno.notas[2], aluno.notas[3]);
                            printf("Faltas: %d\n", aluno.faltas);
                            printf("Codigo da Turma: %d\n", aluno.codigoTurma);
                            HLine();
                            cont++;
                        }
                    }
                }
                printf("\nTotal de %d alunos encontrados\n", cont);

                break;

            case 5:
                atualizarVetor(file, alunos);
                cont = 0;

                printf("Digite o codigo da turma: \n");
                scanf("%d", &codigoTurma);

                printf("Buscando alunos\n");
                sleep(1);
                printf("...\n");
                sleep(1);
                //Media >= 7 e Frequencia >=21
                HLine();

                for (i = 0; i < TAM; i++) {

                    aluno = alunos[i];

                    media = (aluno.notas[0] + aluno.notas[1] + aluno.notas[2] + aluno.notas[3]) / 4;

                    if (aluno.matricula == -1) {

                    } else {
                        if (aluno.codigoTurma == codigoTurma && media >= 7 && aluno.faltas <= 14) {
                            printf("Matricula: %d\n", aluno.matricula);
                            printf("Nome: %s\n", aluno.nome);
                            printf("Media: %.2lf\n", media);
                            printf("Frequencia %d/36: \n", 36 - aluno.faltas);
                            HLine();
                            cont++;
                        }
                    }
                }
                printf("\nTotal de %d alunos encontrados\n", cont);
                break;

            case 6:

                atualizarVetor(file, alunos);
                cont = 0;

                printf("Digite o codigo da turma:  (-1 para todas) \n");
                scanf("%d", &codigoTurma);

                printf("Buscando alunos\n");
                sleep(1);
                printf("...\n");
                sleep(1);
                //Media < 7
                HLine();

                for (i = 0; i < TAM; i++) {

                    aluno = alunos[i];

                    media = (aluno.notas[0] + aluno.notas[1] + aluno.notas[2] + aluno.notas[3]) / 4;

                    if (aluno.matricula == -1) {

                    } else {
                        if ((aluno.codigoTurma == codigoTurma || codigoTurma == -1) && media < 7) {
                            printf("Matricula: %d\n", aluno.matricula);
                            printf("Nome: %s\n", aluno.nome);
                            printf("Media: %.2lf\n", media);
                            HLine();
                            cont++;
                        }
                    }
                }
                printf("\nTotal de %d alunos encontrados\n", cont);

                break;

            case 7:

                atualizarVetor(file, alunos);
                cont = 0;

                printf("Digite o codigo da turma:  (-1 para todas) \n");
                scanf("%d", &codigoTurma);

                printf("Buscando alunos\n");
                sleep(1);
                printf("...\n");
                sleep(1);
                //Media < 7
                HLine();

                for (i = 0; i < TAM; i++) {

                    aluno = alunos[i];

                    media = (aluno.notas[0] + aluno.notas[1] + aluno.notas[2] + aluno.notas[3]) / 4;

                    if (aluno.matricula == -1) {

                    } else {
                        if ((aluno.codigoTurma == codigoTurma || codigoTurma == -1) && aluno.faltas > 14) {
                            printf("Matricula: %d\n", aluno.matricula);
                            printf("Nome: %s\n", aluno.nome);
                            printf("Frequencia %d/36: \n", 36 - aluno.faltas);
                            HLine();
                            cont++;
                        }
                    }
                }
                printf("\nTotal de %d alunos encontrados\n", cont);


                break;

            case 8:

                escolhaOrdem = escolhaTipo = 0;
                printf("Escolha o tipo de ordenacao: \n"
                       "1 - Por Matricula\n"
                       "2 - Por Nome\n"
                       "3 - Por Media\n"
                       "4 - Por Quantidade de Faltas\n");
                scanf("%d", &escolhaTipo);
                if (escolhaTipo < 1 || escolhaTipo > 4)
                {
                    printf("Opcao Invalida\n");
                    break;
                }
                
                sleep(1);
                printf("Escolha a Ordem: \n"
                       "1 - Crescente\n"
                       "2 - Decrescente\n");
                scanf("%d", &escolhaOrdem);
                if (escolhaOrdem < 1 || escolhaOrdem > 2)
                {
                    printf("Opcao Invalida\n");
                    break;
                }

                
                
                ordenarVetor(escolhaTipo, escolhaOrdem, alunos, alunosCadastrados);
                atualizarArquivo(alunos, file);
                printf("Ordenacao Concluida\n");
                

                break;


            case 9:
                printf("Limpando Tela\n");
                sleep(1);
                limpaTela();
                break;

            case 10:
                printf("Encerrando programa\n");
                printf(".");
                sleep(1);
                printf(".");
                sleep(1);
                printf(".");
                sleep(1);

                break;
            default:
                printf("Opcao Invalida\n");
                break;

        }

    }


    return 0;
}

void exibirMenu() {
    printf("\n     SISTEMA DE GESTAO DE ALUNOS\n"
           "------------------------------------------\n"
           "1 - Cadastrar aluno\n"
           "2 - Remover aluno\n"
           "3 - Atualizar dados de um aluno\n"
           "4 - Listar alunos cadastrados\n"
           "5 - Listar alunos aprovados\n"
           "6 - Listar alunos reprovados por media\n"
           "7 - Listar alunos reprovados por faltas\n"
           "8 - Tipo de Ordenacao\n"
           "9 - Limpar Tela\n"
           "10 - ENCERRAR PROGRAMA\n"
           "------------------------------------------\n");
}

int cadastrarAluno(Aluno aluno, FILE *file) {
    file = fopen(path, "a");
    fprintf(file, "\n%d '%s' %.2lf %.2lf %.2lf %.2lf %d %d", aluno.matricula, aluno.nome, aluno.notas[0], aluno.notas[1],
            aluno.notas[2], aluno.notas[3], aluno.codigoTurma, aluno.faltas);
    fclose(file);
    return 0;
}

int removerAluno(int indice, Aluno *alunos, FILE *file) {
    file = fopen(path, "w");
    int i;
    Aluno aluno;
    for (i = 0; i < TAM; i++) {
        aluno = alunos[i];
        if (i == indice || alunos[i].matricula == -1)
            continue;
        else {
            fprintf(file, "\n%d '%s' %.2lf %.2lf %.2lf %.2lf %d %d", aluno.matricula, aluno.nome, aluno.notas[0],
                    aluno.notas[1],
                    aluno.notas[2], aluno.notas[3], aluno.codigoTurma, aluno.faltas);
        }
    }
    fclose(file);

    return 0;
}

void limpaTela() {
    system("CLS");
}

int verificarExitencia(int matricula, Aluno *alunos) {

    for (int i = 0; i < TAM; i++) {

        if (alunos[i].matricula == matricula) {
            return i;
        }

    }
    return -1;
}

void atualizarVetor(FILE *file, Aluno *alunos) {
    file = fopen(path, "r");
    int i;
    Aluno aluno;
    for (i = 0; i < TAM; i++) {

        fscanf(file, "%d '%[^']' %lf %lf %lf %lf %d %d", &aluno.matricula, aluno.nome, &aluno.notas[0],
               &aluno.notas[1], &aluno.notas[2], &aluno.notas[3], &aluno.codigoTurma, &aluno.faltas);


        alunos[i] = aluno;

        if ((getc(file)) == EOF) {
            break;
        }
    }
    fclose(file);
}


void atualizarAluno(Aluno aluno, Aluno *alunos, int indice) {
    alunos[indice].matricula = aluno.matricula;
    strcpy(alunos[indice].nome, aluno.nome);
    alunos[indice].codigoTurma = aluno.codigoTurma;
    alunos[indice].faltas = aluno.faltas;
    alunos[indice].notas[0] = aluno.notas[0];
    alunos[indice].notas[1] = aluno.notas[1];
    alunos[indice].notas[2] = aluno.notas[2];
    alunos[indice].notas[3] = aluno.notas[3];
}

void atualizarArquivo(Aluno *alunos, FILE *file) {
    file = fopen(path, "w");
    if (file == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    
    Aluno aluno;
    for (int i = 0; i < TAM; i++) {
        aluno = alunos[i];
        if (alunos[i].matricula == -1)
            continue;
        fprintf(file, "\n%d '%s' %.2lf %.2lf %.2lf %.2lf %d %d", aluno.matricula, aluno.nome, aluno.notas[0],
                aluno.notas[1],
                aluno.notas[2], aluno.notas[3], aluno.codigoTurma, aluno.faltas);
    }
    fclose(file);
}

void ordenarVetor(int tipoOrdem, int ordem, Aluno *alunos, int alunosCadastrados) {
    int i, j;
    Aluno aux;
    double media1, media2;



    // Ordenar por matricula Crescente e Decrescente Respectivamente
    if (ordem == 1 && tipoOrdem == 1) {
        for (i = 0; i < alunosCadastrados; i++) {
            for (j = 0; j < alunosCadastrados - i - 1; j++) {
                if (alunos[j].matricula > alunos[j + 1].matricula) {
                    aux = alunos[j];
                    alunos[j] = alunos[j + 1];
                    alunos[j + 1] = aux;
                }
            }
        }
    } else if (ordem == 2 && tipoOrdem == 1) {
        for (i = 0; i < alunosCadastrados; i++) {
            for (j = 0; j < alunosCadastrados - i - 1; j++) {
                if (alunos[j].matricula < alunos[j + 1].matricula) {
                    aux = alunos[j];
                    alunos[j] = alunos[j + 1];
                    alunos[j + 1] = aux;
                }
            }
        }
    }

    // Ordenar por nome Crescente e Decrescente Respectivamente
    if (ordem == 1 && tipoOrdem == 2) {
        for (i = 0; i < alunosCadastrados; i++) {
            for (j = 0; j < alunosCadastrados - i - 1; j++) {
                if (strnicmp(alunos[j].nome, alunos[j + 1].nome, 10) > 0) {
                    aux = alunos[j];
                    alunos[j] = alunos[j + 1];
                    alunos[j + 1] = aux;
                }
            }
        }
    } else if (ordem == 2 && tipoOrdem == 2) {
        for (i = 0; i < alunosCadastrados; i++) {
            for (j = 0; j < alunosCadastrados - i - 1; j++) {
                if (strnicmp(alunos[j].nome, alunos[j + 1].nome, 10) < 0) {
                    aux = alunos[j];
                    alunos[j] = alunos[j + 1];
                    alunos[j + 1] = aux;
                }
            }
        }
    }

    // Ordenar por media Crescente e Decrescente Respectivamente
    if (ordem == 1 && tipoOrdem == 3) {
        for (i = 0; i < alunosCadastrados; i++) {
            for (j = 0; j < alunosCadastrados - i - 1; j++) {
                media1 = (alunos[j].notas[0] + alunos[j].notas[1] + alunos[j].notas[2] + alunos[j].notas[3]) / 4;
                media2 = (alunos[j + 1].notas[0] + alunos[j + 1].notas[1] + alunos[j + 1].notas[2] +
                          alunos[j + 1].notas[3]) / 4;
                if (media1 > media2) {
                    aux = alunos[j];
                    alunos[j] = alunos[j + 1];
                    alunos[j + 1] = aux;
                }
            }
        }
    } else if (ordem == 2 && tipoOrdem == 3) {
        for (i = 0; i < alunosCadastrados; i++) {
            for (j = 0; j < alunosCadastrados - i - 1; j++) {
                media1 = (alunos[j].notas[0] + alunos[j].notas[1] + alunos[j].notas[2] + alunos[j].notas[3]) / 4;
                media2 = (alunos[j + 1].notas[0] + alunos[j + 1].notas[1] + alunos[j + 1].notas[2] +
                          alunos[j + 1].notas[3]) / 4;
                if (media1 < media2) {
                    aux = alunos[j];
                    alunos[j] = alunos[j + 1];
                    alunos[j + 1] = aux;
                }
            }
        }
    }

    // Ordenar por Faltas Crescente e Decrescente Respectivamente
    if (ordem == 1 && tipoOrdem == 4) {
        for (i = 0; i < alunosCadastrados; i++) {
            for (j = 0; j < alunosCadastrados - i - 1; j++) {
                if (alunos[j].faltas > alunos[j + 1].faltas) {
                    aux = alunos[j];
                    alunos[j] = alunos[j + 1];
                    alunos[j + 1] = aux;
                }
            }
        }
    } else if (ordem == 2 && tipoOrdem == 4) {
        for (i = 0; i < alunosCadastrados; i++) {
            for (j = 0; j < alunosCadastrados - i - 1; j++) {
                if (alunos[j].faltas < alunos[j + 1].faltas) {
                    aux = alunos[j];
                    alunos[j] = alunos[j + 1];
                    alunos[j + 1] = aux;
                }
            }
        }
    }


}


void zerarVetor(Aluno *alunos) {
    for (int i = 0; i < TAM; i++) {
        alunos[i].matricula = -1;
    }
}

int numeroDeAlunos(Aluno *alunos) {
    int cont = 0;
    for (int i = 0; i < TAM; i++) {
        if (alunos[i].matricula != -1) {
            cont++;
        }

    }
    return cont;

}

void HLine() {
    printf("------------------------------------------\n");
}
