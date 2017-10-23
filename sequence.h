#ifndef SEQUENCE_H
#define SEQUENCE_H


class Sequence
{
public:
std::list<int> str;
Sequence(Color Fore, Color Back);
~Sequence(){}
bool add(Color upper,Color lower);
private:
Color fore;
Color back;

bool EqvColor(Color first, Color second);
bool fits(Color a, Color b);
};

#endif // SEQUENCE_H
