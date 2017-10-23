#ifndef SEQUENCE_H
#define SEQUENCE_H


class Sequence
{
public:
std::list<int> str;
Sequence(Color Fore, Color Back){
    fore = Fore;
    back = Back;
}
~Sequence(){}
bool add(Color upper,Color lower);
private:
Color fore;
Color back;
const int LOWER;
const int UPPER;
const int FULL;
const int EMPTY;
    bool EqvColor(Color first, Color second);
    bool fits(Color a, Color b);
};

#endif // SEQUENCE_H
