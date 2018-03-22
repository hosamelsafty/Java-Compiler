#include "DFATransitionTable.h"

#define RAPIDJSON_HAS_STDSTRING 1

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/ostreamwrapper.h"



struct DFATransitionTable::impl
{
    std::map < State, std::map<char, State > > table;
};

DFATransitionTable::DFATransitionTable()
        : m_d(std::make_unique<impl>())
{

}

DFATransitionTable::DFATransitionTable(const DFATransitionTable & t)
        : m_d(std::make_unique<impl>())
{
    m_d->table = t.m_d->table;
}

DFATransitionTable::~DFATransitionTable()
{

}

void DFATransitionTable::add(const State &currentState, char input, const State &nextState)
{
    m_d->table[currentState][input] = nextState;
}

State DFATransitionTable::nextState(const State &currentState, char input) const
{
    return m_d->table[currentState][input];
}

State* DFATransitionTable::tryNextState(const State &currentState, char input) const
{
    auto res = m_d->table[currentState].find(input);
    if(res != m_d->table[currentState].end()){
        return &res->second;
    }
    return  NULL;

}
std::vector<State> DFATransitionTable::getStates() const
{
    std::vector<State> keys;
    for( auto& pair : m_d->table)
    {
        keys.push_back(pair.first);
    }
    return keys;
}

std::map<char,State> DFATransitionTable::getMapping(const State& state) const
{
    return m_d->table[state];
}

std::ostream& operator<<(std::ostream& out, const DFATransitionTable &transitionTable)
{
    using namespace rapidjson;
    Document d;
    d.SetObject();
    Document::AllocatorType& allocator = d.GetAllocator();

    d.AddMember("tt", Value(), allocator);
    d["tt"].SetArray();
    for (const std::pair<State, std::map<char, State> > & transitionTableRow : transitionTable.m_d->table)
    {
        Value row;
        row.SetObject();

        row.AddMember("currentState", transitionTableRow.first.getID(), allocator);

        for (const std::pair<char, State> &inputResultPair : transitionTableRow.second)
        {
            std::string charString(1, inputResultPair.first);
            Value input(charString.c_str(), charString.size(), allocator);
			row.AddMember(input, inputResultPair.second.getID(), allocator);
        }

        d["tt"].PushBack(row, allocator);
    }

    OStreamWrapper osw(out);
    PrettyWriter<OStreamWrapper> writer(osw);
    d.Accept(writer);

    return out;
}

std::istream& operator>>(std::istream& in, DFATransitionTable &transitionTable)
{
    using namespace rapidjson;

    IStreamWrapper isw(in);

    Document d;
    d.ParseStream(isw);

    std::map < State, std::map<char, State > > table;

    for ( auto& row : d["tt"].GetArray())
    {
        State currentState( row["currentState"].GetInt() );

        for (auto& m : row.GetObject())
        {
            std::string name(m.name.GetString());
            if (name != "currentState")
            {
                char input = name[0];
                State nextState(m.value.GetInt());

                table[currentState][input] = nextState;
            }
        }
    }

    transitionTable.m_d->table = table;

    return in;
}
