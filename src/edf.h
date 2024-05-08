#ifndef EDF_H
#define EDF_H
#include<taskmanager.h>
#include<queue>
#include<vector>
class EDF;
class EDFComparator
{

private:
    TaskManager<EDF>& m_manager;
public:
    EDFComparator(TaskManager<EDF>& manager);
    bool operator()(Job* j1,Job* j2);
    ~EDFComparator();
};



class EDF//:public Scheduler
{
private:
    /* data */
    TaskManager<EDF>& m_manager;
    std::vector<Job*> m_jobsheap;
public:
    // EDF();
    EDF(TaskManager<EDF>& manager);
    Job* getJob();
    void addJob(Job* job);
    void removeJob(Job* job);
    float nextEvent();
    ~EDF();
};



#endif