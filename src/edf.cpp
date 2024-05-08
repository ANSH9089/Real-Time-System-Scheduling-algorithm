#include<edf.h>
#include<queue>
#include<cstdio>
#include<algorithm>
EDFComparator::EDFComparator(TaskManager<EDF> &manager) : m_manager(manager)
{
}

inline bool EDFComparator::operator()(Job* j1,Job* j2)
{
    
    if ((m_manager.getTask(j1->gettaskid()).getStartT()+(m_manager.getTask(j1->gettaskid()).getPeriod()*(j1->jobindex()))
    +m_manager.getTask(j1->gettaskid()).getRelDeadline())<(m_manager.getTask(j2->gettaskid()).getStartT()+(m_manager.getTask(j2->gettaskid()).getPeriod()*(j2->jobindex()))
    +m_manager.getTask(j2->gettaskid()).getRelDeadline()))
    {
        return false;
    }
    
    return true;
}

EDFComparator::~EDFComparator()
{
}



EDF::EDF(TaskManager<EDF> &manager):m_manager(manager)//,queue(std::priority_queue<Job*,std::vector<Job*>,EDFComparator> (EDFComparator(manager)))
{

}

Job* EDF::getJob()
{
    std::make_heap(m_jobsheap.begin(),m_jobsheap.end());
    if(m_jobsheap.size()==0ULL){
        return NULL;
    }
    Job* job=m_jobsheap[0];
    // std::pop_heap<std::vector<Job*>::iterator,EDFComparator>(m_jobsheap.begin(),m_jobsheap.end(),EDFComparator(m_manager));
    return job;
}

void EDF::addJob(Job* job)
{
    m_jobsheap.push_back(job);
    std::push_heap<std::vector<Job*>::iterator,EDFComparator>(m_jobsheap.begin(),m_jobsheap.end(),EDFComparator(m_manager));
}
void EDF::removeJob(Job* job){
    printf("removed %u %s\n",job->jobindex(),m_manager.getTask(job->gettaskid()).getname().c_str());
    if(job==m_jobsheap[0]){
        std::pop_heap<std::vector<Job*>::iterator,EDFComparator>(m_jobsheap.begin(),m_jobsheap.end(),EDFComparator(m_manager));
        // printf("size %u",m_jobsheap.size());
        // exit(0);
        m_jobsheap.pop_back();
    }
    else{
        m_jobsheap.erase(std::find(m_jobsheap.begin(),m_jobsheap.end(),job));
        std::make_heap<std::vector<Job*>::iterator,EDFComparator>(m_jobsheap.begin(),m_jobsheap.end(),EDFComparator(m_manager));
    }
}
EDF::~EDF()
{
}

float EDF::nextEvent()
{
    
    
    return m_manager.nextrelease();
}
