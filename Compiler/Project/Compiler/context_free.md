# context-free grammar for C--


## high level
<<<<<<< HEAD

program --> Define_list
>Define_list(global value,struct definition,function declaration, funtion main part)

Define_List --> (Define_List;Define_Block) | Define_Block
=======

program --> Define_lists
>Define_lists(global value,struct definition,function declaration, funtion main part)

Define_Lists --> (Define_Lists;Define_Block) | Define_Block

Define_Block -->  Var_Dec |  Struct_Dec | Fun_Dec | Fun_Imp

Struct_Dec
### Function

Fun_Dec  --> Specifier ID  LP Arg_List RP Semi

Fun_Imp -->  Specifier ID  LP Arg_List RP Block

Block --> LBrace Stat_List RBrace

Arg_List --> ( Arg_List ,specifier ID) | (specifier ID)

### Assign

Var_Dec --> Specifier ExtDecList Semi

ExtDecList --> (ExtDecList , ExtDec) | ExtDec

ExtDec --> ExtDec Assign Exp | ID

## statements

Stats_List --> (Stats_List  Stat) | Stat

Stat -->  Exp Semi
        |   Return Exp Semi
        |   IF LP Exp RP  Block
        |   IF LP Exp RP  Block Else Block --> Block
        |   For LP Exp SEMI Exp SEMI Exp RP Block
        |   While LP Exp RP Block
        |   Do Semi Block While LP Exp RP Semi
        |   Switch LP Exp RP COL LBrace Case_List RBrace

Case_List --> Case Exp COL Stat_List Case_List
        |   Default COL Stat_List

        #add
>>>>>>> 3d3b9da6b9f6a37111f43e013484fd87af8ecf8e

Define_Block -->  Var_Dec |  Struct_Dec | Fun_Dec | Fun_Imp

Struct_Dec --> STRUCT IDENTIFIER LBRACE Define_Lists RBRACE
             | STRUCT IDENTIFIER
### Function

Fun_Dec  --> Specifier IDENTIFIER  LP Arg_List RP SEMI

Fun_Imp -->  Specifier IDENTIFIER  LP Arg_List RP Block

Block --> LBrace Stat_List RBrace

Arg_List --> ( Arg_List COM specifier IDENTIFIER) | (specifier IDENTIFIER)

### Assign

Var_Dec --> Specifier ExtDecList SEMI

ExtDecList --> (ExtDecList COM ExtDec) | ExtDec

ExtDec --> ExtDec Assign Exp | IDENTIFIER

## statements

Stats_List --> (Stats_List  Stat) | Stat

Stat -->  Exp SEMI
        |   Return Exp SEMI
        |   IF LP Exp RP  Block
        |   IF LP Exp RP  Block Else Block --> Block
        |   For LP Exp SEMI Exp SEMI Exp RP Block
        |   While LP Exp RP Block
        |   Do SEMI Block While LP Exp RP SEMI
        |   Switch LP Exp RP COL LBrace Case_List RBrace

Case_List --> Case Exp COL Stat_List Case_List
        |   Default COL Stat_List

        #add

Exp --> Exp ADD Exp
      | Exp SUB Exp
      | Exp MUL_PTR Exp
      | Exp DIV Exp
      | Exp MOD Exp
      | Exp BINAND_ADDRESS Exp
      | Exp AND Exp
      | Exp OR Exp
      | Exp BINOR Exp
      | Exp XOR Exp
      | Exp LSHIFT Exp
      | Exp RSHIFT Exp

      | Exp ADDEQ Exp
      | Exp SUDEQ Exp
      | Exp MULEQ Exp
      | Exp DIVEQ Exp
      | Exp MODEQ Exp
      | Exp BINANDEQ Exp
      | Exp BINOREQ Exp
      | Exp BINXOR Exp
      | Exp LSHIFTEQ Exp
      | Exp RSHIFTEQ Exp

      | NOT Exp
      | TIL Exp

      | Exp INC  %pred
      | INC Exp %pred
      | Exp DEC  %pred
      | DEC Exp  %pred

      | MUL_PTR Exp %pred
      | BINAND_ADDRESS Exp %pred
      | Exp DOT IDENTIFIER
      | Exp MEMBEROF IDENTIFIER
      | SIZEOF LPAREN IDENTIFIER RPAREN
      | SIZEOF Exp
      | SIZEOF LPAREN Exp RPAREN
      | Exp QUE Exp COL Exp
      | Exp ASS Exp
      | Exp COM Exp
      | LPAREN Exp RPAREN
      | IDENTIFIER
      | Constant

Specifier --> BOOL
            | INT
            | LONG
            | FLOAT
            | DOUBLE
            | CHAR
            | UNSIGNED INT
            | Struct_Dec

Constant --> TRUE
           | FALSE
           | INT_CONST
           | DOUBLE_CONST
           | CHAR_CONST
           | STRING_CONST