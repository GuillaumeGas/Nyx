#include "Const.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Bool::Bool(bool value, Position * pos) {
    this->value = new Value (value);
    this->pos = pos;
}

Bool::~Bool() {}

void Bool::print (ostream & out, int offset) const {
    out << "ConstBool(" << (value->getBool () ? "true" : "false") << ")";
}

Expression * Bool::clone () {
    Position * new_pos = new Position (pos->line, pos->column);
    return new Bool (value->getBool (), new_pos);
}

Expression * Bool::interpretExpression () { return this; }

Expression * Bool::interpretLE (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set (value->getBool () <= e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getBool () <= e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getBool () <= e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getBool () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

Expression * Bool::interpretGE (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set (value->getBool () >= e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getBool () >= e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getBool () >= e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getBool () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

Expression * Bool::interpretNE (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set (value->getBool () != e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getBool () != e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getInt () != e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getBool () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

Expression * Bool::interpretLT (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set (value->getBool () < e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getBool () < e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getBool () < e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getBool () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

Expression * Bool::interpretGT (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set (value->getBool () > e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getBool () > e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getBool () > e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getBool () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

Expression * Bool::interpretEQ (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set (value->getBool () == e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getBool () == e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getBool () == e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getBool () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

Expression * Bool::interpretAND (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set (value->getBool () && e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getBool () && e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getBool () && e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getBool () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

Expression * Bool::interpretOR (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set (value->getBool () || e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getBool () || e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getBool () || e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getBool () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

Expression * Bool::interpretPLUS (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set (value->getBool () + e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getBool () + e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getBool () + e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getBool () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}

Expression * Bool::interpretMINUS (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set (value->getBool () - e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getBool () - e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getBool () - e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getBool () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}

Expression * Bool::interpretMUL (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set (value->getBool () * e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getBool () * e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getBool () * e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getBool () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}

Expression * Bool::interpretDIV (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set (value->getBool () / e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getBool () / e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getBool () / e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getBool () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}

Expression * Bool::interpretMOD (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::INT) {
	value->set (value->getBool () % e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getBool () % e_value->getChar ());
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}


Expression * Bool::interpretUnaryMINUS () {
    value->set (value->getBool () * -1);
    return this;
}


// ####################################

Char::Char(char value, Position * pos) {
    this->value = new Value (value);
    this->pos = pos;
}

Char::~Char() {}

void Char::print (ostream & out, int offset) const {
    out << "ConstChar(" << "'" << value->getChar () << "'" << ")";
}

Expression * Char::clone () {
    Position * new_pos = new Position (pos->line, pos->column);
    return new Char (value->getChar (), new_pos);
}

Expression * Char::interpretExpression () { return this; }

Expression * Char::interpretLE (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set ((float) value->getChar () <= e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getChar () <= e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getChar () <= e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getChar () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

Expression * Char::interpretGE (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set ((float) value->getChar () >= e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getChar () >= e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getChar () >= e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getChar () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

Expression * Char::interpretNE (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set ((float) value->getChar () != e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getChar () != e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getInt () != e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getChar () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

Expression * Char::interpretLT (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set ((float) value->getChar () < e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getChar () < e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getChar () < e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getChar () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

Expression * Char::interpretGT (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set ((float) value->getChar () > e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getChar () > e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getChar () > e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getChar () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

Expression * Char::interpretEQ (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set ((float) value->getChar () == e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getChar () == e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getChar () == e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getChar () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

Expression * Char::interpretAND (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set ((float) value->getChar () && e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getChar () && e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getChar () && e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getChar () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

Expression * Char::interpretOR (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set ((float) value->getChar () || e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getChar () || e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getChar () || e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getChar () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

Expression * Char::interpretPLUS (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set ((float) value->getChar () + e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getChar () + e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getChar () + e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getChar () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}

Expression * Char::interpretMINUS (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set ((float) value->getChar () - e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getChar () - e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getChar () - e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getChar () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}

Expression * Char::interpretMUL (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set ((float) value->getChar () * e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getChar () * e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getChar () * e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getChar () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}

Expression * Char::interpretDIV (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set (value->getChar () / e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getChar () / e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getChar () / e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getChar () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}

Expression * Char::interpretMOD (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::INT) {
	value->set (value->getChar () % e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getChar () % e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getChar () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}


Expression * Char::interpretUnaryMINUS () {
    value->set (value->getChar () * -1);
    return this;
}

// ####################################

Int::Int(int v, Position * pos) {
    this->value = new Value (v);
    this->pos = pos;
}

Int::~Int() {}

void Int::print (ostream & out, int offset) const {
    out << "ConstInt(" << value->getInt () << ")";
}

Expression * Int::clone () {
    Position * new_pos = new Position (pos->line, pos->column);
    return new Int (value->getInt (), new_pos);
}

Expression * Int::interpretExpression () { return this; }

Expression * Int::interpretLE (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set ((float) value->getInt () <= e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getInt () <= e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getInt () <= e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getInt () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

Expression * Int::interpretGE (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set ((float) value->getInt () >= e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getInt () >= e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getInt () >= e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getInt () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

Expression * Int::interpretNE (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set ((float) value->getInt () != e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getInt () != e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getInt () != e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getInt () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

Expression * Int::interpretLT (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set ((float) value->getInt () < e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getInt () < e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getInt () < e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getInt () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

Expression * Int::interpretGT (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set ((float) value->getInt () > e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getInt () > e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getInt () > e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getInt () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

Expression * Int::interpretEQ (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set ((float) value->getInt () == e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getInt () == e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getInt () == e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getInt () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

Expression * Int::interpretAND (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set ((float) value->getInt () && e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getInt () && e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getInt () && e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getInt () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

Expression * Int::interpretOR (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set ((float) value->getInt () || e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getInt () || e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getInt () || e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getInt () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

Expression * Int::interpretPLUS (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set ((float) value->getInt () + e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getInt () + e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getInt () + e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getInt () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}

Expression * Int::interpretMINUS (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set ((float) value->getInt () - e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getInt () - e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getInt () - e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getInt () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}

Expression * Int::interpretMUL (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set ((float) value->getInt () * e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getInt () * e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getInt () * e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getInt () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}

Expression * Int::interpretDIV (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set ((float) value->getInt () / e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set ((float) value->getInt () / e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set ((float) value->getInt () / e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getInt () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}

Expression * Int::interpretMOD (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::INT) {
	value->set (value->getInt () % e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getInt () % e_value->getChar ());
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}


Expression * Int::interpretUnaryMINUS () {
    value->set (value->getInt () * -1);
    return this;
}

// ####################################

Float::Float (float value, Position * pos) {
    this->value = new Value (value);
    this->pos = pos;
}

Float::~Float () {}

void Float::print (ostream & out, int offset) const {
    out << "ConstFloat(" << std::to_string (this->value->getFloat ()) << ")";
}

Expression * Float::clone () {
    Position * new_pos = new Position (pos->line, pos->column);
    return new Float (value->getFloat (), new_pos);
}

Expression * Float::interpretExpression () { return this; }

Expression * Float::interpretLE (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set ( value->getFloat () <= e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getFloat () <= e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getFloat () <= e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getFloat () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

Expression * Float::interpretGE (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set (value->getFloat () >= e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getFloat () >= e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getFloat () >= e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getFloat () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

Expression * Float::interpretNE (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set (value->getFloat () != e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getFloat () != e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getFloat () != e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getFloat () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

Expression * Float::interpretLT (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set (value->getFloat () < e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getFloat () < e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getFloat () < e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getFloat () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

Expression * Float::interpretGT (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set (value->getFloat () > e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getFloat () > e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getFloat () > e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getFloat () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

Expression * Float::interpretEQ (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set (value->getFloat () == e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getFloat () == e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getFloat () == e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getFloat () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

Expression * Float::interpretAND (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set (value->getFloat () && e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getFloat () && e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getFloat () && e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getFloat () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

Expression * Float::interpretOR (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set (value->getFloat () || e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getFloat () || e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getFloat () || e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getFloat () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }
    return this;
}

Expression * Float::interpretPLUS (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set (value->getFloat () + e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getFloat () + e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getFloat () + e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getFloat () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}

Expression * Float::interpretMINUS (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set (value->getFloat () - e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getFloat () - e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getFloat () - e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getFloat () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}

Expression * Float::interpretMUL (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set (value->getFloat () * e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getFloat () * e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getFloat () * e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getFloat () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}

Expression * Float::interpretDIV (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    if (e_type == TYPE::FLOAT) {
	value->set (value->getFloat () / e_value->getFloat ());
    } else if (e_type == TYPE::INT) {
	value->set (value->getFloat () / e_value->getInt ());
    } else if (e_type == TYPE::CHAR) {
	value->set (value->getFloat () / e_value->getChar ());
    } else if (e_type == TYPE::BOOL) {
	value->set (value->getFloat () <= e_value->getBool ());
    } else {
	throw TypeErrorException (this, e, pos);
    }

    return this;
}

Expression * Float::interpretUnaryMINUS () {
    value->set (value->getFloat () * -1);
    return this;
}

// ####################################

Array::Array (vector<Expression*> * array, Position * pos) {
    this->pos = pos;
    this->array = array;
    this->value = new Value (this, "array");
}

Expression * Array::clone () {
    Position * pos = new Position (pos->line, pos->column);
    vector<Expression*> * vec = new vector<Expression*> ();

    for (auto it : *(array)) {
	vec->push_back (it->clone ());
    }
    return new Array (vec, pos);
}

Array::Array () {}

Array::~Array () {
    if (array != NULL) {
	for (auto it : *array) {
	    if (it)
		delete it;
	}
    }
}

void Array::print (ostream & out, int offset) const {
    out << "<array>[";
    if (array != NULL) {
	int i = 0;
	for (auto it : *array) {
	    it->print (out);
	    if (i < array->size () -1)
		out << ", ";
	    ++i;
	}
    }
    out << "]";
}

Expression * Array::interpretExpression () {
    for (auto & it : *array)
	it = it->interpretExpression ();
    return this;
}

Expression * Array::interpretPLUS (Expression * e) {
    Value * e_value = e->getValue ();
    TYPE e_type = e_value->getType ()->value;

    // if e is not an array, we add it at the end of the array
    if (e_type != TYPE::ARRAY && e_type != TYPE::STRING) {
	array->push_back (e->clone ());
    } else {
	Array * e_array = (Array*) e_value->getPtr ();

	for (auto it : *(e_array->array)) {
	    array->push_back (it->clone ());
	}
    }
    return this;
}

// ####################################

String::String (string str, Position * pos) {
    this->array = new vector<Expression*> ();
    for (int i = 0; i < str.size (); i++)
	this->array->push_back (new Char (str[i], pos));
    this->pos = pos;
    this->value = new Value (this, "array");
}

String::~String () {
    if (array) {
	for (auto it : *array) {
	    if (it)
		delete it;
	}
	delete array;
    }
}

void String::print (ostream & out, int offset) const {
    shift (out, offset);
    out << "\"";
    for (auto it : *array)
	out << it->getValue ()->getChar ();
    out << "\"";
}

Expression * String::interpretExpression () {
    return this;
}

// ####################################

Range::Range (Expression * start, Expression * end, Position * pos) {
    this->pos = pos;
    this->start = start;
    this->end = end;
    this->value = new Value (this, "range");
}

Expression * Range::clone () {
    Position * new_pos = new Position (pos->line, pos->column);
    return new Range (start->clone (), end->clone (), new_pos);
}

Range::~Range () {
    if (start)
	delete start;
    if (end)
	delete end;
}

void Range::print (ostream & out, int offset) const {
    out << "<range>[";
    start->print (out);
    out << " .. ";
    end->print (out);
    out << "]";
}

Expression * Range::interpretExpression () {
    start = start->interpretExpression ();
    end = end->interpretExpression ();
    if (start->getValue ()->getType ()->value != TYPE::INT) {
	Type t ("int");
	throw TypeErrorException (&t, start->getValue ()->getType (), start->pos);
    } else if (end->getValue ()->getType ()->value != TYPE::INT) {
	Type t ("int");
	throw TypeErrorException (&t, end->getValue ()->getType (), end->pos);
    }
    return this;
}
