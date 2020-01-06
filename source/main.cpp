#include <string>
#include <vector>
#include "GarrysMod/Lua/Interface.h"

using namespace GarrysMod::Lua;

LUA_FUNCTION(encode) {
	if (!LUA->IsType(1, Type::STRING)) {
		LUA->ArgError(1, "Expected a string");
		LUA->PushNil();
		return 1;
	}

	std::string input = LUA->GetString(1);
	std::string output;

	int val = 0, valb = -6;
	for (unsigned char c : input) {
		val = (val << 8) + c;
		valb += 8;
		while (valb >= 0) {
			output.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[(val >> valb) & 0x3F]);
			valb -= 6;
		}
	}
	if (valb > -6) output.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[((val << 8) >> (valb + 8)) & 0x3F]);
	while (output.size() % 4) output.push_back('=');

	LUA->PushString(output.c_str());
	return 1;
}

LUA_FUNCTION(decode) {
	if (!LUA->IsType(1, Type::STRING)) {
		LUA->ArgError(1, "Expected a string");
		LUA->PushNil();
		return 1;
	}

	std::string input = LUA->GetString(1);
	std::string output;

	std::vector<int> T(256, -1);
	for (int i = 0; i < 64; i++) T["ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[i]] = i;
	int val = 0, valb = -8;
	for (unsigned char c : input) {
		if (T[c] == -1) break;
		val = (val << 6) + T[c];
		valb += 6;
		if (valb >= 0) {
			output.push_back(char((val >> valb) & 0xFF));
			valb -= 8;
		}
	}

	LUA->PushString(output.c_str());
	return 1;
}

GMOD_MODULE_OPEN() {
	LUA->PushSpecial(SPECIAL_GLOB);
		LUA->CreateTable();
			LUA->PushCFunction(encode);
			LUA->SetField(-2, "encode");

			LUA->PushCFunction(decode);
			LUA->SetField(-2, "decode");
		LUA->SetField(-2, "base64");
	LUA->Pop();

	return 1;
}

GMOD_MODULE_CLOSE() {
	return 0;
}