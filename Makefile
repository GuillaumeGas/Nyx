CC := g++ -g
CFLAGS := --std=c++11 -g

all : main 

main : main.o compilo/Compilo.o parser/Lexer.o parser/Syntax.o parser/Token.o parser/syntax/Program.o parser/syntax/Type.o parser/syntax/Assign.o ast/Ast.o ast/Program.o ast/Type.o ast/VarDecl.o ast/Position.o ast/IntValue.o ast/StringValue.o ast/VarAssign.o ast/Value.o
	$(CC) $(CFLAGS) $(LIBSDIR) -o $@ $^ $(LIBS)	

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLDIR) -o $@ -c $< 

clean:
	rm *.o;rm compilo/*.o;rm parser/*.o;rm ast/*.o;rm *~;rm compilo/*~;rm parser/*~;rm ast/*~;rm parser/syntax/*~;rm parser/syntax/*.o
