#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processamento.h"

int main (int argc, char *argv[])
{
    int i,j,k,padding;
    char nome_arquivo[50], x = 0;
    FILE *arq_input;
    FILE *arq_output;
    Pixel **mat;
    Header header;
    char command[50];

    strcpy(command, "imagem.bmp" );
  
  	arq_input = fopen (command, "rb");
    if (arq_input == NULL)
    {
         printf("O arquivo nao pode ser aberto.\n");
         exit(2);
    }

    le_cabecalho(&header, arq_input);

    printf("Cabecalho lido\n");
    mat = aloca_linhas(header.height);

    for(i=0; i<header.height; i++) {
       mat[i] = aloca_coluna(header.width);
    }
    printf("Matriz alocada\n");
    padding = calcula_padding(header.width);
    le_matriz_pixels(mat, header, arq_input);
    fclose(arq_input);
    arq_output = fopen("saida.bmp", "w+b");
    if (arq_output == NULL) {
        printf ("O arquivo nao pode ser aberto.\n");
        exit (1);
    }

    aplica_filtro(mat, header);
    printf("Filtro aplicado com sucesso!\n");
    salva_versao_editada(header, arq_output, mat);

    
    fclose(arq_output);

    strcpy(command, "shotwell saida.bmp" );
    system(command);
   
    free(mat);
    printf("Saindo...\n");

    return 0;

}
