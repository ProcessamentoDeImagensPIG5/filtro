/* Struct que descreve o cabecalho do arquivo BMP */
typedef struct header
{
        char magic_number1;
        char magic_number2;
        unsigned int size_bmpfile;
        unsigned int application;
        unsigned int offset;
        unsigned int header;
        unsigned int width;
        unsigned int height;
        unsigned short int number_colorplanes;
        unsigned short int number_bitspixel;
        unsigned int bi_rgb;
        unsigned int size_rawbmpdata;
        unsigned int horizontal_resolution;
        unsigned int vertical_resolution;
        unsigned int number_colorspallete;
        unsigned int allcolorsimportant;
} Header;

/* Struct que descreve um pixel */
typedef struct pixel_rgb
{
      unsigned char B;
      unsigned char G;
      unsigned char R;
} Pixel;

/*
    Funcao le_cabecalho
    Descricao:
        Le os dados do cabecalho do arquivo BMP
*/
void escreve(Header *cabecalho, FILE* arq_saida){
    fwrite(&cabecalho->magic_number1, sizeof(char), 1, arq_saida);
    fwrite(&cabecalho->magic_number2, sizeof(char), 1, arq_saida);
    fwrite(&cabecalho->size_bmpfile, sizeof(unsigned int), 1, arq_saida);
    fwrite(&cabecalho->application, sizeof(unsigned int), 1, arq_saida);
    fwrite(&cabecalho->offset, sizeof(unsigned int), 1, arq_saida);
    fwrite(&cabecalho->header, sizeof(unsigned int), 1, arq_saida);
    fwrite(&cabecalho->width, sizeof(unsigned int), 1, arq_saida);
    fwrite(&cabecalho->height, sizeof(unsigned int), 1, arq_saida);
    fwrite(&cabecalho->number_colorplanes, sizeof(unsigned short int), 1, arq_saida);
    fwrite(&cabecalho->number_bitspixel, sizeof(unsigned short int), 1, arq_saida);
    fwrite(&cabecalho->bi_rgb, sizeof(unsigned int), 1, arq_saida);
    fwrite(&cabecalho->size_rawbmpdata, sizeof(unsigned int), 1, arq_saida);
    fwrite(&cabecalho->horizontal_resolution, sizeof(unsigned int), 1, arq_saida);
    fwrite(&cabecalho->vertical_resolution, sizeof(unsigned int), 1, arq_saida);
    fwrite(&cabecalho->number_colorspallete, sizeof(unsigned int), 1, arq_saida);
    fwrite(&cabecalho->allcolorsimportant, sizeof(unsigned int), 1, arq_saida);

}
void le_cabecalho(Header *cabecalho, FILE* arq_entrada){
    fread(&cabecalho->magic_number1, sizeof(char), 1, arq_entrada);
    fread(&cabecalho->magic_number2, sizeof(char), 1, arq_entrada);
    fread(&cabecalho->size_bmpfile, sizeof(unsigned int), 1, arq_entrada);
    fread(&cabecalho->application, sizeof(unsigned int), 1, arq_entrada);
    fread(&cabecalho->offset, sizeof(unsigned int), 1, arq_entrada);
    fread(&cabecalho->header, sizeof(unsigned int), 1, arq_entrada);
    fread(&cabecalho->width, sizeof(unsigned int), 1, arq_entrada);
    fread(&cabecalho->height, sizeof(unsigned int), 1, arq_entrada);
    fread(&cabecalho->number_colorplanes, sizeof(unsigned short int), 1, arq_entrada);
    fread(&cabecalho->number_bitspixel, sizeof(unsigned short int), 1, arq_entrada);
    fread(&cabecalho->bi_rgb, sizeof(unsigned int), 1, arq_entrada);
    fread(&cabecalho->size_rawbmpdata, sizeof(unsigned int), 1, arq_entrada);
    fread(&cabecalho->horizontal_resolution, sizeof(unsigned int), 1, arq_entrada);
    fread(&cabecalho->vertical_resolution, sizeof(unsigned int), 1, arq_entrada);
    fread(&cabecalho->number_colorspallete, sizeof(unsigned int), 1, arq_entrada);
    fread(&cabecalho->allcolorsimportant, sizeof(unsigned int), 1, arq_entrada);

    printf("Magic number:%c%c\n", cabecalho->magic_number1, cabecalho->magic_number2);
    printf("Size of the BMP file:%u\n", cabecalho->size_bmpfile);
    printf("Application cabecalho:%u\n", cabecalho->application);
    printf("Offset: %u\n", cabecalho->offset);
    printf("Header: %u\n", cabecalho->header);
    printf("Width: %u\n", cabecalho->width);
    printf("Height: %u\n", cabecalho->height);
    printf("Number of color planes: %hu\n", cabecalho->number_colorplanes);
    printf("Number bits/pixel: %d \n", cabecalho->number_bitspixel);
    printf("BI_RGB: %u\n", cabecalho->bi_rgb);
    printf("Size of the raw BMP cabecalho: %u\n", cabecalho->size_rawbmpdata);
    printf("Horizontal resolution of the image: %u\n", cabecalho->horizontal_resolution);
    printf("Vertical resolution of the image: %u\n", cabecalho->vertical_resolution);
    printf("Number of colors in the palette: %u\n", cabecalho->number_colorspallete);
    printf("All colors are important: %u\n", cabecalho->allcolorsimportant);

}

