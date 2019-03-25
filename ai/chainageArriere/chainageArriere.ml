
let rules = [
    ("phanerogame",["fleur";"graine"]);
    ("phanerogame",["fleur";"graine-nue"]);
    ("sapin",["phanerogame";"graine-nue"]);
    ("monocotyledone",["phanerogame";"1-cotyledone"])
];;

let string_list l = let rec tmp = fun str l ->
                    match l with
                    | s::l -> tmp (str^", "^s) l
                    | [] -> str
                  in match l with
                     | s::l -> tmp s l
                     | [] -> ""
;;

let rec print_rules  = function
                    | [] -> print_string "PR_FIN\n"
                    | (a,l)::rl -> print_string (a^",["^(string_list l)^"]\n"); print_rules rl
;;

let facts = ["fleur"; "graine-nue"];;

let rec find_in_rules = fun rules obj ->
  match rules with
  | [] -> ([],[])
  | (o,l)::rl -> if obj = o then (print_rules rl ; (l,rl)) else find_in_rules rl obj
;;

let rec is_in_facts = fun facts goal ->
  match facts with
  | [] -> false
  | g::f -> if goal = g then true else is_in_facts f goal
;;

let demonstrate = fun rules facts goal ->
  if is_in_facts facts goal then ((true,[]),rules) else ( let (res,rules_left) =  (find_in_rules rules goal) in ((not (res = []),res),rules_left))
;;

(*
let rec chainage_arriere = fun rules facts goals ->
  match goals with
  | [] -> true
  | g::lg -> match demonstrate rules facts g with
            | (true,[]),rl -> (print_string (g^" OK\n") ; chainage_arriere rules (g::facts) lg)
            | (true,sg),rl -> (print_string ("New sub goals : "^(string_list sg)^".\n") ; chainage_arriere rules facts sg)
            | (false,_),[] ->  (print_string (g^" KO2\n") ; false)
            | (false,_),rl ->  (print_string (g^" KO3\n") ; chainage_arriere rl facts goals)
;;
 *)

let rec chainage_arriere = fun rules facts goals indent->
  match goals with
  | [] -> true
  | g::lg -> print_string (indent^"On souhaite démontrer "^g^" :\n") ;if is_in_facts facts g then (print_string (indent^g^" démontré, il est présent dans les faits.\n");chainage_arriere rules facts lg indent) else
     if demBut rules facts g indent
     then (print_string (indent^g^" démontré.\n"^indent^"Il a été ajouté à la base de faits.\n") ;chainage_arriere rules (g::facts) lg indent)
     else (print_string (indent^g^" n'a pas pu être démontré.\n") ; false)
and demBut = fun rules facts goal indent ->
    let rec tmp = function
      | [] -> false
      | (a,l)::lr -> if a = goal
                     then (print_string (indent^"  On utilise la règle ("^(string_list l)^") -> "^a^".\n"^indent^"Nouveaux sous buts : "^(string_list l)^".\n"); if (chainage_arriere rules facts l ("  "^indent)) then true else (print_string (indent^"Bactrack...\n"^indent^"On continue d'essayer de démontrer "^goal^" :\n");tmp lr)) else tmp lr
    in tmp rules
;;


let goals = ["sapin"];;

chainage_arriere rules facts goals "";;
