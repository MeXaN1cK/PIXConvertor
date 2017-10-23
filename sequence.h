#ifndef SEQUENCE_H
#define SEQUENCE_H


class Sequence
{
public:
    Sequence(Color Fore, Color Back){
        fore = Fore;
        back = Back;
    }
    ~Sequence(){}
bool add(Color upper,Color lower);
private:
    bool EqvColor(Color first, Color second);
    bool fits(Color a, Color b);
};

#endif // SEQUENCE_H
