mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());

struct treap {
    ll data, priority;
    array<treap *, 2> kids;
    int subtreeSize, sum, toProp;

    treap(int data);

};

void recalc(treap *t) {
    // recalculate sum and size
    if (t == NULL)return;
    t->subtreeSize = 1;
    for (auto kid : t->kids) {
        if (kid == NULL)continue;
        t->subtreeSize += kid->subtreeSize;
    }
    t->sum = t->data + t->toProp * t->subtreeSize;
    for (auto kid : t->kids) {
        if (kid != NULL)
            t->sum += kid->sum;
    }
}

treap::treap(int data) {
    this->data = data;
    priority = rng();
    kids = {NULL, NULL};
    toProp = 0;
    sum = data;
    subtreeSize = 1;
    recalc(this);
}

int size(treap *t) {
    if (t == NULL)return 0;
    return t->subtreeSize;
}

void propagete(treap *t) {
    if (t == NULL)return;
    if (t->toProp == 0)return;
    for (auto it : t->kids) {
        if (it != NULL) {
            it->toProp += t->toProp;
        }
    }
    t->data += t->toProp;
    t->toProp = 0;
    recalc(t);
}

array<treap *, 2> split(treap *t, int leftSize) {
    if (t == NULL)return {NULL, NULL};
    propagete(t);
    if (leftSize <= size(t->kids[0])) {
        // the root (me) is  in the right side
        array<treap *, 2> ans = split(t->kids[0], leftSize);
        t->kids[0] = ans[1];
        recalc(t);
        return {ans[0], t};
    } else {
        // i am in the left side
        int remin = leftSize - 1 - size(t->kids[0]);
        array<treap *, 2> ans = split(t->kids[1], remin);
        t->kids[1] = ans[0];
        recalc(t);
        return {t, ans[1]};
    }
}

treap *merge(treap *t1, treap *t2) {
    if (t1 == NULL)return t2;
    if (t2 == NULL)return t1;
    propagete(t1);
    propagete(t2);
    if (t1->priority < t2->priority) {
        t1->kids[1] = merge(t1->kids[1], t2);
        recalc(t1);
        return t1;
    } else {
        t2->kids[0] = merge(t1,t2->kids[0]);
        recalc(t2);
        return t2;
    }

}

treap *addRange(treap *it, int l, int r, int value) {
    array<treap *, 2> ans = split(it, l);
    array<treap *, 2> ans2 = split(ans[1], r - l + 1);
    ans2[0]->toProp += value;
    return merge(ans[0], merge(ans2[0], ans2[1]));
}
