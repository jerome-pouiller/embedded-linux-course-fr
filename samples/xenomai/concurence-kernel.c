#include <linux/kernel.h> 
#include <linux/module.h>
#include <linux/init.h>
#include <xenomai/native/task.h>
#include <xenomai/native/sem.h>

#define N 4

RT_TASK tasks[N];
RT_SEM s[N];

static void loop(void *cookie) {
	int idx = (int) cookie;
	int i = 0;
	int err = 0;

	while(1) {
		pr_info("Task: %d, count: %d\n", idx, i++);
		if ((err = rt_sem_p(&s[idx], TM_INFINITE)))
			pr_err("%d\n", -err);  
		if ((err = rt_sem_v(&s[(idx + 1) % N])))
			pr_err("%d\n", -err);  
	}
}


static int m_init(void)
{
	int i;
	int err = 0;
	for (i = 0; i < N; i++) {
		if ((err = rt_sem_create (s + i, NULL, 0, 0)))
			pr_err("Sem creation: %d\n", -err);
		if ((err = rt_task_create(tasks + i, NULL, 0, 1, 0)))
			pr_err("Task creation: %d\n", -err);
	}
	for (i = 0; i < N; i++) {
		if ((err = rt_task_start(tasks + i,  loop, (void *) i)))
			pr_err("%d\n", -err);  
	}
	if ((err = rt_sem_v(&s[0])))
			pr_err("%d\n", -err);  


        return 0;
}

static void m_exit(void)
{
	int i;
	int err = 0;

	for (i = 0; i < N; i++) {
		if ((err = rt_task_delete (&tasks[i])))
			pr_err("%d\n", -err);  
	}

}

// Declare special functions
module_init(m_init);
module_exit(m_exit);

// These uppercase macro will be added to informative section of module (.modinfo)
MODULE_AUTHOR("Jérôme Pouiller");
MODULE_DESCRIPTION("Testing Xenomai API");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.1");


