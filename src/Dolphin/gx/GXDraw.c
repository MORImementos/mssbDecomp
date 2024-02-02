#include "Dolphin/gx.h"
#include "Dolphin/mtx.h"
#include "math.h"

void Subdivide(u8 subdivisionCount, const Vec *a, const Vec *b, const Vec *c)
{
    Vec p1;
    Vec p2;
    Vec p3;
    
    f32 stackManip[5];
    f32 sum; 

    if (subdivisionCount == 0)
    {
        GXBegin(GX_TRIANGLES, GX_VTXFMT3, 3);
        GXPosition3f32(a->x, a->y, a->z);
        GXPosition3f32(a->x, a->y, a->z);
        GXPosition3f32(b->x, b->y, b->z);
        GXPosition3f32(b->x, b->y, b->z);
        GXPosition3f32(c->x, c->y, c->z);
        GXPosition3f32(c->x, c->y, c->z);
    }
    else
    {
        p1.x = a->x + b->x;
        p2.x = b->x + c->x;
        p3.x = c->x + a->x;
        p1.y = a->y + b->y;
        p2.y = b->y + c->y;
        p3.y = c->y + a->y;
        p1.z = a->z + b->z;
        p3.z = c->z + a->z;
        p2.z = b->z + c->z;
        
        sum = dolsqrtf(SQUARE(p1.x) + SQUARE(p1.y) + SQUARE(p1.z));
        
        p1.x = p1.x / sum;
        p1.y = p1.y / sum;
        p1.z = p1.z / sum;

        sum = dolsqrtf(SQUARE(p2.x) + SQUARE(p2.y) + SQUARE(p2.z));

        p2.x = p2.x / sum;
        p2.y = p2.y / sum;
        p2.z = p2.z / sum;

        sum = dolsqrtf(SQUARE(p3.x) + SQUARE(p3.y) + SQUARE(p3.z));

        p3.x = p3.x / sum;
        p3.y = p3.y / sum;
        p3.z = p3.z / sum;

        subdivisionCount = ((subdivisionCount & 0xff) - 1);

        Subdivide(subdivisionCount & 0xff, a, &p1, &p3);
        Subdivide(subdivisionCount & 0xff, b, &p2, &p1);
        Subdivide(subdivisionCount & 0xff, c, &p3, &p2);
        Subdivide(subdivisionCount & 0xff, &p1, &p2, &p3);
    }
}
// unsure what these are for, but they're padding out .data?
static u8 unusedBytes[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x0b, 
    0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x08, 
    0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0e,
    0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x03, 
    0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x0f, 
    0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 
    0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x11, 
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x07, 
    0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x12, 
    0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x07, 
    0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x04, 
    0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x0c, 
    0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x0b, 
    0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x10, 
    0xbf, 0x4f, 0x1b, 0x9b, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x9e, 0x37, 0x37, 0xbf, 0x4f, 0x1b, 0x9b, 
    0x00, 0x00, 0x00, 0x00, 0xbe, 0x9e, 0x37, 0x37, 0x3f, 0x4f, 0x1b, 0x9b, 0x00, 0x00, 0x00, 0x00, 
    0xbe, 0x9e, 0x37, 0x37, 0x3f, 0x4f, 0x1b, 0x9b, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x9e, 0x37, 0x37, 
    0x3e, 0x9e, 0x37, 0x37, 0xbf, 0x4f, 0x1b, 0x9b, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x9e, 0x37, 0x37, 
    0xbf, 0x4f, 0x1b, 0x9b, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x9e, 0x37, 0x37, 0x3f, 0x4f, 0x1b, 0x9b, 
    0x00, 0x00, 0x00, 0x00, 0x3e, 0x9e, 0x37, 0x37, 0x3f, 0x4f, 0x1b, 0x9b, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x3e, 0x9e, 0x37, 0x37, 0xbf, 0x4f, 0x1b, 0x9b, 0x00, 0x00, 0x00, 0x00, 
    0xbe, 0x9e, 0x37, 0x37, 0xbf, 0x4f, 0x1b, 0x9b, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x9e, 0x37, 0x37, 
    0x3f, 0x4f, 0x1b, 0x9b, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x9e, 0x37, 0x37, 0x3f, 0x4f, 0x1b, 0x9b, 
    0xbf, 0x00, 0x00, 0x00, 0xbf, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0xbf, 0x00, 0x00, 0x00, 
    0xbf, 0x00, 0x00, 0x00, 0xbf, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0xbf, 0x00, 0x00, 0x00, 
    0xbf, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0xbf, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 
    0xbf, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0xbf, 0x00, 0x00, 0x00, 
    0x3f, 0x00, 0x00, 0x00, 0xbf, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 
    0xbf, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 
    0x3f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbf, 0x80, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x80, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbf, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0xbf, 0x80, 0x00, 0x00, 0x00, 0x04, 0x02, 0x01, 0x02, 0x04, 0x00, 0x03, 
    0x04, 0x01, 0x04, 0x03, 0x00, 0x02, 0x05, 0x01, 0x05, 0x02, 0x00, 0x05, 0x03, 0x01, 0x03, 0x05
};

