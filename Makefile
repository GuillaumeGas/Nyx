CC := g++ -g
CFLAGS := --std=c++11 -g

all : main 

main : main.o compilo/Compilo.o parser/Lexer.o parser/Syntaxe.o parser/Token.o ast/Ast.o ast/Program.o ast/Type.o ast/VarDecl.o
	$(CC) $(CFLAGS) $(LIBSDIR) -o $@ $^ $(LIBS)	

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLDIR) -o $@ -c $< 

clean:
	rm *.o;rm compilo/*.o;rm parser/*.o;rm ast/*.o
