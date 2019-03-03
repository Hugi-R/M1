let rules = [
    ("phanerogame",["fleur";"graine"]);
    ("sapin",["phanerogame";"graine-nue"]);
    ("monocotyledone",["phanerogame";"1-cotyledone"])
];;

let string_list = let rec tmp = fun str l ->
                    match l with
                    | s::l -> tmp (str^" "^s) l
                    | [] -> str
                  in tmp ""
;;

let facts = ["fleur"; "graine"];;

let rec find_in_rules = fun rules obj ->
  match rules with
  | [] -> []
  | (o,l)::rules -> if obj = o then l else find_in_rules rules obj
;;

let rec is_in_facts = fun facts goal ->
  match facts with
  | [] -> false
  | g::f -> if goal = g then true else is_in_facts f goal
;;

let demonstrate = fun rules facts goal ->
  if is_in_facts facts goal then (true,[]) else ( let res = (find_in_rules rules goal) in (not (res = []),res) )
;;

let rec chainage_arriere = fun rules facts goals ->
  match goals with
  | [] -> true
  | g::lg -> match demonstrate rules facts g with
            | true,[] -> (print_string (g^" OK \n") ; chainage_arriere rules (g::facts) lg)
            | true,sg -> print_string ("New sub goals : "^(string_list sg)^".\n") ; if chainage_arriere rules facts sg then
                                                                                 (print_string (g^" OK \n") ; chainage_arriere rules (g::facts) lg) else
                                                                                 (print_string (g^" KO \n") ; false)
            | false,_ ->  (print_string (g^" KO\n") ; false)
;;

let goals = ["sapin"];;

chainage_arriere rules facts goals;;
