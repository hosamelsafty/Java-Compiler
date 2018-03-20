#include "minimizeDFA.h"

std::vector<std::pair<State, std::vector<int> > > getAcceptedStates(std::vector<State> v);
std::vector<std::pair<State, std::vector<int> > > getNotAcceptedStates(std::vector<State> v);
void matchStates(const DFATransitionTable &dfa, std::vector<std::vector<std::pair<State, std::vector<int> > > > &classes);
int findClass(std::vector<std::vector<std::pair<State, std::vector<int> > > > classes, unsigned long long int end, int id);
std::vector<std::vector<std::pair<State, std::vector<int> > > > split(std::vector<std::pair<State, std::vector<int> > >group);
bool is_equal(std::vector<int> v1, std::vector<int> v2);

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
DFATransitionTable minimizeDFA(const DFATransitionTable &dfa)
{
    std::vector<State> states = dfa.getStates();
    std::vector<std::vector<std::pair<State, std::vector<int> > > > classes;
    classes.push_back(getNotAcceptedStates(states));
    classes.push_back(getAcceptedStates(states));
    bool finish = false;
    unsigned long long int end = 1;
    while(!finish){
        finish = true;
        matchStates(dfa, classes);
        for(int i = 0; i <= end; i++){
            std::vector<std::vector<std::pair<State, std::vector<int> > > > groups = split(classes[i]);
            unsigned long long int len = groups.size();
            for(int j = 0; j < len; j++){
                classes.push_back(groups[j]);
            }
        }
        if(classes.size() != 2 * end + 1){
            finish = false;
        }
        for(int i = 0; i <= end; i++){
            classes.erase(classes.begin());
        }
        end = classes.size();
    }
    matchStates(dfa, classes);
    DFATransitionTable min_dfa;
    unsigned long long int no_states = classes.size();
    State _states[no_states];
    for(int i = 0; i < no_states; i++){
        _states[i] = State(i);
        _states[i].setType(classes[i][0].first.getType());
    }
    for(int i = 0; i < no_states; i++){
        std::map<char, State> trans = dfa.getMapping(classes[i][0].first);
        for(auto& pair : trans){
           // classes[i][j].second.push_back(findClass(classes, end, pair.second.getID()));
            int class_id = findClass(classes, end, trans[pair.first].getID());
            min_dfa.add(_states[i], pair.first, _states[class_id]);
        }
        /*for(char c = '0'; c <= '9'; c++){
            min_dfa.add(_states[i], c, _states[classes[i][0].second[counter++]]);
        }
        for(char c = 'a'; c <= 'z'; c++){
            min_dfa.add(_states[i], c, _states[classes[i][0].second[counter++]]);
        }
        for(char c = 'A'; c <= 'Z'; c++){
            min_dfa.add(_states[i], c, _states[classes[i][0].second[counter++]]);
        }*/
    }
	return min_dfa;
}
#pragma clang diagnostic pop

std::vector<std::pair<State, std::vector<int> > > getAcceptedStates(std::vector<State> v){
    std::vector<std::pair<State, std::vector<int> > > res;
    unsigned long long int len = v.size();
    for(int i = 0; i < len; i++){
        if(v[i].getType() == ACCEPTING){
            std::vector<int> t;
            res.emplace_back(v[i], t);
        }
    }
    return res;
}

std::vector<std::pair<State, std::vector<int> > > getNotAcceptedStates(std::vector<State> v){
    std::vector<std::pair<State, std::vector<int> > > res;
    unsigned long long int len = v.size();
    for(int i = 0; i < len; i++){
        if(v[i].getType() != ACCEPTING){
            std::vector<int> t;
            res.emplace_back(v[i], t);
        }
    }
    return res;
}

void matchStates(const DFATransitionTable &dfa, std::vector<std::vector<std::pair<State, std::vector<int> > > > &classes){
    unsigned long long int end = classes.size();
    for(int i = 0; i <= end; i++){
        unsigned long long int n = classes[i].size();
        for(int j = 0; j < n; j++){
            std::map<char, State> trans = dfa.getMapping(classes[i][j].first);
            for(auto& pair : trans){
                classes[i][j].second.push_back(findClass(classes, end, pair.second.getID()));
            }
           /* for(char c = '0'; c <= '9'; c++){
                State s = trans[c];
                classes[i][j].second.push_back(findClass(classes, end, s.getID()));
            }
            for(char c = 'a'; c <= 'z'; c++){
                State s = trans[c];
                classes[i][j].second.push_back(findClass(classes, end, s.getID()));
            }
            for(char c = 'A'; c <= 'Z'; c++){
                State s = trans[c];
                classes[i][j].second.push_back(findClass(classes, end, s.getID()));
            }
            */
        }
    }
}

int findClass(std::vector<std::vector<std::pair<State, std::vector<int> > > > classes, unsigned long long int end, int id){
    for(int i = 0; i <= end; i++){
        for(int j = 0; j < classes[i].size(); j++){
            if(classes[i][j].first.getID() == id){
                return i;
            }
        }
    }
}

std::vector<std::vector<std::pair<State, std::vector<int> > > > split(std::vector<std::pair<State, std::vector<int> > >group) {
    unsigned long long int n = group.size();
    std::vector<bool> vis(n, false);
    std::vector<std::vector<std::pair<State, std::vector<int> > > > res;
    for (int j = 0; j < n; j++) {
        if (vis[j]) {
            continue;
        }
        vis[j] = true;
        std::vector<std::pair<State, std::vector<int> > >temp;
        std::vector<int> v;
        temp.emplace_back(group[j].first, v);
        for (int k = j + 1; k < n; k++) {
            if (is_equal(group[j].second, group[k].second)) {
                vis[k] = true;
                std::vector<int> vt;
                temp.emplace_back(group[k].first, vt);
            }
        }
        res.push_back(temp);
    }
    return res;
}
bool is_equal(std::vector<int> v1, std::vector<int> v2){
    if(v1.size() != v2.size()){
        return false;
    }
    unsigned long long int n = v1.size();
    for(int i = 0; i < n; i++){
        if(v1[i] != v2[i]){
            return false;
        }
    }
    return true;
}
