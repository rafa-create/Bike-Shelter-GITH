
def check_csn_liste(CSN):
    global cartes
    cartes='C:/Users/Rafael/Documents/Cours/UE proj+com+manag/Projet 1A 60%/Bike-Shelter-GITH/Pi/cartes.txt'
    CSN=str(CSN)
    with open(cartes, "r") as f:
        lines = f.readlines()
        f.close()
    for line in lines:
        if line.strip("\n") == CSN:
            f.close()
            return True
    return False

def sup_csn_liste(CSN):
    CSN=str(CSN)
    with open(cartes, "r") as f:
        lines = f.readlines()
        f.close()
    with open(cartes, "w") as f:
        for line in lines:
            if line=='\n':
                None
            else:
                if line.strip("\n") != CSN:
                    f.write(line)
            #else:
                #return("CSN supprimé")
        #return ("Pas le CSN")#arrive pas là normalement
        f.close()
def ajouter_csn(CSN):
    f = open(cartes,"a+")
    f.write("\n")
    f.write(str(CSN))
    f.close()

CSN="04 4C 40 B 61 6 80"
if check_csn_liste(CSN):
    sup_csn_liste(CSN)
else :
    ajouter_csn(CSN)
