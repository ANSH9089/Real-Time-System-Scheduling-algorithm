#ifndef TASKGEN_H
#define TASKGEN_H
#include<taskmanager.h>
template<class scheduler_class>
class TaskGenerator{
    TaskManager<scheduler_class> m_manager;
    TaskGenerator(TaskManager<scheduler_class>& manager);
};


#endif