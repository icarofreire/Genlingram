/* lib para realizar o parse de coisas espaçadas; */

int veri_string_counter_based(const char *str, int *con_str)
{
	int fim = strlen(str);
	/* \/ por conta do processo de tokenização,
	uma string grande poderá ter partida em N pedaços.
	Ex: 'Color Wheel teste mazee', esta string seria dividida em 4 pedaços;
	*/

	int meio = 0;
	if(
		(str[0] == '"' || str[0] == '\'') ||
		(str[fim-1] == '"' || str[fim-1] == '\'')
	){
		(*con_str)++;
	}else{
		meio = 1;
	}

	int part = 0;
	if(*con_str == 1) part = 1; // << inicio;
	if(meio == 1 && *con_str == 1) part = 2; // << meio;
	if(*con_str == 2) { // << fim;
		part = 3;
		(*con_str) = 0;
	}

	return part;
}

bool veri_comment_ini_line(const char *str)
{
	int len = strlen(str);
	return (
		((len >= 2) && (str[0] == '/' && str[1] == '/')) ||
		((len >= 1) && (str[0] == '#'))
	);
}

int veri_comment_counter_based(const char *str, int *con)
{
	int fim = strlen(str);

	int meio = 0;
	if(
		((fim >= 2) && (str[0] == '/' && str[1] == '*')) ||
		((fim >= 2) && (str[fim-2] == '*' || str[fim-1] == '/'))
	){
		(*con)++;
	}else{
		meio = 1;
	}

	int part = 0;
	if(*con == 1) part = 1; // << inicio;
	if(meio == 1 && *con == 1) part = 2; // << meio;
	if(*con == 2) { // << fim;
		part = 3;
		(*con) = 0;
	}

	return part;
}