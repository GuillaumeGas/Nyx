#pragma once

#define DllExport __declspec(dllexport)

namespace nyx {
    namespace debug {
	class DllExport Debugger {
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
