#include "./../header/tokenizer.h"
#include "./../header/tree.h"

void freeRowInfo(rowInfo* info){
    if(info == NULL)
        return;
    if(info->value != NULL)
        free(info->value);
    free(info);
}

void freeMatrix(matrixInfo* info){
    if(info == NULL)
        return;
    if(info->value != NULL){
        for(int c = 0; c < info->rows; c++){
            if(info->value[c] != NULL)
                free(info->value[c]);
        }
    }
    free(info);
}

rowInfo *open(const char* namefile){
    FILE *file = fopen(namefile, "r");  // Abra o arquivo em modo leitura
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    // Ir até o final do arquivo para determinar o tamanho
    fseek(file, 0, SEEK_END);
    int file_size = ftell(file);
    rewind(file);  // Volta para o início do arquivo

    // Aloca memória para armazenar o conteúdo do arquivo
    char *buffer = malloc(file_size + 1);  // +1 para o caractere nulo
    if (buffer == NULL) {
        perror("Erro ao alocar memória");
        fclose(file);
        return NULL;
    }

    // Lê o arquivo inteiro para o buffer
    size_t bytes_read = fread(buffer, 1, file_size, file);
    buffer[bytes_read] = '\0';  // Adiciona o caractere nulo no final para uma string

    //printf("Conteúdo do arquivo:\n%s\n", buffer);

    // Limpeza
    fclose(file);  // Fecha o arquivo

    rowInfo *retorno = (rowInfo *) malloc(sizeof(rowInfo));
    retorno->size = file_size + 1;
    retorno->value = buffer;

    return retorno;
}

matrixInfo* tokenizer(rowInfo *input){

    if(input == NULL){
        printf("Failed at tokenizer... \nAborting...\n");
        fflush(stdout);
        abort();
    }

    if(input->value == NULL){
        printf("Failed at tokenizer...\nAborting...\n");
        fflush(stdout);
        abort();
    }

    char* info = input->value;

    const char delimiters[] = "";
    int i = 0, MAX_TOKENS = 10000;
    char* token = strtok(info, delimiters);
    char** tokens = (char**) malloc(MAX_TOKENS * sizeof(char*));

    while(token != NULL && i < MAX_TOKENS){
        int lenght = strlen(token) + 1;
        tokens[i] = (char*) malloc(lenght * sizeof(char));
        if(tokens[i] == NULL){
            printf("Malloc failed at tokenizer...\nAborting\n");
            fflush(stdout);
            abort();
        }
        strcpy(tokens[i], token);
        i++;
        token = strtok(NULL, delimiters);
    }

    matrixInfo *retorno = (matrixInfo *) malloc(sizeof(matrixInfo));

    if(retorno == NULL){
        printf("Failed at malloc in Matrixinfo...\nAborting...");
        fflush(stdout);
        abort();
    }

    retorno->rows = i;
    retorno->value = tokens;

    return retorno;
}

void warningAndAbortion(char* warn){
    if(warn == NULL){
        printf("Wrong warning...");
        fflush(stdout);
        abort();
    }
    printf("%s\n", warn);
    fflush(stdout);
    abort();

}

int checkPrimitiveTreeAndRowInfo(primitiveTree** primitive, rowInfo* info){
    if(primitive == NULL){
        printf("NULL primitive...\n");
        return 1;
    }

    if(info == NULL){
        printf("NULL info...\n");
        return 1;
    }

    return 0;
}

int includeDeclaration(primitiveTree** primitive, rowInfo* info, int start){
    
    if(checkPrimitiveTreeAndRowInfo(primitive, info)){
        return -1;
    }
    
    int leftArrow = 0, rightArrow = 0, c = start, d = 0, LIMIT = 50;
    char* leitura = (char*) malloc((LIMIT + 1)*sizeof(char));
    char* information = info->value;
    for(; c < info->size && d < LIMIT; c++){
        if(leftArrow && rightArrow){
            break;
        }

        if(information[c] != ' '){
            if(information[c] != '<' && !leftArrow){
                warningAndAbortion("Wrong include declaration... aborting...");
            }
            if(information[c] == '<'){
                if(leftArrow){
                    warningAndAbortion("Double < at include... \naborting...\n");
                }
                leftArrow = 1;
            }

            if(information[c] == '>'){
                rightArrow = 1;
            }

            leitura[d] = information[c];
            d++;
        }
    }

    if(d == LIMIT){
        warningAndAbortion("Wrong include declaration");
    }else{
        leitura[d] = '\0';
        insertInPrimitiveType(primitive, "include", leitura);
    }

    free(leitura);

    return c;
}

