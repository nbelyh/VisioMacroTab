#pragma once

#include "Script.h"
#include <vector>

struct ScriptStorage
{
	void SaveScript(Script& s);
	void LoadScript(Script& s);

	std::vector<Script> GetAllScripts();
	std::vector<Script> FindScripts(const CString& match);
};
