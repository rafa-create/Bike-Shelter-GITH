from dns.resolver import query
import mysql.connector
import datetime
from mysql.connector import errorcode
from mysql.connector.errors import get_mysql_exception


class DBConnector():

    def __init__(self,user ="root", pswd ="",db="historique-vélos", host ="127.0.0.1"):
        try:
            self.__cnx=mysql.connector.connect(user=user,password=pswd,host=host,database=db)
        except mysql.connector.Error as err:
            if err.errno == errorcode.ER_ACCESS_DENIED_ERROR:
                print("Something is wrong with your user name or password")
            if err.errno==errorcode.ER_BAD_DB_ERROR:
                print("DB does not exist")
            else:
                print(err)

    def Afficherhistorique(self):
        cursor = self.__cnx.cursor()
        cursor.execute("SELECT * FROM historique")
        for row in cursor :
            print (row)
        cursor.close()

    def Rechercher(self, firstname,lastname):
        cursor = self.__cnx.cursor()
        cursor.execute(" SELECT* FROM historique WHERE first_name= %s AND last_name=%s", (firstname,lastname))
        res=list(cursor.fetchall())
        cursor.close()
        print (res)


    def Creer_ligne(self, firstname,lastname,hiredate,gender,birthdate):
        cursor=self.__cnx.cursor()
        cursor.execute(" SELECT max(historique.emp_no) from historique")
        lastid=cursor.fetchall()[0][0]
        query2=("INSERT INTO historique"
            "(carte,action,date_heure)"
            "VALUES (%s,%s,%s)")
        lastid+=1
        cursor=self.__cnx.cursor()
        cursor.execute(query2,(lastid,firstname,lastname,hiredate,gender,birthdate))
        self.__cnx.commit()
        cursor.close()
        print(firstname,"a ete ajouté et son id est:",lastid)

    def Sup_employee_par_id(self,num_id):
        cursor=self.__cnx.cursor()
        cursor.execute(" delete from employees where emp_no= %s",(num_id,))
        self.__cnx.commit()
        res=list(cursor.fetchall())
        cursor.close()
        print("L'employé qui a comme id ",num_id,"a été supprimé")



continuer=True
while continuer:
    print("Que voulez vous faire ?")
    print(" 1 Afficher l'historique'")
    print(" 4 Faire une recherche")
    print(" 5 Créer une ligne")
    print(" 6 Supprimer un registre")
    n = int(input("Veuillez choisir votre numéro:"))
    print("")
    if n==1:
        DBConnector().Afficherhistorique()
    if n==4:
        carte = str(input("Veuillez choisir le numero de carte à rechercher:"))
        DBConnector().Rechercher(carte)
    if n==5:
        carte = str(input("Renseignez le numéro de carte':"))
        action= str(input("Renseignez l'action efféctuée:"))

        DBConnector().Creer_employee(carte,action, datetime.date(2021, 7, 5),, datetime.date(1962, 7, 5))
    if n==6:
        id_a_sup=str(input("Renseignez l'id du registre de l'employé à supprimer "))
        DBConnector().Sup_employee_par_id(id_a_sup)

    print("")
    a = str(input("Voulez vous faire une autre requète (oui ou non) ? "))

    if a=="oui":
        continuer=True
    else:
        continuer=False
