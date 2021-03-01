#include "replace.h"
using std::string;

std::string TextStringReplace(const std::string & original,
	const std::string & searchStr, const std::string & replacementStr)
{
	if (searchStr.empty()) return original;

	string result;
	string::size_type searchPos = 0, foundPos;
	while ((foundPos = original.find(searchStr, searchPos)) != string::npos)
	{
		result.append(original, searchPos, foundPos - searchPos);
		result.append(replacementStr);
		searchPos = foundPos + searchStr.length();
	}
	result.append(original, searchPos);
	return result;
}

StreamReplaceError TextStreamReplace(std::istream & input, std::ostream & output,
	const std::string & searchStr, const std::string & replacementStr)
{
	string line;
	while (std::getline(input, line))
	{
		output << TextStringReplace(line, searchStr, replacementStr);
		if (!output) return StreamReplaceError::IOError;

		if (input.eof()) return StreamReplaceError::Success;

		output << '\n';
		if (!output) return StreamReplaceError::IOError;
	}

	if (input.eof()) return StreamReplaceError::Success;
	if (input.bad()) return StreamReplaceError::IOError;
	return StreamReplaceError::TooLongLine;
}
