/* lib to verify AST; */


bool isNonTerm(struct grammar_symbols* gsymbols, int token){
    return (getKeyByValue(gsymbols->nonTerminals, token) != NULL);
}

int adler32_wiki(int *data, size_t len) 
/* 
    where data is the location of the data in physical memory and 
    len is the length of the data in bytes 
*/
{
	const int MOD_ADLER = 65521;
    int a = 1, b = 0;
    size_t index;
    
    // Process each byte of the data in order
    for (index = 0; index < len; ++index)
    {
        a = (a + data[index]) % MOD_ADLER;
        b = (b + a) % MOD_ADLER;
    }
    
    return (b << 16) | a;
}

int isPathInDLL_ret(struct grammar_symbols* gsymbols, struct NodeDLL* head, int src, int dest, int caminhos[], int len_caminhos) {
    struct NodeDLL* origNode = searchNodeByKey(head, src);
    struct NodeDLL* destNode = searchNodeByKey(head, dest);
    if (origNode == NULL || destNode == NULL) return -1;

    int max = 1000;
    int visited[max];
    for(int i=0; i<max; i++){
        visited[i] = 0;
    }

    int nthp = 0;
    visited[nthp] = src;
    nthp++;

    for(int i=0; i<nthp; i++){
        if(visited[i] > 0){

            origNode = searchNodeByKey(head, visited[i]);
            for(int k=0; k<origNode->len_children_datas; k++){
                int filho = origNode->children_datas[k];
                if(filho != -1){
                    
                    if(filho == destNode->data){

                        int caminho = adler32_wiki(visited, nthp);
                        int same_path = 0;
                        printf("Path: [%d]\n", caminho);
                        int ult=0;
                        for(int i=0; i<len_caminhos; i++){
                            if(caminhos[i] == 0){
                                ult = i;
                            }
                            if(caminhos[i] == caminho){
                                same_path = 1; break;
                            }
                        }
                        if(same_path == 0){
                            caminhos[ult] = caminho;
                            return 1;
                        }else if(same_path == 1 && isNonTerm(gsymbols, filho)){
                            return 1;
                        }
                        
                        // return 1;
                    }else{
                        if(isNonTerm(gsymbols, filho)){// << não terminal;
                            /*\/ verificar presença na pilha de visitados; */
                            int rep = 0;
                            for(int v=0; v<nthp; v++){
                                if(visited[v] == filho){
                                    rep = 1; break;
                                }
                            }

                            /*\/ adiciona o valor não-visitado na pilha; */
                            if(rep == 0){
                                visited[nthp] = filho;
                                nthp++;
                            }
                        }
                    }
                }
            }// fim for;
        }
    }

    return -1;
}

/*\/ criar exemplos de verificação de regras; */
void verify(struct grammar_symbols* gsymbols, struct NodeDLL *tree, int *tokensRules, int sizeTokens){

    /** ... */
    int n_path = 0;
    if(sizeTokens > 0){
        int tk1 = tokensRules[0];
        if(!isNonTerm(gsymbols, tk1)){// << terminal;
            struct NodeDLL* nodeNonTerm = searchNodeByChildren(tree, tk1);
            if(nodeNonTerm){
                n_path++;
                tk1 = nodeNonTerm->data;
            }
        }

        int len_caminhos = 1000;
        int caminhos[len_caminhos];
        for(int i=0; i<len_caminhos; i++){
            caminhos[i] = 0;
        }

        for(int i=1; i<sizeTokens; i++){
            int tk2 = tokensRules[i];

            int is_path = isPathInDLL_ret(gsymbols, tree, tk1, tk2, caminhos, len_caminhos);
            if(is_path == 1){
                printf("[%s - %s] = %d;\n", getKeyByValue(gsymbols->symbolNum, tk1), getKeyByValue(gsymbols->symbolNum, tk2), is_path);
                n_path++;
            }else{
                printf("NO [%s - %s] = %d;\n", getKeyByValue(gsymbols->symbolNum, tk1), getKeyByValue(gsymbols->symbolNum, tk2), is_path);
                n_path--;
            }
        }

        // int paiteste = 213;//221;
        // int literal = 78;
        // int is_path = isPathInDLL_ret(gsymbols, tree, paiteste, literal, caminhos, len_caminhos);
        // printf("is_path[%d]\n", is_path);
        // is_path = isPathInDLL_ret(gsymbols, tree, paiteste, literal, caminhos, len_caminhos);
        // printf("is_path[%d]\n", is_path);
    }
    printf("n_path: [%d][%d]\n", n_path, sizeTokens);
    if(n_path == sizeTokens){
        printf("[Padrão reconhecido];\n");
    }
}
