#include "TransitionTable.h"

#define RAPIDJSON_HAS_STDSTRING 1

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/ostreamwrapper.h"

#include <map>
#include <set>


struct TransitionTable::impl
{
	std::map < std::set<State>, std::map<char, std::set<State> > > table;
};

TransitionTable::TransitionTable()
	: m_d(std::make_unique<impl>())
{

}

TransitionTable::TransitionTable(const TransitionTable & t)
	: m_d(std::make_unique<impl>())
{
	m_d->table = t.m_d->table;
}

TransitionTable::~TransitionTable()
{

}

void TransitionTable::add(const std::set<State> &currentStates, char input, const std::set<State> &nextStates)
{
	m_d->table[currentStates][input] = nextStates;
}

std::set<State> TransitionTable::nextStates(const std::set<State> &currentStates, char input) const
{
	return m_d->table[currentStates][input];
}

std::ostream& operator<<(std::ostream& out, const TransitionTable &transitionTable)
{
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

	return out;
}

std::istream& operator>>(std::istream& in, TransitionTable &transitionTable)
{
	using namespace rapidjson;

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

	return in;
}
