#ifndef TABLE_H
#define TABLE_H

class Table
{
public:
    Table();

    virtual int push() = 0;

    virtual bool validate(bool edit=false) = 0;

protected:
    unsigned int id;
};

#endif // TABLE_H
