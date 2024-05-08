#include<dma.h>
#include<queue>
#include<cstdio>
#include<algorithm>
DMAComparator::DMAComparator(TaskManager<DMA> &manager) : m_manager(manager)
{
}

inline bool DMAComparator::operator()(Job* j1,Job* j2)
{
    if (m_manager.getTask(j1->gettaskid()).getRelDeadline()<m_manager.getTask(j2->gettaskid()).getRelDeadline())
    {
        return false;
    }
    
    return true;
}

DMAComparator::~DMAComparator()
{
}



DMA::DMA(TaskManager<DMA> &manager):m_manager(manager)//,queue(std::priority_queue<Job*,std::vector<Job*>,DMAComparator> (DMAComparator(manager)))
{

}

Job* DMA::getJob()
{
    if(m_jobsheap.size()==0ULL){
        return NULL;
    }
    Job* job=m_jobsheap[0];
    // std::pop_heap<std::vector<Job*>::iterator,DMAComparator>(m_jobsheap.begin(),m_jobsheap.end(),DMAComparator(m_manager));
    return job;
}

void DMA::addJob(Job* job)
{
    // queue.push(job);
    m_jobsheap.push_back(job);
    std::push_heap<std::vector<Job*>::iterator,DMAComparator>(m_jobsheap.begin(),m_jobsheap.end(),DMAComparator(m_manager));
}
void DMA::removeJob(Job* job){
    if(job==m_jobsheap[0]){
        std::pop_heap<std::vector<Job*>::iterator,DMAComparator>(m_jobsheap.begin(),m_jobsheap.end(),DMAComparator(m_manager));
        // printf("size %u",m_jobsheap.size());
        // exit(0);
        m_jobsheap.pop_back();
    }
    else{
        m_jobsheap.erase(std::find(m_jobsheap.begin(),m_jobsheap.end(),job));
        std::make_heap<std::vector<Job*>::iterator,DMAComparator>(m_jobsheap.begin(),m_jobsheap.end(),DMAComparator(m_manager));
    }
}
DMA::~DMA()
{
}

float DMA::nextEvent()
{
    
    
    return m_manager.nextrelease();
}
