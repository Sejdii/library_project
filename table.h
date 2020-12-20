#ifndef TABLE_H
#define TABLE_H

class Table
{
public:
    Table();

    virtual int push() = 0;

    virtual bool validate(bool edit=false) = 0;

private:
    unsigned int id;
};

#endif // TABLE_H
