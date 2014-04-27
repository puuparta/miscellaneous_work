#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

namespace Utils
{
	void split(std::string str, std::string delim, std::vector<std::string> *results)
	{
		int cutAt;
		while( (cutAt = str.find_first_of(delim)) != str.npos )
		{
			if(cutAt > 0)
			{
				results->push_back(str.substr(0,cutAt));
			}

			str = str.substr(cutAt+1);
		}
		if(str.length() > 0)
		{
			results->push_back(str);
		}
	}


}

#endif