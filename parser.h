#ifndef _PARSER_H
#define _PARSER_H

#include <vector>
#include <map>

void parseXML(char *xml_position,
		std::map<std::string, std::vector<std::string>> *VARIABLES_ptr,
		std::vector<std::vector<std::string>> *PARAMETERS_MUST_ptr,
		std::vector<std::vector<std::string>> *PARAMETERS_NOT_MUST_ptr);

#endif /* _PARSER_H */
