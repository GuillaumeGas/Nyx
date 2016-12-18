# Interpret

Projet personnel pour le fun, la passion...
Ebauche d'un interpréteur avec une syntaxe proche de celle du C.

Syntaxe actuellement acceptée :

```C++
void print (int val) {
    int a, b = 2;
    $print_i (val);
}
int main (int a, int b) {
    while:test (test) {
	    foo ([1, 2, 3]);
	if (a) {
	    for (i in foo (a) .. 3+5) {
		print (fo(), 5+i);
	    }
	    break test;
	} else {
	    for (a in [1, 2, 3]) {
		print (a);
	    }
	}
    }
    return 2*(2+3);
}
```

# Détails

- Le dossier 'parser' contient la lexer ainsi que l'analyseur syntaxique, ce dernier étant basé sur le pattern visitor.
- Le dossier ast contient les classes permettant de créer l'arbre de syntaxe abstrait
- Le dossier symbol contient le nécessaire pour gérer la table des symboles (classe singleton).
- Le dossier global permet d'avoir des info sur le fichier sur lequel on travail (va nous permettre d'afficher la ligne comportant une erreur par exemple..)
