#pragma once

namespace SUtil
{
	// @brief String -> Value
	template <typename T>
	T s2v(std::string& str)
	{
		T value;
		std::stringstream ss;

		if (str != "")
		{
			ss.str(str);
			ss >> value;
		}

		return value;
	}

	// @brief 유니코드 -> 멀티바이트
	std::string w2s(std::wstring& ws)
	{
		int len = WideCharToMultiByte(CP_ACP, 0, &ws[0], -1, NULL, 0, NULL, NULL);
		std::string s(len, 0);
		WideCharToMultiByte(CP_ACP, 0, &ws[0], -1, &s[0], len, NULL, NULL);

		return s;
	}

	// @brief 멀티바이트 -> 유티코드
	std::wstring s2w(std::string& s)
	{
		std::wstring ws;

		return ws;
	}

}

