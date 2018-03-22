#include "minimizeDFA.h"

std::vector<std::pair<State, std::map<char, State> > > getAcceptedStates(std::vector<State> v);

std::vector<std::pair<State, std::map<char, State> > > getNotAcceptedStates(std::vector<State> v);

void
matchStates(const DFATransitionTable &dfa,
            std::vector<std::vector<std::pair<State, std::map<char, State> > > > &classes);

int
findClass(std::vector<std::vector<std::pair<State, std::map<char, State> > > > &classes, unsigned long long int end,
          int id);

std::vector<std::vector<std::pair<State, std::map<char, State> > > >
split(std::vector<std::vector<std::pair<State, std::map<char, State> > > > &classes, unsigned long long int end,
      std::vector<std::pair<State, std::map<char, State> > > group);

bool is_equal(std::vector<std::vector<std::pair<State, std::map<char, State> > > > classes, unsigned long long int end,
              std::map<char, State> m1, std::map<char, State> m2);

#pragma clang diagnostic push

#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

DFATransitionTable minimizeDFA(const DFATransitionTable &dfa) {
    std::vector<State> states = dfa.getStates();
    std::vector<std::vector<std::pair<State, std::map<char, State> > > > classes;
    classes.push_back(getNotAcceptedStates(states));
    classes.push_back(getAcceptedStates(states));
    bool finish = false;
    unsigned long long int end = 2;
    while (!finish) {
        finish = true;
        matchStates(dfa, classes);
        for (int i = 0; i < end; i++) {
            std::vector<std::vector<std::pair<State, std::map<char, State> > > > groups = split(classes, end,
                                                                                                classes[i]);
            unsigned long long int len = groups.size();
            for (int j = 0; j < len; j++) {
                classes.push_back(groups[j]);
            }
        }
        if (classes.size() != 2 * end) {
            finish = false;
        }
        for (int i = 0; i < end; i++) {
            classes.erase(classes.begin());
        }
        end = classes.size();
    }
    matchStates(dfa, classes);
    DFATransitionTable min_dfa;
    unsigned long long int no_states = classes.size();
	std::vector<State> _states(no_states); // [no_states];
    for (int i = 0; i < no_states; i++) {
        _states[i] = State(i);
        _states[i].setType(classes[i][0].first.getType());
    }
    for (int i = 0; i < no_states; i++) {
        std::map<char, State> trans = dfa.getMapping(classes[i][0].first);
        for (auto &pair : trans) {
            int class_id = findClass(classes, end, trans[pair.first].getID());
            min_dfa.add(_states[i], pair.first, _states[class_id]);
        }
    }
    return min_dfa;
}

#pragma clang diagnostic pop


std::vector<std::pair<State, std::map<char, State> > > getAcceptedStates(std::vector<State> v) {
    std::vector<std::pair<State, std::map<char, State> > > res;
    unsigned long long int len = v.size();
    for (int i = 0; i < len; i++) {
        if (v[i].getType() == ACCEPTING) {
            std::map<char, State> t;
            res.emplace_back(v[i], t);
        }
    }
    return res;
}

std::vector<std::pair<State, std::map<char, State> > > getNotAcceptedStates(std::vector<State> v) {
    std::vector<std::pair<State, std::map<char, State> > > res;
    unsigned long long int len = v.size();
    for (int i = 0; i < len; i++) {
        if (v[i].getType() != ACCEPTING) {
            std::map<char, State> t;
            res.emplace_back(v[i], t);
        }
    }
    return res;
}

void
matchStates(const DFATransitionTable &dfa,
            std::vector<std::vector<std::pair<State, std::map<char, State> > > > &classes) {
    unsigned long long int end = classes.size();
    for (int i = 0; i < end; i++) {
        unsigned long long int n = classes[i].size();
        for (int j = 0; j < n; j++) {
            std::map<char, State> trans = dfa.getMapping(classes[i][j].first);
            for (auto &pair : trans) {
                classes[i][j].second[pair.first] = findClass(classes, end, pair.second.getID());
            }
        }
    }
}

int
findClass(std::vector<std::vector<std::pair<State, std::map<char, State> > > > &classes, unsigned long long int end,
          int id) {
    for (int i = 0; i < end; i++) {
        for (int j = 0; j < classes[i].size(); j++) {
            if (classes[i][j].first.getID() == id) {
                return i;
            }
        }
    }
}

std::vector<std::vector<std::pair<State, std::map<char, State> > > >
split(std::vector<std::vector<std::pair<State, std::map<char, State> > > > &classes, unsigned long long int end,
      std::vector<std::pair<State, std::map<char, State> > > group) {
    unsigned long long int n = group.size();
    std::vector<bool> vis(n, false);
    std::vector<std::vector<std::pair<State, std::map<char, State> > > > res;
    for (int j = 0; j < n; j++) {
        if (vis[j]) {
            continue;
        }
        vis[j] = true;
        std::vector<std::pair<State, std::map<char, State> > > temp;
        std::map<char, State> v;
        temp.emplace_back(group[j].first, v);
        for (int k = j + 1; k < n; k++) {
            if (is_equal(classes, end, group[j].second, group[k].second)) {
                vis[k] = true;
                std::map<char, State> vt;
                temp.emplace_back(group[k].first, vt);
            }
        }
        res.push_back(temp);
    }
    return res;
}

bool is_equal(std::vector<std::vector<std::pair<State, std::map<char, State> > > > classes, unsigned long long int end,
              std::map<char, State> m1, std::map<char, State> m2) {
    if (m1.size() != m2.size()) {
        return false;
    }
    for (auto &pair: m1) {
        if (!m2.count(pair.first)) {
            return false;
        }
        if (findClass(classes, end, m1[pair.first].getID()) != findClass(classes, end, m2[pair.first].getID())) {
            return false;
        }
    }
    return true;
}