#ifndef RMA_H
#define RMA_H
#include"scheduler.h"
#include<queue>
class RMA;
class RMAComparator
{
private:
    TaskManager<RMA>& m_manager;
public:
    RMAComparator(TaskManager<RMA>& manager);
    bool operator()(Job* j1,Job* j2);
    ~RMAComparator();
};



class RMA//:public Scheduler
{
private:
    /* data */
    TaskManager<RMA>& m_manager;
    std::vector<Job*> m_jobsheap;
public:
    // RMA();
    RMA(TaskManager<RMA>& manager);
    Job* getJob();
    void addJob(Job* job);
    void removeJob(Job* job);
    float nextEvent();
    float util();
    ~RMA();
};



#endif