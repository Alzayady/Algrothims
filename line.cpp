struct LINE {
    ll a, b, c;
    pair<int, int> Point1, Point2;

    bool operator==(const LINE &L) {
        return L.a == a && L.b == b && L.c == c;
    };

    LINE(pair<int, int> point1, pair<int, int> point2) {
        Point1 = point1;
        Point2 = point2;
        a = point2.second - point1.second;
        b = point1.first - point2.first;
        c = point1.second * (point1.first - point2.first) - point1.first * (point1.second - point2.second);
        if (a < 0) {
            a *= -1;
            b *= -1;
            c *= -1;
        }
        if (a != 0 && b != 0 && c != 0) {
            ll m = abs(__gcd(a, b));
            m = abs(__gcd(m, c));
            a /= m;
            b /= m;
            c /= m;
        }
        if (b == 0) {
            if (c == 0) {
                a = 1;
            } else {
                ll m = abs(__gcd(a, c));
                a /= m;
                c /= m;
            }
        }
        if (a == 0) {
            if (c == 0) {
                b = 1;
            } else {
                ll m = abs(__gcd(b, c));
                b /= m;
                c /= m;
            }
        }
        if (c == 0) {
            if (a != 0 && b != 0) {
                ll m = abs(__gcd(b, a));
                a /= m;
                b /= m;
            }
        }
    }

    ld getX(ld y) {
        return 1.0 * (c - b * y) / a;
    }

    ld getY(ld x) {
        return 1.0 * (c - a * x) / b;
    }

    pair<ld, ld> intersectLine(LINE second) {
        if (b * second.a == second.b * a) {
            if (a == second.a && b == second.b && c == second.c) {
                return Point1;
            }
            return {INT_MAX, INT_MAX};
        }
        ll nom = c * second.a - second.c * a;
        ll dom = b * second.a - second.b * a;
        ld y = 1.0 * nom / dom;
        ld x = getX(y);
        return {x, y};
    }

    pair<ld, ld> intersectSegment(LINE second) {
        if (b * second.a == second.b * a) {
            if (a == second.a && b == second.b && c == second.c) {
                if (onSegment(second.Point1)) {
                    return second.Point1;
                }
                if (onSegment(second.Point2)) {
                    return second.Point2;
                }
                if (second.onSegment(Point1)) {
                    return Point1;
                }
                if (second.onSegment(Point2)) {
                    return Point2;
                }
            }
            return {INT_MAX, INT_MAX};
        }
        ll nom = c * second.a - second.c * a;
        ll dom = b * second.a - second.b * a;
        ld y = 1.0 * nom / dom;
        ld x = getX(y);
        if (onSegment({x, y}) && second.onSegment({x, y}))
            return {x, y};
        else
            return {INT_MAX, INT_MAX};
    }


    ll getDisSQ(pair<ll, ll> p1, pair<ll, ll> p2) {
        return (p1.first - p2.first) * (p1.first - p2.first) +
               (p1.second - p2.second) * (p1.second - p2.second);
    }

    bool onLine(pair<ld, ld> point) {
        return (a * point.first + b * point.second - c) < 0.00000001;
    }

    bool onSegment(pair<ld, ld> point) {
        ll dis = (getDisSQ(Point1, Point2));
        ll disA = (getDisSQ(point, Point1));
        ll disB = (getDisSQ(point, Point2));
        return disA <= dis && disB <= dis && onLine(point);
    }
};

