#include "minimizeDFA.h"

bool is_equal(std::vector<int> v1, std::vector<int> v2);
std::vector<std::pair<State, std::vector<int> > > getAcceptedStates(std::vector<State> v);
int findClass(std::vector<std::vector<std::pair<State, std::vector<int> > > > classes, unsigned long long int end, int id);
std::vector<std::vector<std::pair<State, std::vector<int> > > > split(std::vector<std::pair<State, std::vector<int> > >group);
std::vector<std::pair<State, std::vector<int> > > getNotAcceptedStates(std::vector<State> v);

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
        for(int i = 0; i <= end; i++){
            unsigned long long int n = classes[i].size();
            for(int j = 0; j < n; j++){
                std::map<char, State> trans = dfa.getMapping(classes[i][j].first);
                for(char c = '0'; c <= '9'; c++){
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
            }
        }
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
	return dfa;
}

std::vector<std::pair<State, std::vector<int> > > getAcceptedStates(std::vector<State> v){
    std::vector<std::pair<State, std::vector<int> > > res;
    unsigned long long int len = v.size();
    for(int i = 0; i < len; i++){
        if(v[i].getType() == ACCEPTING){
            std::vector<int> t;
            res.push_back(make_pair(v[i], t));
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
            res.push_back(make_pair(v[i], t));
        }
    }
    return res;
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
        temp.push_back(make_pair(group[j].first, v));
        for (int k = j + 1; k < n; k++) {
            if (is_equal(group[j].second, group[k].second)) {
                vis[k] = true;
                std::vector<int> vt;
                temp.push_back(make_pair(group[k].first, vt));
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