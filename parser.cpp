#include <libxml/xpath.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <libxml/xmlreader.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <map>

#include "config.h"
#include "types.h"
#include "debug.h"
#include "alloc-inl.h"
#include "hash.h"
#include "parser.h"


//extern std::map<std::string, std::vector<std::string>> VARIABLES;
//extern std::vector<std::vector<std::string>> PARAMETERS_MUST; 
//extern std::vector<std::vector<std::string>> PARAMETERS_NOT_MUST;

void parseVariable(xmlDocPtr doc, 
		xmlNodePtr cur,
		std::map<std::string, std::vector<std::string>> *VARIABLES_ptr,
                std::vector<std::vector<std::string>> *PARAMETERS_MUST_ptr,
                std::vector<std::vector<std::string>> *PARAMETERS_NOT_MUST_ptr) {
  
  cur = cur->xmlChildrenNode;
  std::string name;
  std::vector<std::string> values;

  while (cur != NULL) {
    if ((!xmlStrcmp(cur->name, (const xmlChar *)"NAME"))) {
      name = std::string((char *)(xmlNodeListGetString(doc, cur->xmlChildrenNode, 1))); 
    } else if((!xmlStrcmp(cur->name, (const xmlChar *)"ELEMENT"))){
      values.push_back(std::string((char *)(xmlNodeListGetString(doc, cur->xmlChildrenNode, 1))));
    } else if((!xmlStrcmp(cur->name, (const xmlChar *)"text"))) {

    } else {
      FATAL("parseXML failed");
    }
    cur = cur->next;
  }

  if (name.size() == 0) {
    FATAL("name of variable is NULL");
  } else {
    (*VARIABLES_ptr)[name] = values;
  }

}

void parseParameter(xmlDocPtr doc, 
		xmlNodePtr cur,
		std::map<std::string, std::vector<std::string>> *VARIABLES_ptr,
                std::vector<std::vector<std::string>> *PARAMETERS_MUST_ptr,
                std::vector<std::vector<std::string>> *PARAMETERS_NOT_MUST_ptr) {  
  cur = cur->xmlChildrenNode;
  std::vector<std::string> values;
  std::string must;

  while (cur != NULL) {
    if ((!xmlStrcmp(cur->name, (const xmlChar *)"MUST"))) {
      must = std::string((char *)(xmlNodeListGetString(doc, cur->xmlChildrenNode, 1))); 
    } else if((!xmlStrcmp(cur->name, (const xmlChar *)"ELEMENT"))){
      values.push_back(std::string((char *)(xmlNodeListGetString(doc, cur->xmlChildrenNode, 1))));
    } else if((!xmlStrcmp(cur->name, (const xmlChar *)"text"))) {

    } else {
      FATAL("parseXML failed");
    }
    cur = cur->next;
  }

  if (must.size() == 0) {
    FATAL("must of parameter is NULL");
  } else if(must == "true") {
    PARAMETERS_MUST_ptr->push_back(values);
  } else {
    PARAMETERS_NOT_MUST_ptr->push_back(values);
  }

}

void parseWholeDoc(xmlDocPtr doc,
		std::map<std::string, std::vector<std::string>> *VARIABLES_ptr,
                std::vector<std::vector<std::string>> *PARAMETERS_MUST_ptr,
                std::vector<std::vector<std::string>> *PARAMETERS_NOT_MUST_ptr) {
  xmlNodePtr cur;
  cur = xmlDocGetRootElement(doc);

  if (cur == NULL) {
    FATAL("parseXML failed in parseWholeDoc");
  }

  cur = cur->xmlChildrenNode;

  while (cur != NULL) {
    
    if ((!xmlStrcmp(cur->name, (const xmlChar *)"VARIABLE"))) {
      parseVariable(doc, cur, VARIABLES_ptr, PARAMETERS_MUST_ptr, PARAMETERS_NOT_MUST_ptr);
    } else if ((!xmlStrcmp(cur->name, (const xmlChar *)"PARAMETER"))) {
      parseParameter(doc, cur, VARIABLES_ptr, PARAMETERS_MUST_ptr, PARAMETERS_NOT_MUST_ptr);
    } else if ((!xmlStrcmp(cur->name, (const xmlChar *)"text"))) {

    } else {
      FATAL("parseXML failed in parseWholeDoc");
    }
    cur = cur->next;    
  }

}

void parseXML(char *xml_position,
                std::map<std::string, std::vector<std::string>> *VARIABLES_ptr,
                std::vector<std::vector<std::string>> *PARAMETERS_MUST_ptr,
                std::vector<std::vector<std::string>> *PARAMETERS_NOT_MUST_ptr) {
  xmlDocPtr doc;
  doc = xmlParseFile(xml_position);

  parseWholeDoc(doc, VARIABLES_ptr, PARAMETERS_MUST_ptr, PARAMETERS_NOT_MUST_ptr);

}