int verificar_argumentos(const char *args) {

    int MAX = 1000;

    char type[MAX];
    char arg[MAX];
    int i = 0, j = 0;
    int has_arguments = 0;

    // Percorre a string de argumentos
    while (args[i] != '\0') {
        // Ignora espaços em branco
        if (isspace(args[i])) {
            i++;
            continue;
        }

        // Verifica se encontrou um argumento
        if (isalpha(args[i]) || args[i] == '_') {
            // Lê o nome do argumento
            while (isalnum(args[i]) || args[i] == '_') {
                arg[j++] = args[i++];
            }
            arg[j] = '\0';

            // Ignora espaços em branco
            while (isspace(args[i])) {
                i++;
            }

            // Verifica se a próxima parte é um tipo válido
            j = 0;
            while (isalnum(args[i]) || args[i] == '_') {
                type[j++] = args[i++];
            }
            type[j] = '\0';

            // Se o tipo é válido, registra que encontrou um argumento
                has_arguments = 1;
            
        }

        // Ignora espaços em branco
        while (isspace(args[i])) {
            i++;
        }

        // Se encontrou uma vírgula, avança para o próximo argumento
        if (args[i] == ',') {
            i++;
            j = 0; // Reseta o índice do argumento
        } else if (args[i] == ')') {
            break; // Termina quando chega ao fim da lista de argumentos
        } else {
            return 0; // Se não for vírgula nem parênteses, erro
        }
    }

    // Se não há argumentos, verificar se a lista é "void"
    if (!has_arguments && strcmp(args, "void") != 0) {
        return 0; // Erro se não houver argumentos e não for void
    }

    return 1; // Declaração de argumentos está correta
}

int verificar_corpo_funcao(const char *corpo) {
    int brace_count = 0;   // Contador para chaves
    int instrucao_count = 0; // Contador para instruções
    int i = 0;

    // Ignora espaços em branco iniciais
    while (isspace(corpo[i])) {
        i++;
    }

    // Verifica se começa com '{'
    if (corpo[i] != '{') {
        return 0; // Deve começar com '{'
    }
    brace_count++; // Contabiliza a abertura da chave
    i++; // Avança para o próximo caractere

    while (corpo[i] != '\0') {
        // Ignora espaços em branco
        while (isspace(corpo[i])) {
            i++;
        }

        // Verifica se encontrou uma instrução
        if (corpo[i] != '}' && corpo[i] != '\0') {
            // Contador de instruções
            instrucao_count++;

            // Encontra a próxima instrução
            while (corpo[i] != ';' && corpo[i] != '}' && corpo[i] != '\0') {
                if (corpo[i] == '{') {
                    brace_count++; // Contabiliza chaves aninhadas
                } else if (corpo[i] == '}') {
                    brace_count--; // Descontabiliza chaves fechadas
                }
                i++;
            }

            // Se chegou ao final da instrução, deve ser com um ';'
            if (corpo[i] == ';') {
                i++; // Avança para o próximo caractere
            } else {
                return 0; // Erro se não terminar com ';'
            }
        }

        // Verifica se encontrou uma chave de fechamento '}'
        if (corpo[i] == '}') {
            brace_count--; // Descontabiliza a chave
            i++;
            break; // Sai do loop após encontrar uma chave de fechamento
        }
    }

    // Após o loop, verifica se todas as chaves estão balanceadas
    if (brace_count == 0 && instrucao_count > 0) {
        return 1; // Corpo da função está correto
    } else {
        return 0; // Chaves desbalanceadas ou sem instruções válidas
    }
}

