#include "Util.h"

vl inverse(vl v) {

    vl ret(v.size());
    for (ls i = 0; i < v.size(); i++) {
        ret[i] = v[v.size() - 1 - i];
    }
    return ret;
}
