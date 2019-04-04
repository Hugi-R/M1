let chimie = [
    (1, "dioxyde de carbone", ["bicarbonate de sodium"; "chaleur"], 0); (* decomposition du bicarbonate de sodium a la chaleur *)
    (2, "eau", ["bicarbonate de sodium"; "chaleur"], 0);
    (3, "eau", ["alcool";"acide carboxylique"],0); (* esterification *)
    (4, "ester", ["alcool";"acide carboxylique"],0);
    (5, "alcool", ["ester";"eau"], 0); (* retro esterification *)
    (6, "acide carboxylique", ["ester";"eau"], 0);
    (7, "dioxyde de carbone", ["acide carboxylique"; "eau"], 0); (* electrolyse de kolbe *)
    (8, "dioxygene", ["dioxyde de carbone"; "eau"; "photon"], 0); (* photosynthese oxygenique *)
    (9, "eau", ["dioxyde de carbone"; "hydrogene sulfure"; "photon"], 0); (* photosynthese anoxygenique des bacteries pourpres sulfureuses*)
    (10, "eau", ["glucose"; "NAD"; "polyphosphate"; "ADP"], 0); (* glycolyse (respiration cellulaire) *)
    (11, "ATP", ["glucose"; "NAD"; "polyphosphate"; "ADP"], 0);
    (12, "proton", ["glucose"; "NAD"; "polyphosphate"; "ADP"], 0);
    (13, "eau", ["aldehyde"; "argent"; "hydroxide"], 0); (* reaction de Tollens *)
    (14, "acide carboxylique", ["aldehyde"; "argent"; "hydroxide"], 0);
    (15, "argent", ["aldehyde"; "argent"; "hydroxide"], 0);
    (16, "dioxyde de carbone", ["carbone"; "dioxygene"], 0); (* combustion du carbone *)
    (17, "dioxyde de carbone", ["sucre"; "dioxygene"], 0); (* respiration *)
    (18, "dioxygene", ["eau"], 0); (* electrolyse *)
    (19, "hydrogene", ["eau"], 0);
    (20, "photon", ["luciferine"; "ATP"; "magnesium"; "dioxygene"], 0) (* bioluminescence luciferase *)
  ]
;;

