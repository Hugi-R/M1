import re

def read_file (path):
    with open(path, "r") as f:
        nb_var = 0
        nb_clause = 0
        var_set = set()
        clause_list = []
        for line in f:
            line = line.strip()
            line = re.sub(' +', ' ',line)
            if line[0] == "c":
                pass
            elif line[0] == "p":
                s = line.split(" ")
                nb_var = int(s[2])
                nb_clause = int(s[3])
            elif line[0] == "%":
                break
            elif line[0] in ["-", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"]:
                s = line.split(" ")
                clause = []
                for v in s:
                    if v == "0":
                        break
                    var_set.add(abs(int(v)))
                    clause.append(int(v))
                clause_list.append(clause)
            else:
                raise Exception("Unexpected expression : %s" % line)
        assert len(var_set) == nb_var
        assert len(clause_list) == nb_clause
        return var_set,clause_list
            
        
if __name__ == "__main__":
    print(read_file("prob/uf20-01.cnf"))