static GXVtxDescList lbl_802E6910[27];
static GXVtxAttrFmtList lbl_802E69E8[27];

static Vec SpherePoints[] = {
    { -0.5257311f,  0.f,  0.8506508f },
    {  0.5257311f,  0.f,  0.8506508f },
    { -0.5257311f,  0.f, -0.8506508f },
    {  0.5257311f,  0.f, -0.8506508f },
    {  0.f,  0.8506508f,  0.5257311f },
    {  0.f,  0.8506508f, -0.5257311f },
    {  0.f, -0.8506508f,  0.5257311f },
    {  0.f, -0.8506508f, -0.5257311f },
    {  0.8506508f,  0.5257311f,  0.f },
    { -0.8506508f,  0.5257311f,  0.f },
    {  0.8506508f, -0.5257311f,  0.f },
    { -0.8506508f, -0.5257311f,  0.f },
};

static u8 SphereIndices[20][3] = {
    { 0x00, 0x04, 0x01 },
    { 0x00, 0x09, 0x04 },
    { 0x09, 0x05, 0x04 },
    { 0x04, 0x05, 0x08 },
    { 0x04, 0x08, 0x01 },
    { 0x08, 0x0a, 0x01 },
    { 0x08, 0x03, 0x0a },
    { 0x05, 0x03, 0x08 },
    { 0x05, 0x02, 0x03 },
    { 0x02, 0x07, 0x03 },
    { 0x07, 0x0a, 0x03 },
    { 0x07, 0x06, 0x0a },
    { 0x07, 0x0b, 0x06 },
    { 0x0b, 0x00, 0x06 },
    { 0x00, 0x01, 0x06 },
    { 0x06, 0x01, 0x0a },
    { 0x09, 0x00, 0x0b },
    { 0x09, 0x0b, 0x02 },
    { 0x09, 0x02, 0x05 },
    { 0x07, 0x02, 0x0b }
};

void GXDrawSphere1(u8 subdivisions)
{
    s32 i;
    GXGetVtxDescv(lbl_802E6910);
    GXGetVtxAttrFmtv(GX_VTXFMT3, lbl_802E69E8);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_NRM, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT3, GX_VA_POS, GX_CLR_RGBA, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT3, GX_VA_NRM, GX_CLR_RGB, GX_F32, 0);
    i = 19;
    do {
        u8 ii = i;
        Subdivide(subdivisions, &SpherePoints[SphereIndices[ii][0]], &SpherePoints[SphereIndices[ii][1]], &SpherePoints[SphereIndices[ii][2]]);
        i--;
    } while(i >= 0);
    GXSetVtxDescv(lbl_802E6910);
    GXSetVtxAttrFmtv(GX_VTXFMT3, lbl_802E69E8);
}