#ifndef TASKMANAGER_H
#define TASKMANAGER_H
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
class Task
{
private:
    static unsigned int i;
    std::string name="Task";
    float m_startphase=0;
    float m_period=1;
    float m_exectime=1;
    float m_reldeadline=m_period;
    size_t m_lastJob=0;
public:
    // Task(/* args */)=default;
    std::string getname();
    float getStartT();
    float getPeriod();
    float getExectime();
    float getRelDeadline();
    size_t lastJob();
    void jobadded();
    Task(float startp,float p,float e,float relatived);
    Task(float startp,float p,float e);
    ~Task();
};
class JobInstance
{
private:
public:
    size_t m_id=0;//task id
    float m_startT=0;
    float m_executedT=0;
    float m_totalexecT;
    JobInstance(size_t taskid,float startT,float executedT);
    ~JobInstance();
};

class Job
{
private:
    size_t m_taskid=0;
    size_t m_jobindex;
    float m_executedT=0;
    float m_totalexecT;
    
public:
    Job(size_t id,size_t jobindex,float e);
    size_t gettaskid() const;
    float getexecutedT() const;
    float gettotalexecT() const;
    size_t jobindex() const;
    void exec(float t);
    ~Job();
};




template<class Scheduler_class>
class TaskManager
{
public:
    std::vector<Job*> jobs;
private:
    // float t=0;
    std::vector<Task> tasks;
    std::vector<JobInstance> history;//time diagram
    Scheduler_class scheduler;
    void addJob(size_t taski);
    void removeJob(Job* jobp);
public:
    void printHistory();
    float t=0;
    TaskManager(/* args */);
    Task getTask(size_t taskid);
    void addTask(float startp,float p,float e,float relatived);
    void addTask(float startp,float p,float e);
    void printTasks();
    void update();
    Job* schedule();
    float nextrelease();
    float exec(Job* jobp);
    ~TaskManager();
};

template<class Scheduler_class>
void TaskManager<Scheduler_class>::printHistory()
{
    for (size_t i = 0; i < history.size(); i++)
    {
        std::cout<<tasks[history[i].m_id].getname()<<" "<<history[i].m_startT<<" "<<history[i].m_executedT<<'\n';
    }
    
}
template<class Scheduler_class>
void TaskManager<Scheduler_class>::addJob(size_t taski)
{
    printf("job added [%f]:task_id %lu\n",t,taski);
    Job* newjob=new Job(taski,tasks[taski].lastJob(),tasks[taski].getExectime());
    jobs.push_back(newjob);
    scheduler.addJob(newjob);
    tasks[taski].jobadded();
}
template<class Scheduler_class>
void TaskManager<Scheduler_class>::removeJob(Job* jobp)
{
    // printf("job completed %f\n",t);
    scheduler.removeJob(jobp);
    delete jobp;
    jobs.erase(std::find(jobs.begin(),jobs.end(),jobp)); //TODO
    // tasks[taski].jobadded();
}
template<class Scheduler_class>
TaskManager<Scheduler_class>::TaskManager():scheduler(Scheduler_class(*this))
{
}
template<class Scheduler_class>
void TaskManager<Scheduler_class>::addTask(float startp, float p, float e, float relatived)
{
    tasks.emplace_back(startp,p,e,relatived);
}
template <class Scheduler_class>
inline Task TaskManager<Scheduler_class>::getTask(size_t taskid)
{
    return tasks[taskid];
}
template<class Scheduler_class>
void TaskManager<Scheduler_class>::addTask(float startp, float p, float e)
{
    tasks.emplace_back(startp,p,e);
}
template<class Scheduler_class>
void TaskManager<Scheduler_class>::printTasks()
{
    for (size_t i = 0; i < tasks.size(); i++)
    {
        std::cout << tasks[i].getname() << " "
                    <<tasks[i].getStartT() << " "
                    <<tasks[i].getPeriod()<<" "
                    <<tasks[i].getExectime()<<" "
                    <<tasks[i].getRelDeadline() << '\n';
    }
}
template<class Scheduler_class>
void TaskManager<Scheduler_class>::update()
{
    for (size_t i = 0; i < tasks.size(); i++)
    {
        Task& temptask=tasks[i];
        if((temptask.getStartT()+temptask.getPeriod()*(temptask.lastJob()))<=t){
            addJob(i);
        }
    }
    
}
template<class Scheduler_class>
Job* TaskManager<Scheduler_class>::schedule()
{
    return scheduler.getJob();
    
}
template<class Scheduler_class>
float TaskManager<Scheduler_class>::nextrelease()
{
    
    float nextreleaseT=tasks[0].getStartT()+tasks[0].getPeriod()*(tasks[0].lastJob());
    float temprel=0;
    for (size_t i = 1; i < tasks.size(); i++)
    {
        temprel=tasks[i].getStartT()+tasks[i].getPeriod()*(tasks[i].lastJob());
        if(temprel<nextreleaseT) nextreleaseT=temprel;
    }
    return nextreleaseT;
}
template<class Scheduler_class>
float TaskManager<Scheduler_class>::exec(Job* jobp)
{
    float nextevent=scheduler.nextEvent();
    if(jobp==NULL){

        return nextevent-t;
    }
    float runT=std::min((jobp->gettotalexecT())-(jobp->getexecutedT()),nextevent-t);
    printf("%u run %s for %f\n",jobp->jobindex(),getTask(jobp->gettaskid()).getname().c_str(),runT);
    jobp->exec(runT);
    history.emplace_back(jobp->gettaskid(),t,runT);
    if((jobp->gettotalexecT())==(jobp->getexecutedT())){
        printf("job completed %f\n",t+runT);
        removeJob(jobp);
    }
    return runT;
}
template<class Scheduler_class>
TaskManager<Scheduler_class>::~TaskManager()
{
}




#endif