int declaration(primitiveTree** primitive, char* primitiveType, rowInfo* info, int start){

    if(checkPrimitiveTreeAndRowInfo(primitive, info)){
        return -1;
    }

    int limit = 1000;
    int isFunction = 0, c = start, d = 0;
    char* leitura = (char*) malloc(3000*sizeof(char));
    char* arguments = (char*) malloc(limit*sizeof(char));
    char* body = (char*) malloc(limit*sizeof(char));
    char* reading = (char*) malloc(100*sizeof(char));
    for(; c < info->size && d < 100; c++, d++){
        if(info->value[c] == '('){
            isFunction = 1;
        }
    }

    if(isFunction){
        char* name = (char*) malloc(limit*sizeof(char));
        if(name == NULL || arguments == NULL || body == NULL || reading == NULL){
            warningAndAbortion("Failure at mallocing while reading function");
        }

        for(c = start, d = 0; c < info->size && d < limit; c++){
            if(leitura[c] == '('){
                reading[d] = '\0';
                strcpy(name, reading);
                break;
            }
            reading[d] = leitura[c];
            d++;
        }
        if(d == limit){
            warningAndAbortion("wrong function declaration");
        }
        strcpy(reading, "");

        for(d = 0; c < info->size && d < limit; c++){
            if(leitura[c] == '{'){
                reading[d] = '\0';
                strcpy(arguments, reading);
                break;
            }
            reading[d] = leitura[c];
            d++;
        }
        if(d == limit){
            warningAndAbortion("wrong function declaration");
        }

        strcpy(reading, "");

        for(d = 0; c < info->size && d < limit; c++){
            if(leitura[c] == '}'){
                reading[d] = '\0';
                strcpy(body, reading);
                break;
            }
            reading[d] = leitura[c];
            d++;
        }

        if(d == limit){
            warningAndAbortion("wrong function declaration");
        }

        if(!verificar_argumentos(arguments)){
            warningAndAbortion("Wrong arguments declaration");
        }

        if(!verificar_corpo_funcao(body)){
            warningAndAbortion("wrong body function declaration");
        }

        insertFunctionInPrimitiveType(primitive, primitiveType, name, arguments, body);

    }else{
        char* percorrer = info->value;
        for(c = start, d = 0; c < info->size && d < limit; c++, d++){
            if(percorrer[c] == ';'){
                break;
            }
            leitura[d] = percorrer[c];
        }

        if(d == limit){
            warningAndAbortion("Wrong variable declaration");
        }

        leitura[d] = '\0';
        char* quebrar = strtok(leitura, ",");
        while(quebrar != NULL){
            insertInPrimitiveType(primitive, primitiveType, quebrar);
            quebrar = strtok(NULL, ",");
        }
    }

    return c;

}

// Função que verifica a formatação de uma função C, incluindo argumentos
int verificar_formatacao_funcao(const char *declaracao) {
    char tipo[50], nome[50];
    const char *ptr = declaracao;
    
    // Extrai o tipo de retorno e o nome da função
    if (sscanf(ptr, "%49s %49s", tipo, nome) != 2) {
        printf("Erro: Declaração inválida.\n");
        return 0;
    }
        
    // Move o ponteiro para depois do nome da função
    ptr = strstr(ptr, nome) + strlen(nome);
    
    // Verifica a presença dos parênteses para os parâmetros
    while (isspace(*ptr)) ptr++;
    if (*ptr != '(') {
        printf("Erro: Parêntese '(' faltando após o nome da função.\n");
        return 0;
    }

    // Verifica os argumentos da função
    ptr++;
    while (isspace(*ptr)) ptr++;
    if (*ptr != ')') {  // Função com argumentos
        do {
            char arg_type[50], arg_name[50];
            
            // Extrai o tipo e o nome do argumento
            if (sscanf(ptr, "%49s %49s", arg_type, arg_name) != 2) {
                printf("Erro: Argumento inválido na declaração.\n");
                return 0;
            }

            // Move o ponteiro para após o argumento atual
            ptr = strstr(ptr, arg_name) + strlen(arg_name);
            while (isspace(*ptr)) ptr++;

            // Se houver uma vírgula, espera-se outro argumento
            if (*ptr == ',') {
                ptr++;
                while (isspace(*ptr)) ptr++;
            } else if (*ptr != ')') {
                printf("Erro: Formato incorreto nos argumentos.\n");
                return 0;
            }
        } while (*ptr != ')');
    }
    ptr++;

    // Verifica a presença do corpo da função
    while (isspace(*ptr)) ptr++;
    if (*ptr != '{') {
        printf("Erro: Chave '{' faltando para o corpo da função.\n");
        return 0;
    }

    // Confirma que a função termina com uma chave de fechamento '}'
    if (strchr(ptr, '}') == NULL) {
        printf("Erro: Chave '}' faltando no final do corpo da função.\n");
        return 0;
    }

    printf("Formato da função está correto.\n");
    return 1;
}

