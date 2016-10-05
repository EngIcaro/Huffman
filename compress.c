/*
    A função creare_bits recebe como parâmetro a raiz da árvore e um 
    conatador iniciado em 0. Tem como objetivo mapear os bits de cada
    caracteres e salvar em um array de structs. OBS: auxi é um string
    global 
*/

void crearebits(Node *root, int idx){
    if(root->left != NULL)
    {
        auxi[idx] = '0';
        crearebits(root->left, idx+1);
    }
    if(root->right != NULL)
    {
        auxi[idx] = '1';
        crearebits(root->right, idx+1);
    }
    if(root->left == NULL && root->right == NULL)
    {    
    memcpy(sequenc[root->caracter].bits, auxi, idx);
    }
}


/*
    Essa função recebe como parâmetro a raiz da arvóre. E sua função
    é percorrer a árvore em pré ordem e salvar em uma string global.           
*/

void pre_order(Node *atual)
{

    if(atual != NULL)
    {
        if(atual->caracter == '*' && atual->left == NULL && atual->right == NULL)
        {
            string[size_tree++] = '\\';
            string[size_tree++] = '*';
        }
        else if (atual->caracter == '\\'  && atual->left == NULL && atual->right == NULL)
        {
            string[size_tree++] = '\\';
            string[size_tree++] = '\\';
        }
        else
        {
            string[size_tree++] = atual->caracter;
            pre_order(atual->left);
            pre_order(atual->right);
        }
    }
}



/*
    A função creat_Header recebe como parâmetro a raiz da árvore, e tem como
    obejtivo imprimir no .huff dois caracteres nulo e a árvore em pré ordem

*/

void creat_Header(Node *root)
{
    int i=0;
    pre_order (root);
    fputc('0', output);
    fputc('0', output);
        while(string[i] != '\0')
        {
            fputc(string[i], output);
            ++i;
        }
}

/*
    Realiza a potência de dois. 

*/
int potencia(int i,int j){
    int result=1;
    while(j)
    {
    result*=i;
    j--;
    }
    return result;
}
/* 
    Essa função pega a string de tamanho oito com o mapeamento dos bits e transforma
    a string em um número decimal. retornando o numero em decimal. OBS: a codificação dos
    bits começa no menos significativo para o mais significativo


*/
int nbyte(char *byte){
    int i, k;
    k = 0;
    int contador = 0;
    for(i = 0; i<=7; i++)
    {
        printf("%c",byte[i]);
        if(byte[i] == '1')
        {
            contador += potencia(2, k);
        }
        k++;
    }
   printf("\ncontta%d\n", contador);
    return contador;
}

/*
    A função compress recebe como parâmetro o arquivo de entrada. E tem como 
    objetivo ler os caracteres do arquivo e comprimir de acordo com seu mapeamento.
    imprimindo os novos caracteres no arquivo .huff. No final ele escreve no começo
    do arquivo o primeiro byte que contem o lixo e os 5 bits da árvore e o segundo byte
    com o tamanho da árvore. Retorna o lixo
*/
 int compress(FILE *file)
 {
    file = fopen("bla", "rb");
    int i, k, trash;
    k = trash = 0;
    unsigned char x;
    char apoio[20];
    char byte[8];
    memset(apoio, '*', sizeof apoio);
    memset(byte, '*', sizeof byte);
    char negativo;
    unsigned char positivo;
    while((negativo = (positivo = fgetc(file))) != EOF)
    {
        memcpy(apoio, sequenc[positivo].bits, strlen(sequenc[positivo].bits));
        for(i = 0; apoio[i] != '*'; i++)
        {
            byte[k] = apoio[i];
            k++;
            if(k == 8)
            {

                x = nbyte(byte);
                fputc(x, output);
                k = 0;
                memset(byte, '*', sizeof byte);
            }
        }
        memset(apoio, '*', sizeof apoio);
    }
    if(k>0)
    {
        trash = (8 - k);
        x = nbyte(byte);
        fputc(x, output);
    }
    unsigned char first_byte, second_byte;
    first_byte = second_byte = 0;
    first_byte = trash<<5;
    first_byte |= ((size_tree>>8)&(0xFF));
    second_byte = (size_tree)&(0xFF);
    fseek(output, 0, SEEK_SET);
    fputc(first_byte, output);
    fputc(second_byte, output);
    return trash;
}
