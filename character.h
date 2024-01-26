#include <raylib.h>
#include "basecharacter.h"

class Character : public BaseCharacter
{
public:
    Character(int winWidth, int winHeight);
    void tick(float deltaTime);

private:

};