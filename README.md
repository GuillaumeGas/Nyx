# Interpret

Projet personnel pour le fun, la passion...
Ebauche d'un interpréteur avec une syntaxe proche de celle du C.

Syntaxe actuellement acceptée :

```
void print_i (int val) {
    $printi (val, 0);
}

int main () {
    int a = 0;
    for (i in 0 .. 10) {
	while:test (true) {
	    a = a + 1;
	    if (a > 10) {
	        break test;
	    }
	}
    }
    for:f (a in 20 .. 0) {
	print_i (a);
    }
    return 0;
}
```

# Détails

- Le dossier 'parser' contient la lexer ainsi que l'analyseur syntaxique, ce dernier étant basé sur le pattern visitor.
- Le dossier ast contient les classes permettant de créer l'arbre de syntaxe abstrait
- Le dossier symbol contient le nécessaire pour gérer la table des symboles (classe singleton).
- Le dossier global permet d'avoir des info sur le fichier sur lequel on travail (va nous permettre d'afficher la ligne comportant une erreur par exemple..)