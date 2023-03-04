%{
	int chars=0;
	int words=0;
	int lines=0;
%}
%%
[a-zA-Z0-9]+ {
	words++;
	chars+=yyleng;
}

. {
	chars++;
}

\n {
	chars++;
	lines++;
}
%%
int main(int argc, char **argv) {
	yylex();
	printf("%d %d %d\n", lines, words, chars);
	return 0;
}

int yywrap(){
	return 1;
}
