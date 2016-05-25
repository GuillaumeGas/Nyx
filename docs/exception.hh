#pragma once

#include <exception>
#include <utils/file_reader.hh>
#include <parser/parser_decl.hh>

namespace Ymir {

    struct YmirException {
	YmirException(File::Word & w) : m_text(w.str) {}
	YmirException(const char * f) : m_text(f) {}
	YmirException() {}

	std::string str() { return m_text; }
	std::string m_text;
    };


    struct _YmirException_ {
	_YmirException_(File::Word & w) : m_text(w.str) {}
	_YmirException_(const char * f) : m_text(f) {}
	_YmirException_() {}

	std::string str() { return m_text; }
	std::string m_text;
    };

    
    struct SyntaxError : YmirException {

		SyntaxError() {}

		SyntaxError(File::Word & w)  {
	   	 	std::stringstream ss;
	    	ss << "Unexpected '" << w.str << "' line : " << w.line << " col : " << w.col;
	   		m_text = ss.str();
	   		this->w = w;
		}

		File::Word w;
    };

      struct MissingError : SyntaxError {
	    MissingError(File::Word & w, const char * c)  {
		  std::stringstream ss;
		  ss << "Expected '" << c << "' after '" << w.str << "' line : " << w.line << " col : " << w.col;
		  m_text = ss.str();
		  this->w = w;
	    }
	    File::Word w;
      };


    struct FileNotFoundException : _YmirException_ {
	FileNotFoundException(File::Word & d)  {
	    std::stringstream ss;
	    ss << "File '" << d.str << "' not found required from (" << d.line << ", " << d.col << ")";
	    m_text = ss.str();
	}

	FileNotFoundException(File::Word & d, const char * file)  {
	    std::stringstream ss;
	    ss << "File '" << d.str << "' not found required from '" << file << "' (" << d.line << ", " << d.col << ")";
	    m_text = ss.str();
	}

	FileNotFoundException(const char * f)  {
	    std::stringstream ss;
	    ss << "File '" << f << "' not found";
	    m_text = ss.str();
	}

    };

	struct WrongPlaceDecl : public _YmirException_ {
		WrongPlaceDecl(Node * what, Node * father) {
			std::stringstream ss;
			ss << "Cannot declare " << what->toString() << " inside " << father->toString() << std::endl;
			m_text = ss.str();
		}
	};


	struct UndefinedReference : public _YmirException_ {
		UndefinedReference(RefDecl * ref) {
			std::stringstream ss;
			ss << "Undefined reference to '" << ref->name << "' : " << ref->line() ;
			m_text = ss.str();
		}
	};


};