/*  Funcao aloca_linhas
    Descricao:
        Para armazenar a matriz de pixels, são necessários "height" ponteiros para identificar os vetores das linhas.
        Esta funcao aloca, portanto, o espaço de memória necessário para armazenar "height" ponteiros para vetores de estruturas Pixel.
    Entrada:
        height -> Dimensao vertical da matriz, i.e., o numero de linhas na matriz de pixels
    Saida:
        Ponteiro para uma regiao de memoria capaz de armazenar "height" ponteiros para (ponteiros para estruturas Pixel)
*/
struct pixel_rgb** aloca_linhas(int height){
    return malloc(height*sizeof(int*));

}

/*  Funcao calcula_padding
    Descricao:
        Por restricao do formato BMP todas as linhas da matriz de pixels devem necessariamente possuir um tamanho multiplo de 4.
        Por isso, temos que calcular a quantidade de bytes a ser acrescida no final da linha para garantir essa restrição.
        Desta forma, devemos calcular um valor X tal que "X" mais o "tamanho da linha" (sizeof(Pixel)*width) seja multiplo de 4.

    Entrada:
        width -> Dimensao horizontal da matriz, i.e., o numero de colunas na matriz de pixels
    Saida:
        quantidade de bytes extra a serem acrescidos ao final da linha para que ela tenha tamanho múltiplo de 4

*/
int calcula_padding(int width){
    return width%4;
}
/*  Funcao aloca_coluna
    Descricao:
        Para armazenar a matriz de pixels, são necessários "width" ponteiros para identificar os valores de uma coluna.
        Esta funcao aloca, portanto, o espaço de memória necessário para armazenar "width" ponteiros para estruturas Pixel.
    Entrada:
        width -> Dimensao horizontal da matriz, i.e., o numero de colunas na matriz de pixels
    Saida:
        Ponteiro para uma regiao de memoria capaz de armazenar "width" ponteiros para estruturas Pixel
*/

struct pixel_rgb* aloca_coluna(int width){
    return malloc(width*sizeof(int));
}

void le_matriz_pixels(Pixel** mat, Header header, FILE* arq_input)
{
    int i, j, k;
    char lixo;
    for(i=header.height-1; i>-1;i--)
    {
        for(j=0; j<header.width;j++)
        {
            fread(&mat[i][j], sizeof(Pixel), 1, arq_input);
        }

        //pegar o pading
        if(calcula_padding(header.width)!=0)
        {
            for(k=0;k<calcula_padding(header.width);k++)
            {
                fread(&lixo, sizeof (char), 1, arq_input);
            }
        }
    }
}

