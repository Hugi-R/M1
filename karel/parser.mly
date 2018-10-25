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

adr : /* empty */ { nextquad () }

simple_stmt: TURN_LEFT
				{ gen (INVOKE (turn_left, 0, 0)) }
|			TURN_OFF
				{ gen STOP  }
|			MOVE
				{ gen (INVOKE (move, 0, 0)) }
|			PICK_BEEPER
				{ gen (INVOKE (pick_beeper, 0, 0)) }
|			PUT_BEEPER
				{ gen (INVOKE (put_beeper, 0, 0)) }
|			BEGIN stmts END {()}
|			ITERATE INT TIMES stmt { print_string "iterate\n" }
|			WHILE adr if_test DO stmt { backpatch $2 (nextquad ()); gen (GOTO ($3, 0, 0)) }
|			IF if_test THEN stmt { backpatch $2 (nextquad ()) }
|			IF if_test THEN stmt ELSE stmt { print_string "ifelse\n" }
|			ID { if is_defined $1 then print_string "id $1\n" else (raise (SyntaxError "ID not defined")) }
;

test:
	FRONT_IS_CLEAR {let d = new_temp () in gen (INVOKE (is_clear, front, d)); d}
|	FRONT_IS_BLOCKED {let d = new_temp () in gen (INVOKE (is_blocked, front, d)); d}
|	LEFT_IS_CLEAR {let d = new_temp () in gen (INVOKE (is_clear, left, d)); d}
|	LEFT_IS_BLOCKED {let d = new_temp () in gen (INVOKE (is_blocked, left, d)); d}
|	RIGHT_IS_CLEAR {let d = new_temp () in gen (INVOKE (is_clear, right, d)); d}
|	RIGHT_IS_BLOCKED {let d = new_temp () in gen (INVOKE (is_blocked, right, d)); d}
|	NEXT_TO_A_BEEPER {let d = new_temp () in gen (INVOKE (next_beeper, d, 0)); d}
|	NOT_NEXT_TO_A_BEEPER {let d = new_temp () in gen (INVOKE (no_next_beeper, d, 0)); d}
|	FACING_NORTH {let d = new_temp () in gen (INVOKE (facing, north, d)); d}
|	NOT_FACING_NORTH {let d = new_temp () in gen (INVOKE (not_facing, north, d)); d}
|	FACING_EAST {let d = new_temp () in gen (INVOKE (facing, east, d)); d}
|	NOT_FACING_EAST {let d = new_temp () in gen (INVOKE (not_facing, east, d)); d}
|	FACING_SOUTH {let d = new_temp () in gen (INVOKE (facing, south, d)); d}
|	NOT_FACING_SOUTH {let d = new_temp () in gen (INVOKE (not_facing, south, d)); d}
|	FACING_WEST {let d = new_temp () in gen (INVOKE (facing, west, d)); d}
|	NOT_FACING_WEST {let d = new_temp () in gen (INVOKE (not_facing, west, d)); d}
|	ANY_BEEPERS_IN_BEEPER_BAG {let d = new_temp () in gen (INVOKE (any_beeper, d, 0)); d}
|	NO_BEEPERS_IN_BEEPER_BAG {let d = new_temp () in gen (INVOKE (no_beeper, d, 0)); d}
;

define_new:
|	DEFINE_NEW ID AS stmts { if is_defined $2 then raise (SyntaxError "ID already defined") else define $2 0 }
;

if_test : test {
	let z = new_temp () in
	let _ = gen (SETI (z, 0)) in
	let a = nextquad () in
	let _ = gen (GOTO_EQ (0, $1, z)) in
	a
}
;