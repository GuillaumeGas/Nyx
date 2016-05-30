// #include "PrintI.hpp"

// using namespace std;
// using namespace bob;
// using namespace syntax;

// void PrintI::analyze(Syntax * syntax, unsigned int index) {
//   Token * par_l = syntax->get_token(index+1);
  
//   if(par_l == NULL || par_l->type != TokenType::PAR_L)
//     throw MissingErrorException("(", Position(par_l->line, par_l->column));
  
//   //TODO aller chercher une expression entière, mettre à jour l'index à la fin de l'expression pour vérifier la suite

//   Token * par_r = syntax->get_token(index+3);
//   Token * semicolon = syntax->get_token(index+4);

//   if(par_r == NULL || par_r->type != TokenType::PAR_R)
//     throw MissingErrorException(")", Position(par_r->line, par_r->column));
//   if(semicolon == NULL || semicolon->type != TokenType::SEMICOLON)
//     throw MissingErrorException(";", Position(semicolon->line, semicolon->column));

  
// }
