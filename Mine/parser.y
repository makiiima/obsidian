%{
    #inlcude<iostream>
    #include<string>
    extern int yylex(void);
    int yyerror(const char *s){fprintf(stderr, "%s\n", s);}return 0;}
    using namespace std;    
%}

%output "Parser.cpp"