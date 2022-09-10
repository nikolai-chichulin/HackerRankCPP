#include "Util.h"

vector<int> inverse(vector<int> v) {

    vector<int> ret(v.size());
    for (int i = 0; i < v.size(); i++) {
        ret[i] = v[v.size() - 1 - i];
    }
    return ret;
}
