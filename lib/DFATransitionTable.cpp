#include "DFATransitionTable.h"

#define RAPIDJSON_HAS_STDSTRING 1

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/ostreamwrapper.h"



struct DFATransitionTable::impl
{
    State startingState;
    std::set<State> endingStates;

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
    m_d->startingState = t.m_d->startingState;
    m_d->endingStates = t.m_d->endingStates;
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

bool DFATransitionTable::checkTransition(const State &currentState, char input) const
{
    std::map<char, State> table = m_d->table[currentState];
    return table.find(input) != table.end();
}

std::vector<State> DFATransitionTable::getStates() const
{
    std::vector<State> keys;
    for (auto& pair : m_d->table)
    {
        keys.push_back(pair.first);
    }
    return keys;
}

std::map<char, State> DFATransitionTable::getMapping(const State& state) const
{
    return m_d->table[state];
}

void DFATransitionTable::setStartingState(const State &state)
{
    m_d->startingState = state;
}


void DFATransitionTable::setAcceptingStates(const std::set<State> &states)
{
    m_d->endingStates = states;
}

void DFATransitionTable::addAcceptingState(const State &state)
{
    m_d->endingStates.insert(state);
}

bool DFATransitionTable::isAcceptingState(const State &state) const
{
    return m_d->endingStates.find(state) != m_d->endingStates.end();
}

State DFATransitionTable::getStartingState() const
{
    return m_d->startingState;
}

std::set<State> DFATransitionTable::getAcceptingStates() const
{
    return m_d->endingStates;
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

    d.AddMember("startState", transitionTable.getStartingState().getID(), allocator);

    Value acceptingStates;
    acceptingStates.SetArray();

    for (auto & state : transitionTable.getAcceptingStates())
    {
        acceptingStates.PushBack(state.getID(), allocator);
    }

    d.AddMember("acceptingStates", acceptingStates, allocator);

    OStreamWrapper osw(out);
    PrettyWriter<OStreamWrapper> writer(osw);
    d.Accept(writer);

    return out;
}

std::istream& operator >> (std::istream& in, DFATransitionTable &transitionTable)
{
    using namespace rapidjson;

    IStreamWrapper isw(in);

    Document d;
    d.ParseStream(isw);

    if (!(d.HasMember("tt") && d.HasMember("startState") && d.HasMember("acceptingStates")))
        return in;

    std::map < State, std::map<char, State > > table;

    for (auto& row : d["tt"].GetArray())
    {
        State currentState(row["currentState"].GetInt());

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

    transitionTable.setStartingState(State(d["startState"].GetInt()));

    for (auto & value : d["acceptingStates"].GetArray())
    {
        transitionTable.addAcceptingState(State(value.GetInt()));
    }

    transitionTable.m_d->table = table;

    return in;
}