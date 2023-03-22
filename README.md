# jeux_dame
Jeux de dame

Après avoir récupéré le code il est préférable de faire un 'make clean',
ensuite lancer : make

Pour exécuter les programmes il faut:

- Partie Défenseur :
si c'est le défenseur (dans ce dossier nous l'avons appelé serveur) faut faire
./serveur d'abord et une fois qu il est en marche on peut nous attaquer sur l'adresse
qui correspond à l'adresse de l hébergeur du serveur.
Par exemple dans notre cas le serveur est en écoute sur le port 7777 et est sur l'adresse
2001:910:1410:523:0:fada:4b1f:c9e5
et c'est de cette adresse a besoin l'attaquant qui veut nous attaquer pour y parvenir.

- Partie attaquant :
si c'est l'attaquant (dans ce dossier nous l'avons appelé client) faut faire
./client avec comme argument l'adresse de l'hébergeur du 'serveur' qu'on veut attaquer.
Par exemple si on veut s'attaquer à nous même faut avant tout s'assurer que le serveur est en marche ensuite faire:
./client 127.0.0.1 