int verificar_declaracao_main(const char *declaracao) {
    // Declaração de padrões regex para os formatos válidos
    const char *pattern_void = "^int\\s+main\\s*\\(\\s*void\\s*\\)\\s*\\{?$";
    const char *pattern_args = "^int\\s+main\\s*\\(\\s*int\\s+argc\\s*,\\s*char\\s*\\*\\s*argv\\[\\s*\\]\\s*\\)\\s*\\{?$";

    regex_t regex_void, regex_args;

    // Compila os padrões regex
    if (regcomp(&regex_void, pattern_void, REG_EXTENDED) != 0 ||
        regcomp(&regex_args, pattern_args, REG_EXTENDED) != 0) {
        fprintf(stderr, "Erro ao compilar regex\n");
        return 0;
    }

    // Executa o match do regex
    int is_valid = (regexec(&regex_void, declaracao, 0, NULL, 0) == 0) ||
                   (regexec(&regex_args, declaracao, 0, NULL, 0) == 0);

    // Libera a memória dos regex compilados
    regfree(&regex_void);
    regfree(&regex_args);

    // Retorna 1 se a declaração é válida, 0 caso contrário
    return is_valid;
}

int verificar_sintaxe_printf(const char *declaracao) {
    // Padrão regex para printf com uma string de formato e argumentos opcionais
    const char *pattern = "^printf\\s*\\(\\s*\"[^\"]*\"(\\s*,\\s*[^\\)]+)?\\s*\\)\\s*;$";

    regex_t regex;
    int reti;

    // Compila o padrão regex
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Erro ao compilar regex\n");
        return 0;
    }

    // Executa o match do regex
    reti = regexec(&regex, declaracao, 0, NULL, 0);
    regfree(&regex);  // Libera a memória do regex

    // Retorna 1 se a declaração é válida, 0 caso contrário
    return !reti;
}

int verificar_sintaxe_scanf(const char *declaracao) {
    // Padrão regex para scanf com string de formato e argumentos opcionais
    const char *pattern = "^scanf\\s*\\(\\s*\"[^\"]*\"(\\s*,\\s*&[^\\)]+)*\\s*\\)\\s*;$";

    regex_t regex;
    int reti;

    // Compila o padrão regex
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Erro ao compilar regex\n");
        return 0;
    }

    // Executa o match do regex
    reti = regexec(&regex, declaracao, 0, NULL, 0);
    regfree(&regex);  // Libera a memória do regex

    // Retorna 1 se a declaração é válida, 0 caso contrário
    return !reti;
}

int verificar_sintaxe_if_else(const char *declaracao) {
    // Padrões regex para `if` e `else` com bloco opcional
    const char *pattern_if = "^if\\s*\\(.*\\)\\s*(\\{[^}]*\\}|[^;]+;)$";
    const char *pattern_else = "^else(\\s*if\\s*\\(.*\\)\\s*(\\{[^}]*\\}|[^;]+;)|\\s*(\\{[^}]*\\}|[^;]+;))$";

    regex_t regex_if, regex_else;

    // Compila os padrões regex
    if (regcomp(&regex_if, pattern_if, REG_EXTENDED) != 0 ||
        regcomp(&regex_else, pattern_else, REG_EXTENDED) != 0) {
        fprintf(stderr, "Erro ao compilar regex\n");
        return 0;
    }

    // Verifica se a string corresponde ao padrão `if`
    int is_if = (regexec(&regex_if, declaracao, 0, NULL, 0) == 0);
    
    // Verifica se a string corresponde ao padrão `else`
    int is_else = (regexec(&regex_else, declaracao, 0, NULL, 0) == 0);

    // Libera a memória dos regex compilados
    regfree(&regex_if);
    regfree(&regex_else);

    // Retorna 1 se a declaração é válida para `if` ou `else`, 0 caso contrário
    return is_if || is_else;
}

