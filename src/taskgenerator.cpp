#include<taskgenerator.h>
template<class scheduler_class>
TaskGenerator<scheduler_class>::TaskGenerator(TaskManager<scheduler_class>& manager):m_manager(manager){
}