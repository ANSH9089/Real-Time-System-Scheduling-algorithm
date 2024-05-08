#ifndef DMA_H
#define DMA_H
#include<taskmanager.h>
#include<queue>
#include<vector>
class DMA;
class DMAComparator
{
private:
    TaskManager<DMA>& m_manager;
public:
    DMAComparator(TaskManager<DMA>& manager);
    bool operator()(Job* j1,Job* j2);
    ~DMAComparator();
};



class DMA//:public Scheduler
{
private:
    /* data */
    TaskManager<DMA>& m_manager;
    std::vector<Job*> m_jobsheap;
public:
    // DMA();
    DMA(TaskManager<DMA>& manager);
    Job* getJob();
    void addJob(Job* job);
    void removeJob(Job* job);
    float nextEvent();
    ~DMA();
};



#endif