#include "convertor.h"
#include "sequence.h"

const int LOWER = 0;
const int UPPER = 1;
const int FULL = 2;
const int EMPTY = 3;
std::list<int> str={UPPER};

bool Sequence::EqvColor(Color first, Color second) {
    if(first.r == second.r && first.g == second.g && first.b == second.b)
        return true;
     else
        return false;
}

bool Sequence::fits(Color a, Color b) {
    if((EqvColor(fore,a)&&EqvColor(back,b))||(EqvColor(fore,b)&&EqvColor(back,a)))
        return true;
    else
        return false;
}

Sequence::Sequence(Color Fore, Color Back){
    fore = Fore;
    back = Back;
}

bool Sequence::add(Color upper,Color lower) {
    if(fits(upper,lower)){
        if(EqvColor(upper,fore) && EqvColor(lower,fore))
            str.push_back(FULL);
        else if(EqvColor(upper,fore) && EqvColor(lower,back))
            str.push_back(UPPER);
        else if(EqvColor(upper,back) && EqvColor(lower,fore))
            str.push_back(LOWER);
        else if(EqvColor(upper,back) && EqvColor(lower,back))
            str.push_back(EMPTY);
     return true;
     } else return false;
}
