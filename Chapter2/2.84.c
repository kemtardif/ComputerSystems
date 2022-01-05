


int float_le(float x, float y) {
    unsigned ux = f2u(x);
    unsigned uy = f2u(y);


    unsigned sx = ux >> 31;
    unsigned sy = uy >> 31;

    int xIsNeg = sx > sy;
    int xyEqAndNeg = (sx ==1) && (uy <= ux);
    int xyEqAndPos = (sx == 0) && (uy >= ux);

    return xIsNeg || xyEqAndNeg || xyEqAndPos;
}