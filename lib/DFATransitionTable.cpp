#include "DFATransitionTable.h"


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
    /*
    using namespace rapidjson;
    Document d;
    d.SetObject();
    Document::AllocatorType& allocator = d.GetAllocator();

    d.AddMember("tt", Value(), allocator);
    d["tt"].SetArray();
    for (const std::pair<std::set<State>, std::map<char, std::set<State> >> & transitionTableRow : transitionTable.m_d->table)
    {
        Value row;
        row.SetObject();

        Value currentStatesArray;
        currentStatesArray.SetArray();

        for (const State &currentState : transitionTableRow.first)
        {
            Value value(currentState.name.c_str(), currentState.name.size(), allocator);
            currentStatesArray.PushBack(value, allocator);
        }
        row.AddMember("currentStates", currentStatesArray, allocator);

        for (const std::pair<char, std::set<State>> &inputResultPair : transitionTableRow.second)
        {
            Value nextStatesArray;
            nextStatesArray.SetArray();

            for (const State &nextState : inputResultPair.second)
            {
                Value state(nextState.name.c_str(), nextState.name.size(), allocator);
                nextStatesArray.PushBack(state, allocator);
            }

            std::string charString(1, inputResultPair.first);
            Value input(charString.c_str(), charString.size(), allocator);
            row.AddMember(input, nextStatesArray, allocator);
        }

        d["tt"].PushBack(row, allocator);
    }

    OStreamWrapper osw(out);
    PrettyWriter<OStreamWrapper> writer(osw);
    d.Accept(writer);

    return out;*/
}

std::istream& operator>>(std::istream& in, DFATransitionTable &transitionTable)
{
    /*using namespace rapidjson;

    IStreamWrapper isw(in);

    Document d;
    d.ParseStream(isw);

    std::map < std::set<State>, std::map<char, std::set<State> > > table;

    for ( auto& row : d["tt"].GetArray())
    {
        std::set<State> currentStates;

        for (auto& v : row["currentStates"].GetArray())
        {
            currentStates.emplace(State(v.GetString()));
        }

        for (auto& m : row.GetObject())
        {
            std::string name(m.name.GetString());
            if (name != "currentStates")
            {
                char input = name[0];
                std::set<State> nextStates;

                for (auto& v : m.value.GetArray())
                {
                    nextStates.emplace(State(v.GetString()));
                }

                table[currentStates][input] = nextStates;
            }
        }

    }

    transitionTable.m_d->table = table;

    return in;*/
}
