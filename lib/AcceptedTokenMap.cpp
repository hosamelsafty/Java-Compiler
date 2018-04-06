//
// Created by win8.1 on 24/03/2018.
//

#include "AcceptedTokenMap.h"

std::map<State, std::string> AcceptedTokenMap::nfaMap;
std::map<State, std::string> AcceptedTokenMap::dfaMap;

void AcceptedTokenMap::addNFAMapping(const State & state, std::string tokenType)
{
    nfaMap[state] = tokenType;
}
std::string AcceptedTokenMap::getNFAMapping(const std::set<State> & states)
{
    for (State s : states)
    {
        if (nfaMap.find(s) != nfaMap.end())
            return nfaMap[s];
    }
    return NULL;
}

void AcceptedTokenMap::addDFAMapping(const State & state, std::string tokenType)
{
    dfaMap[state] = tokenType;
}
std::string AcceptedTokenMap::getDFAMapping(const State & state)
{
    return dfaMap[state];
}
