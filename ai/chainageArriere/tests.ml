#use "chainageArriere.ml";;
#use "baseDeRegle.ml";;

(* Test simple : *)
let goal = ["alcool"];;
let facts = ["ester"; "bicarbonate de sodium"; "chaleur"];;
chainage_arriere chimie facts goal "";;

(* Test backtrack *)