/*
  Funcao aplica_filtro
    Descricao:
        Tendo a matriz de pixels mat preenchida, devemos converter os pixels para SEPIA

        Isto pode ser feito mudando os componentes de cores da imagem da seguinte forma:

        vermelho_saida = (0.393 * vermelho_original ) + (0.769 * verde_original) + (0.189 * azul_original)
        verde_saida = (vermelho_original * .349) + (verde_original *.686) + (azul_original * .168)
        azul_saida = (vermelho_original * .272) + (verde_original *.534) + (azul_original * .131)

        Uma observação importante é que, caso algum componente queira extrapolar o valor limite 255, tal componente irá ficar com o valor 255.


        Ao final desta função, todos os pixels estarão com a aparência amarelada do SEPIA.
    Entrada:
        mat     -> Matriz bidimensional de estruturas Pixel
        header  -> Estrutura de cabecalho do arquivo BMP
    Saida:
        void
*/

#define r1r .255
#define r2g .00
#define r3b .00

#define g1r .255
#define g2g .255
#define g3b .00

#define b1r .255
#define b2g .00
#define b3b .255

void aplica_filtro(Pixel** mat, Header header){
    int i, j;
    Pixel matriz;

    for(i=header.height-1;i>-1;i--){
        for(j=0;j<header.width;j++){
                matriz.R=mat[i][j].R;
                matriz.G=mat[i][j].G;
                matriz.B=mat[i][j].B;

                mat[i][j].R = (matriz.R * r1r) + (matriz.G *r2g) + (matriz.B * r3b);
                mat[i][j].G = (matriz.R * g1r) + (matriz.G *g2g) + (matriz.B * g3b);
                mat[i][j].B = (matriz.R * b1r) + (matriz.G *b2g) + (matriz.B * b3b);

                if(((r1r * matriz.R ) + (r2g * matriz.G) + (r3b * matriz.B))>255){
                    mat[i][j].R=255;
                }
                if(((matriz.R * g1r) + (matriz.G *g2g) + (matriz.B * g3b))>255){
                    mat[i][j].G=255;
                }
                if(((matriz.R * b1r) + (matriz.G *b2g) + (matriz.B * b3b))>255){
                    mat[i][j].B=255;
                }
        }
    }
}

/*
  Funcao salva_versao_editada
    Descricao:
        De forma analoga a leitura, a gravacao deve ser feita na mesma ordem e da mesma forma.
        Primeiramente os dados do cabecalho e em seguida os dados do mapa de bits.
        Por fim, existem dois zeros que fecham o arquivo.

    Dica para o cabecalho:
        Mantenha o mesmo padrao e sequencia que foi utilizada na leitura

    Dicas para o mapa de bits / matriz de pixels:
        Lembre-se de colocar o pading no final de cada linha
        Lembre-se que a imagem é escrita da ultima linha para a primeira

    Entrada:
        mat     -> Matriz bidimensional de estruturas Pixel
        header  -> Estrutura de cabecalho do arquivo BMP
    Saida:
        void
*/

void salva_versao_editada(Header header, FILE* arq_output, Pixel** mat){
    int i, j, k;
    char lixo;

    escreve(&header, arq_output);

    for(i=header.height-1; i>-1;i--)
    {
        for(j=0; j<header.width;j++)
        {
            fwrite(&mat[i][j], sizeof(Pixel), 1, arq_output);
        }

        if(calcula_padding(header.width)!=0)
        {
            for(k=0;k<calcula_padding(header.width);k++)
            {
                fwrite(&lixo, sizeof (char), 1, arq_output);
            }
        }
    }

}
