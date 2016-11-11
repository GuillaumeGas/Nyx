# Interpret

Projet personnel pour le fun, la passion...
Ebauche d'un interpréteur avec une syntaxe proche de celle du C.

Syntaxe actuellement acceptée :

```
int main (int args) {
    int a, b = 2, c;
    for (i in 0 .. 10) {
        $printi (i); //syscall
    }
    while (1) {
        $printi (a);
    }
}
```

# Détails

- Le dossier 'parser' contient la lexer ainsi que l'analyseur syntaxique, ce dernier étant basé sur le pattern visitor.
- Le dossier ast contient les classes permettant de créer l'arbre de syntaxe abstrait
- Le dossier symbol contient le nécessaire pour gérer la table des symboles (classe singleton).
- Le dossier global permet d'avoir des info sur le fichier sur lequel on travail (va nous permettre d'afficher la ligne comportant une erreur par exemple..)