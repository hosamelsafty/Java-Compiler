#ifndef JAVACOMPILER_ACCEPTEDTOKENMAP_H
#define JAVACOMPILER_ACCEPTEDTOKENMAP_H

#include "State.h"
#include <string>
#include <map>
#include <set>

class AcceptedTokenMap
{
    static std::map<State, std::string> nfaMap;
    static std::map<State, std::string> dfaMap;
public:
    static void addNFAMapping(const State &, std::string);
    static std::string getNFAMapping(const std::set<State> &);

    static void addDFAMapping(const State &, std::string);
    static std::string getDFAMapping(const State &);
};


#endif