int verificar_sintaxe_while(const char *declaracao) {
    // Padrão regex para `while` com uma condição entre parênteses e um bloco opcional
    const char *pattern_while = "^while\\s*\\(.*\\)\\s*(\\{[^}]*\\}|[^;]+;)$";

    regex_t regex_while;
    int reti;

    // Compila o padrão regex
    reti = regcomp(&regex_while, pattern_while, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Erro ao compilar regex\n");
        return 0;
    }

    // Executa o match do regex
    reti = regexec(&regex_while, declaracao, 0, NULL, 0);
    regfree(&regex_while);  // Libera a memória do regex

    // Retorna 1 se a declaração é válida, 0 caso contrário
    return !reti;
}

int verificar_sintaxe_for(const char *declaracao) {
    // Padrão regex para `for` com três expressões separadas por `;` e um bloco opcional
    const char *pattern_for = "^for\\s*\\(.*;.*;.*\\)\\s*(\\{[^}]*\\}|[^;]+;)$";

    regex_t regex_for;
    int reti;

    // Compila o padrão regex
    reti = regcomp(&regex_for, pattern_for, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Erro ao compilar regex\n");
        return 0;
    }

    // Executa o match do regex
    reti = regexec(&regex_for, declaracao, 0, NULL, 0);
    regfree(&regex_for);  // Libera a memória do regex

    // Retorna 1 se a declaração é válida, 0 caso contrário
    return !reti;
}

int verificar_sintaxe_switch(const char *declaracao) {
    // Padrão regex para `switch` com `case` e `default` opcionais
    const char *pattern_switch = "^switch\\s*\\(.*\\)\\s*\\{\\s*(case\\s+[^:]+:\\s*[^}]*break;\\s*)*(default:\\s*[^}]*;)?\\s*\\}$";

    regex_t regex_switch;
    int reti;

    // Compila o padrão regex
    reti = regcomp(&regex_switch, pattern_switch, REG_EXTENDED | REG_NEWLINE);
    if (reti) {
        fprintf(stderr, "Erro ao compilar regex\n");
        return 0;
    }

    // Executa o match do regex
    reti = regexec(&regex_switch, declaracao, 0, NULL, 0);
    regfree(&regex_switch);  // Libera a memória do regex

    // Retorna 1 se a declaração é válida, 0 caso contrário
    return !reti;
}

void preprocess(primitiveTree** primitive, rowInfo* info){

    char* valores[]  = {"int", "long", "double", "float", "int*", "long*", "double*", "char", "char*", "long long", "long long*", "void"};
    int sizeValores = 12;

    if(checkPrimitiveTreeAndRowInfo(primitive, info)){
        return;
    }

    char* leitura = (char*) malloc((1 + info->size) * sizeof(char));
    char* information = info->value;

    int c = 0, d = 0;

    for(; c < info->size; c++){
        leitura[d] = information[c];
        leitura[d] = '\0';

        No** achou = findPrimitiveType(*primitive, leitura);
        if(achou != NULL){
            if(!strcmp(leitura, "include")){
                c = includeDeclaration(primitive, info, c);
                strcpy(leitura, "");
                d = 0;
            }
            for(int k = 0; k < sizeValores; k++){
                if(!strcmp(leitura, valores[c])){
                    declaration(primitive, valores[k], info, c);
                }
            }
            if(!strcmp(leitura, "main")){
                if(!verificar_declaracao_main(leitura)){
                    warningAndAbortion("Wrong main declaration\n");
                }
            }
            if(!strcmp(leitura, "printf")){
                if(!verificar_sintaxe_printf(leitura)){
                    warningAndAbortion("Wrong printf declaration");
                }
            }
            if(!strcmp(leitura, "scanf")){
                if(!verificar_sintaxe_scanf(leitura)){
                    warningAndAbortion("Wrong scanf declaration");
                }
            }

            if(!strcmp(leitura, "if")){
                if(!verificar_sintaxe_if_else(leitura)){
                    warningAndAbortion("Wrong if declaration");
                }
            }

            if(!strcmp(leitura, "while")){
                if(!verificar_sintaxe_while(leitura)){
                    warningAndAbortion("Wrong if declaration");
                }
            }

            if(!strcmp(leitura, "for")){
                if(!verificar_sintaxe_for(leitura)){
                    warningAndAbortion("Wrong if declaration");
                }
            }

            if(!strcmp(leitura, "switch")){
                if(!verificar_sintaxe_switch(leitura)){
                    warningAndAbortion("Wrong if declaration");
                }
            }
        }

    }
    free(leitura);
    printf("OK!");
}

/*
char **tokenizer2(char **processed){
    char **matrix = malloc
}
*/