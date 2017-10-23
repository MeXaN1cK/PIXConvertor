#ifndef SEQUENCE_H
#define SEQUENCE_H


class Sequence {
public:
    Sequence(Color, Color);
    Sequence();
    ~Sequence();
bool add(Color, Color);

private:
    bool EqvColor(Color, Color);
    bool fits(Color, Color);
    Color fore, back;
};

#endif // SEQUENCE_H
