#include "Lifer.h"


Lifer::Lifer()
{
}

Lifer::Lifer(unsigned int chil, unsigned int life, int lX, int lY, bool hasProc):
children(chil),
lifetime(life),
loc_x(lX),
loc_y(lY),
has_procreated(hasProc)
{
}

Lifer::~Lifer()
{
}