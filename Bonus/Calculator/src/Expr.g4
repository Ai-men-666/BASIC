grammar Expr;
calc:	expr EOF ;
expr:	expr (op = MUL | op = DIV) expr # MulDiv
    |	expr (op = ADD | op = SUB) expr # AddSub
    |	INT # Int
    |	LPAREN expr RPAREN # Parens
    ;

WS      : [ \t\r\n]+ -> skip ;
INT     : [1-9][0-9]* ;
ADD     : '+' ;
SUB     : '-' ;
MUL     : '*' ;
DIV     : '/' ;
LPAREN  : '(' ;
RPAREN  : ')' ;
