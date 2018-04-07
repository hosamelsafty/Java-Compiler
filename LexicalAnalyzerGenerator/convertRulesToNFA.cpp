#include "convertRulesToNFA.h"
#include "lib/RulesReader.h"

#include <stack>
#include <fstream>
#include <assert.h>

using namespace std;

NFATransitionTable nfaOfRule(const Rule &rule);
NFATransitionTable nfaOfRegex(const string &regex);

NFATransitionTable convertRulesToNFA(const std::string &filename)
{
    RulesReader rulesReader;
    std::vector<Rule> rules = rulesReader.process(filename);

    vector<NFATransitionTable> nfas;
    for (auto &rule : rules)
    {
        NFATransitionTable nfa = nfaOfRule(rule);
        nfas.push_back(nfa);
    }

    return NFATransitionTable::multiUnion(nfas);
}

NFATransitionTable nfaOfRule(const Rule &rule)
{
    NFATransitionTable nfa = nfaOfRegex(rule.regex);

    std::set<State> states = nfa.getAcceptingStates();
    std::set<State> acceptingStates;
    for (auto &state : states)
    {
        State acceptingState(state);
        acceptingState.setTokenType(rule.type);
        acceptingStates.insert(acceptingState);
    }
    nfa.setAcceptingStates(acceptingStates);

    return nfa;
}


struct node
{
    bool isOp;
    NFATransitionTable nfa;
    char op;

    node(const NFATransitionTable &n) : isOp(false), nfa(n) {}
    node(char o) : isOp(true), op(o) {}
};

NFATransitionTable charNFA(char c);
void windUpLastUnion(stack<node> &nodeStack);

NFATransitionTable nfaOfRegex(const string &regex)
{
    std::stack<node> nodeStack;

    bool backslash = false;
    for (size_t i = 0; i < regex.size(); ++i)
    {
        backslash = false;
        switch (regex[i])
        {
        case ' ':
            break;
        case '\\':
            backslash = true;
            ++i;
        default:
        {
            char ch = regex[i];
            if (backslash && ch == 'L')
            {
                ch = EPS;
            }

            NFATransitionTable tempNFA = charNFA(ch);
            if (nodeStack.size())
            {
                if (!nodeStack.top().isOp)
                {
                    tempNFA = nodeStack.top().nfa.opConcat(tempNFA);
                    nodeStack.pop();
                }
            }
            nodeStack.push(node(tempNFA));
            break;
        }
        case '|':
            assert(nodeStack.size() && !nodeStack.top().isOp);

            windUpLastUnion(nodeStack); // find previous '|' and process it

            nodeStack.push(node('|'));
            break;
        case '*':
        {
            assert(nodeStack.size() && !nodeStack.top().isOp);

            NFATransitionTable temp = nodeStack.top().nfa.opStar();
            nodeStack.pop();
            nodeStack.push(node(temp));
            break;
        }
        case '+':
        {
            assert(nodeStack.size() && !nodeStack.top().isOp);

            NFATransitionTable temp = nodeStack.top().nfa.opPlus();
            nodeStack.pop();
            nodeStack.push(node(temp));
            break;
        }
        case '(':
            nodeStack.push(node('('));
            break;
        case ')':
            assert(nodeStack.size() && !nodeStack.top().isOp);

            windUpLastUnion(nodeStack); // find previous '|' and process it

            if (nodeStack.size() >= 2)
            {
                node temp = nodeStack.top();
                nodeStack.pop();
                assert(nodeStack.top().isOp && nodeStack.top().op == '(');
                nodeStack.pop();

                if (nodeStack.size())
                {
                    if (!nodeStack.top().isOp)
                    {
                        temp.nfa = nodeStack.top().nfa.opConcat(temp.nfa);
                        nodeStack.pop();
                    }
                }

                nodeStack.push(temp);
            }
            break;
        }
    }

    windUpLastUnion(nodeStack);

    if (nodeStack.empty())
    {
        return NFATransitionTable();
    }
    else
    {
        assert(nodeStack.size() == 1 && !nodeStack.top().isOp);
        return nodeStack.top().nfa;
    }
}


NFATransitionTable charNFA(char c)
{
    NFATransitionTable nfa;
    State s, f;
    nfa.setTransition(s, c, f);
    nfa.addStartingState(s);
    nfa.addAcceptingStates(f);
    return nfa;
}

void windUpLastUnion(stack<node> &nodeStack)
{
    assert(nodeStack.size() && !nodeStack.top().isOp);
    if (nodeStack.size() >= 3)
    {
        node top = nodeStack.top();
        nodeStack.pop();
        if (nodeStack.top().isOp && nodeStack.top().op == '|')
        {
            nodeStack.pop();
            NFATransitionTable unionNFA = nodeStack.top().nfa.opUnion(top.nfa);
            nodeStack.pop();
            nodeStack.push(unionNFA);
        }
        else
        {
            nodeStack.push(top);
        }
    }
}





