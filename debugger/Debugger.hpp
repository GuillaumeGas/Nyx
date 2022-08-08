#pragma once

namespace nyx {
    namespace debug {
	class Debugger {
	public:
	    static Debugger* getInstance();
	    ~Debugger();

	    void debugBreak();

	private:
	    Debugger();

	    static Debugger* instance;
	};
    }
}
