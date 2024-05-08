#include<cstdio>
#include"taskmanager.h"
#include"rma.h"
#include"dma.h"
#include"edf.h"
int main(int argc, char const *argv[])
{

    TaskManager<EDF> manager;
    // manager.addTask(0,20,3);
    // manager.addTask(0,5,2);
    // manager.addTask(0,10,2);
    // manager.addTask(1,6,1);
    // manager.addTask( 0, 7, 2, 6 );
    // manager.addTask( 0, 5, 2, 4 );

    manager.addTask( 0, 4,1);
    manager.addTask( 0, 5, 2);
    manager.addTask( 0, 7, 2);


    manager.printTasks();
    //add task
    //add task
    //add task
    Job* jobp=NULL;
    float tpassed=0.0f;
    std::string name;
    while (manager.t<20.0f)
    {
        printf("t:%f\n",manager.t);
        manager.update(); //update jobs ready queue
        jobp=manager.schedule();
        if(jobp!=NULL)
        name=manager.getTask(jobp->gettaskid()).getname();
        if(jobp!=NULL)
        printf("%u schedule %s at %f rel %f\n",jobp->jobindex(),name.c_str(),manager.t,manager.getTask(jobp->gettaskid()).getRelDeadline());
        else printf("err\n");
        tpassed=manager.exec(jobp);
        // if(jobp!=NULL)
        // printf("%u run %s for %f\n",jobp->jobindex(),name.c_str(),tpassed);
        //manager.nextevent();
        // printf("step %f %p\n",tpassed,jobp);
        manager.t+=tpassed;

    }
    printf("history:\n");
    manager.printHistory();
    return 0;
}
