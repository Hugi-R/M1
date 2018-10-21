%{

open Quad
open Common
open Comp
open Karel


%}

%token BEGIN_PROG
%token BEGIN_EXEC
%token END_EXEC
%token END_PROG

%token MOVE
%token TURN_LEFT
%token TURN_OFF
%token PICK_BEEPER
%token PUT_BEEPER
%token NEXT_TO_A_BEEPER
%token FRONT_IS_CLEAR
%token FRONT_IS_BLOCKED
%token LEFT_IS_CLEAR
%token LEFT_IS_BLOCKED
%token RIGHT_IS_CLEAR
%token RIGHT_IS_BLOCKED
%token NEXT_TO_A_BEEPER
%token NOT_NEXT_TO_A_BEEPER
%token FACING_NORTH
%token NOT_FACING_NORTH
%token FACING_EAST
%token NOT_FACING_EAST
%token FACING_SOUTH
%token NOT_FACING_SOUTH
%token FACING_WEST
%token NOT_FACING_WEST
%token ANY_BEEPERS_IN_BEEPER_BAG
%token NO_BEEPERS_IN_BEEPER_BAG

%token ITERATE
%token TIMES
%token WHILE
%token DO
%token IF
%token THEN
%token ELSE
%token DEFINE_NEW
%token AS

%token <int> INT
%token <string> ID

%token SEMI
%token BEGIN
%token END

/* rend THEN et ELSE associatif a droite
Le conflit IF-THEN-ELSE sera donc résolu en faisant un shift sur ELSE */
%right THEN ELSE

%type <unit> prog
%start prog

%%

prog:	BEGIN_PROG define BEGIN_EXEC stmts_opt END_EXEC END_PROG
			{ () }
;

define:
	/* empty */	{ () }
|	define_new define { () }
;

stmts_opt:	/* empty */		{ () }
|			stmts			{ () }
;

stmts:		stmt			{ () }
|			stmts SEMI stmt	{ () }
|			stmts SEMI		{ () }
;

stmt:		simple_stmt
				{ () }
;

simple_stmt: TURN_LEFT
				{ gen (INVOKE (turn_left, 0, 0)) }
|			TURN_OFF
				{ gen STOP  }
|			MOVE
				{ gen (INVOKE (move, 0, 0)) }
|			PICK_BEEPER
				{ print_string "pickbeeper\n" }
|			PUT_BEEPER
				{ print_string "putbeeper\n" }
|			BEGIN stmts END {()}
|			ITERATE INT TIMES stmt { print_string "iterate\n" }
|			WHILE test DO stmt { print_string "while\n" }
|			IF test THEN stmt { print_string "if\n" }
|			IF test THEN stmt ELSE stmt { print_string "ifelse\n" }
|			ID { if is_defined $1 then print_string "id $1\n" else (raise (SyntaxError "ID not defined")) }
;

test:
|	FRONT_IS_CLEAR {()}
|	FRONT_IS_BLOCKED {()}
|	LEFT_IS_CLEAR {()}
|	LEFT_IS_BLOCKED {()}
|	RIGHT_IS_CLEAR {()}
|	RIGHT_IS_BLOCKED {()}
|	NEXT_TO_A_BEEPER {()}
|	NOT_NEXT_TO_A_BEEPER {()}
|	FACING_NORTH {()}
|	NOT_FACING_NORTH {()}
|	FACING_EAST {()}
|	NOT_FACING_EAST {()}
|	FACING_SOUTH {()}
|	NOT_FACING_SOUTH {()}
|	FACING_WEST {()}
|	NOT_FACING_WEST {()}
|	ANY_BEEPERS_IN_BEEPER_BAG {()}
|	NO_BEEPERS_IN_BEEPER_BAG {()}
;

define_new:
|	DEFINE_NEW ID AS stmts { if is_defined $2 then raise (SyntaxError "ID already defined") else define $2 0 }
