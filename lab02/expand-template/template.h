#pragma once
#include <map>
#include <string>

std::string ExpandTemplate(std::string const& tpl, std::map<std::string, std::string> const& params);

bool ExpandTemplateStream(std::istream & input, std::ostream & output, std::map<std::string, std::string> const& params);
