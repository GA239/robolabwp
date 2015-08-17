#pragma once

#include <string>

using namespace std;

class MZTextureSystem
{
	static MZTextureSystem* instance;
	static int _refcount;

public:

	static MZTextureSystem* startSystem()
    {
		instance = new MZTextureSystem();
		_refcount = 0;
        return instance;
    }
	static MZTextureSystem* getInstance()
    {
		if(!instance)
		{
			startSystem();
		}
		_refcount++;
		return instance;
    }
	void FreeInst() { _refcount--; if(!_refcount) {delete this; instance = NULL;}}

	void setTextureFromImage(string resourceName, string key);
	void useTextureWithKey(string key);
	void setColorWith(double r, double g, double b, string key);
	void useColorWithKey(string key);

private:
	MZTextureSystem(void);
	virtual ~MZTextureSystem(void);
	MZTextureSystem(const MZTextureSystem& root);
	MZTextureSystem& operator=(const MZTextureSystem&);
};

