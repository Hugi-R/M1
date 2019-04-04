
let rules = [
    (1,"phanerogame",["fleur";"graine"],0);
    (2,"sapin",["phanerogame";"graine-nue"],0);
    (3,"monocotyledone",["phanerogame";"1-cotyledone"],0);
    (4,"dicotyledone",["phanerogame";"2-cotyledone"],0);
    (5,"muguet",["monocotyledone";"rhizome"],0);
    (6,"anemone",["dicotyledone"],0);
    (7,"lilas",["monocotyledone";"-rhizome"],0);
    (8,"cryptogame",["feuille";"fleur"],0);
    (9,"mousse",["cryptogame";"-racine"],0);
    (10,"fougere",["cryptogame";"racine"],0);
    (11,"thallophyte",["-feuille";"plante"],0);
    (12,"algue",["thallophyte";"chlorophylle"],0);
    (13,"champignon",["thallophyte";"-chlorophylle"],0);
    (14,"colibacille",["-feuille";"-fleur";"-plante"],0);
];;

(************************************************************)
let string_list
(************************************************************)
( l : string list ) (* une liste de string                  *)
(************************************************************)
(* retourne un string composé des éléments de la liste      *)
(* séparés par une virgule                                  *)
(************************************************************)
: string
(************************************************************)
 = let rec tmp = fun str l ->
                    match l with
                    | s::l -> tmp (str^", "^s) l
                    | [] -> str
                  in match l with
                     | s::l -> tmp s l
                     | [] -> ""
;;

(************************************************************)
let str_rule
(************************************************************)
(num,a,l,_) (* une règle                                    *)
(************************************************************)
(* retourne le string de la règle, de la forme :            *)
(* Règle <int> : (<liste de string>) -> <string>            *)
(************************************************************)
: string
(************************************************************)
= ("Règle "^(string_of_int num)^" : ("^(string_list l)^") -> "^a)
;;

(************************************************************)
let rec is_in_facts
(************************************************************)
( facts : string list ) (* la liste de fait                 *)
( goal : string )       (* le but a trouver                 *)
(************************************************************)
(* retourne true si le but est dans la liste de fait        *)
(************************************************************)
: bool
(************************************************************)
= match facts with
  | [] -> false
  | g::f -> if goal = g then true else is_in_facts f goal
;;

(************************************************************)
let incRules
( num : int )                         (* un numero de règle *)
( rules : (int * string * string list * int) list )
(* une liste de règle                                       *)
(************************************************************)
(* retourne la liste de règle, avec le compteur de la règle *)
(* num incrémenté                                           *)
(************************************************************)
: (int * string * string list * int) list
(************************************************************)
= List.map (fun (n,a,r,it) -> if n = num then (n,a,r,it+1) else (n,a,r,it)) rules
;;

(************************************************************)
let rec chainage_arriere
(************************************************************)
( rules : (int * string * string list * int) list )
                        (* la base de règles                *)
( facts : string list ) (* la base de faits                 *)
( goals : string list ) (* une liste de buts                *)
( indent : string )     (* indentation de l'affichage       *)
                        (* ("" pour commencer)              *)
(************************************************************)
(* inférence par chainage arrière sur les buts goals, avec  *)
(* comme base de règles rules et comme base de fait facts   *)
(************************************************************)
: bool
(************************************************************)
= match goals with
  | [] -> true
  | g::lg -> print_string (indent^"On souhaite démontrer "^g^" :\n") ;
    if is_in_facts facts g
    then (print_string (indent^g^" démontré, il est présent dans les faits.\n");chainage_arriere rules facts lg indent)
    else
      if demBut rules facts g indent
      then (print_string (indent^g^" démontré.\n"^indent^"Il a été ajouté à la base de faits.\n") ;chainage_arriere rules (g::facts) lg indent)
      else (print_string (indent^g^" n'a pas pu être démontré.\n") ; false)
and demBut = fun rules facts goal indent ->
    let rec tmp = function
      | [] -> false
      | (num,a,l,it)::lr ->
        if it > 2 (* nombre de bouclage autorisé, 2 pour éviter un pavé de texte *)
        then ((print_string (indent^"Trop d'iteration (>10) sur la règle "^(str_rule (num,a,l,it))^".\n"^indent^"Bactrack...\n"^indent^"On continue d'essayer de démontrer "^goal^" :\n"));tmp lr)
        else if a = goal
            then (print_string (indent^"On utilise la "^(str_rule (num,a,l,it))^".\n"^indent^"Nouveaux sous buts : "^(string_list l)^".\n");
                if (chainage_arriere (incRules num rules) facts l ("  "^indent))
                then true
                else (print_string (indent^"Bactrack...\n"^indent^"On continue d'essayer de démontrer "^goal^" :\n");tmp lr))
            else tmp lr
    in tmp rules
;;

