%{

open Quad
open Common
open Comp
open Karel

let zero = new_temp();;
let one = new_temp();;
let beeps = [| new_temp(); new_temp(); new_temp(); new_temp() |];;
let beeps_global = new_temp();;

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
%token RESET
%token COUNT
%token FROM
%token TO

%token <int> INT
%token <string> ID
%token <int> BEEPS

%token SEMI
%token BEGIN
%token END

/* rend THEN et ELSE associatif a droite
Le conflit IF-THEN-ELSE sera donc résolu en faisant un shift sur ELSE */
%right THEN ELSE

%type <unit> prog
%start prog

%%

start_prog : /* empty */ {gen (SETI (zero, 0));gen (SETI (one, 1));gen (SETI (beeps_global, 0));let a = nextquad () in gen (GOTO 0); a}

prog:	BEGIN_PROG start_prog define BEGIN_EXEC adr stmts_opt END_EXEC END_PROG
			{ backpatch $2 $5; gen (STOP) } /* add stop at the end */
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
;

iter : INT { let cpt = new_temp () in gen (SETI (cpt, 0)); let n = new_temp () in gen (SETI (n, $1)); let startl = nextquad () in gen (GOTO_EQ (0, cpt, n)); gen (ADD (cpt, cpt, one)); startl }
| BEEPS { let cpt = new_temp () in gen (SETI (cpt, 0)); let startl = nextquad () in gen (GOTO_EQ (0, cpt, beeps.($1))); gen (ADD (cpt, cpt, one)); startl }
;

else_ : ELSE { let a = nextquad () in gen (GOTO 0); a }
;

simple_stmt: TURN_LEFT
				{ gen (INVOKE (turn_left, 0, 0)) }
|			TURN_OFF
				{ gen STOP  }
|			MOVE
				{ gen (INVOKE (move, 0, 0)); let d = new_temp () in gen (INVOKE (next_beeper, d, 0)); let a = nextquad() in gen (GOTO_EQ (0, d, zero)); gen (ADD (beeps_global, beeps_global, one)); backpatch a (nextquad()) }
|			PICK_BEEPER
				{ gen (INVOKE (pick_beeper, 0, 0)) }
|			PUT_BEEPER
				{ gen (INVOKE (put_beeper, 0, 0)) }
|			BEGIN stmts END {()}
|			ITERATE iter TIMES stmt { let _ = gen (GOTO $2) in backpatch $2 (nextquad ()) }
|			WHILE adr if_test DO stmt {let _ = gen (GOTO $2) in backpatch $3 (nextquad ()) }
|			IF if_test THEN stmt { backpatch $2 (nextquad ()) }
|			IF if_test THEN stmt else_ adr stmt { backpatch $2 ($6); backpatch $5 (nextquad ()) }
|			ID { if is_defined $1 then gen (CALL (get_define $1)) else (raise (SyntaxError "ID not defined")) }
|			RESET BEEPS {gen (SETI (beeps.($2), 0))}
|			COUNT BEEPS init_count stmt {let cpt = new_temp() in gen (SUB (cpt, beeps_global, $3)); gen (SET (beeps.($2), cpt)) }
|			fromto stmt {}
;

fromto : FROM BEEPS TO BEEPS { let cpt = new_temp () in gen (SET (cpt, beeps.($2))); let startl = nextquad () in gen (GOTO_EQ (0, cpt, beeps.($4))); gen (ADD (cpt, cpt, one)); backpatch startl (nextquad()) }

init_count : /* */ {let tmp = new_temp() in gen (SET (tmp, beeps_global)); tmp}

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

prologue : ID { if is_defined $1 then raise (SyntaxError "ID already defined") else define $1 (nextquad ()) }

define_new:
|	DEFINE_NEW prologue AS stmts { gen (RETURN) }
;

if_test : test {
	let a = nextquad () in
	let _ = gen (GOTO_EQ (0, $1, zero)) in
	a
}
;
