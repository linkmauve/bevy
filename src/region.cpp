#include "region.h"
#include "utils.h"

#include "shape.h"

namespace Geom {

Regions sanitize_path(Path const &p) {
    Regions results;
    Crossings crs = self_crossings(p);
    for(unsigned i = 0; i < crs.size(); i++) {
        
    }
}

Region Region::operator*(Matrix const &m) const {
    Region r((m.flips() ? boundary.reverse() : getBoundary()) * m, fill);
    if(box && m.onlyScaleAndTranslation()) r.box = (*box) * m;
    return r;
}

bool Region::invariants() const {
    return self_crossings(boundary).empty();
}

unsigned outer_index(Regions const &ps) {
    if(ps.size() <= 1 || contains(ps[0].getBoundary(), ps[1].getBoundary().initialPoint())) {
        return 0;
    } else {
        /* Since we've already shown that chunks[0] is not outside
           it can be used as an exemplar inner. */
        Point exemplar = ps[0].getBoundary().initialPoint();
        for(unsigned i = 1; i < ps.size(); i++) {
            if(ps[i].contains(exemplar)) {
                std::cout << "oi: " << i << "\n";
                return i;
            }
        }
    }
    return ps.size();
}

}
