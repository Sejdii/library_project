#ifndef WORKER_H
#define WORKER_H

#include <QString>

#include <user.h>

const int WORKER_DEF_TYPE = 0;
const int WORKER_ADM_TYPE = 1;

class Worker : public User
{
private:
    unsigned int type;
    QString name;
    QString surname;
public:
    Worker(User user);
    Worker(int type, QString name, QString surname);
    Worker(unsigned int id);

    void set_user(User user);
    void set_id(unsigned int id);
    void fetch_worker_data();

    QString getName();

    int push();
    int getType();
};

#endif // WORKER_H
