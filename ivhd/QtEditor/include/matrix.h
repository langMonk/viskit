#ifndef MATRIX_H
#define MATRIX_H

class anyMatrix
{
public:
    Real *v;
    int n;

    anyMatrix(int _n);
    anyMatrix(const anyMatrix &m);
    ~anyMatrix() { delete [] v; }

    void operator=(const anyMatrix &m);
    void makeIdent();
    void zero();
    Real &el(int x, int y) { return v[x + y*n]; }
    bool isSymmetric();

    QString toString();
};


void Eigensolver(anyMatrix &A, anyMatrix &V, Real *d);


#endif // MATRIX_H
