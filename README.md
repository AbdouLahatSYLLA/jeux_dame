# jeux_dame
Jeux de dame

Apres avoir recuperer le code il est preferable de faire un make clean, 
ensuite lancer : make 
Pour executer les programmes il faut:
- DEFENSEUR :
si c'est le defenseur (dans ce dossier nous l'avons appellé serveur) faut faire 
./serveur d'abord et une fois qu il est en marche on peut nous attaquer sur l'addresse
qui correspond à l addresse de l hebergeur du serveur.
Par exemple dans notre cas le serveur est en ecoute sur le port 7777 et est sur l'addresse
2001:910:1410:523:0:fada:4b1f:c9e5 
et c'est de cette addresse a besoin l' attaquant qui veut nous attaquer pour y parvenir.

- ATTAQUANT : 
si c'est l'attaquant (dans ce dossier nous l'avons appellé client) faut faire 
./client avec comme argument l'adresse de l'hebergeur du serveur qu' on veut attaquer.
Par exemple si on veut s'attaquer à nous meme faut avant tout s'assuerer que le serveur est en marche ensuite faire:
./client 2001:910:1410:523:0:fada:4b1f:c9e5
