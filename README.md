# Interpret

Projet personnel pour le fun, la passion...
Ebauche d'un interpréteur avec une syntaxe proche de celle du C.

Exemple simple :

```C++
void main()
{
	$println("Hello world !");

	$print("Give a first number : ");
	let a = $readInt();
	$print("Give a second number : ");
	let b = $readInt();
	let c = 0;
	$println("Result : ", add(a, b));
}

int add (int a, int b)
{
	return a + b;
}
```

Capture d'écran du résultat :
![Screenshot](screenshots/screenshot.bmp)

# Détails

- Le dossier 'parser' contient la lexer ainsi que l'analyseur syntaxique, ce dernier étant basé sur le pattern visitor.
- Le dossier ast contient les classes permettant de créer l'arbre de syntaxe abstrait
- Le dossier symbol contient le nécessaire pour gérer la table des symboles (classe singleton).
- Le dossier global permet d'avoir des info sur le fichier sur lequel on travail (va nous permettre d'afficher la ligne comportant une erreur par exemple..)

# TODO

- Analyse statique / variables non utilisées : ajouter position du symbol
- Ajouter import
- Refaire index de tableau
- Ajouter classes
