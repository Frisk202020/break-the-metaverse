Ce projet est mon premier projet informatique, et est un ensemble d'utilitaires pour mon scénario de jeux de rôles *Break The Metaverse*, le code se découpe en 3 parties distinctes :

- Le code C est un [logiciel de combat RPG](src/battle/) utilisé en temps réel par le maitre du jeu pour animer une portion du scénario
- Le code Rust est un [serveur](server/) web qui héberge un interface graphique utilisé par un des joueurs durant l'entiereté du scénario. L'interface simule un ordinateur de "hacker" en restant accessible pour tout type de joueurs.
- Le code Python ne représente que quelques utilitaires notamment pour générer des images.

Le code du logiciel de combat a reçu des *ébauches* d'adaptation en C++ et Java, dans le but d'apprendre ces languages en pratique. Les codes sont trouvables dans leur branche respective.

Une version finale des *Book MJ* (descriptif du scénario) ont été ajouté à ce répertoire pour les plus curieux.