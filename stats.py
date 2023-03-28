import sqlite3

# Connexion à la base de données
conn = sqlite3.connect('event.db')

# Récupération des événements et affichage des attributs "title" et "date"
cursor = conn.execute("SELECT sum(nbplace) FROM events order by type")
for row in cursor:
    print(f"Titre : {row[0]}, Date : {row[1]}")

# Fermeture de la connexion à la base de données
conn.close()