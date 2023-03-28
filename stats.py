import sqlite3

# Connexion à la base de données
conn = sqlite3.connect('event.db')

# Récupération des événements et affichage des attributs "title" et "date"
cursor = conn.execute("SELECT sum(nbplace) as sum, type FROM events GROUP by type")

for row in cursor:
    print(f"📊 Nombre de Place : {row[0]} | 🗂️ Type : {row[1]}")

# Fermeture de la connexion à la base de données
conn.close()