#include "shared_queue.h"
#include <stdio.h>

#include <err.h>
#include <errno.h>
#include <assert.h>


struct queue* queue_init(void)
{
	struct queue *queue = malloc(sizeof(struct queue));
	queue->suiv = queue;
	return queue;
}
/* new_shared_queue() allocate and initialize a new queue             */
struct shared_queue* new_shared_queue(void)
{
	struct shared_queue *queue =malloc(sizeof(struct shared_queue));
  queue->store = queue_init();
  int e = sem_init(&queue->lock,0,1);
	if(e!=0)errx(3,"Fail");
	int f= sem_init(&queue->size,0,0);
	if(f!=0)errx(3,"FAIL");
	return queue;
}

static void Push(struct queue *queue,int val)
{
  struct queue *node = queue_init();
	node->value = val;
  if(queue){
  	node->suiv=queue->suiv;
    queue->suiv = node;}
	queue->suiv = node;

}
static int Pop(struct queue *queue)
{
  assert(queue);
  struct queue *node = queue->suiv;
  int x = node->value;
  if(node->suiv == node)
		queue =NULL;
	else
		{queue->suiv = node->suiv;
		 node->suiv = NULL;
  }
	free(node);
  return x;

}
/* shared_queue_push(queue, val) add val to the queue                 *
 * notify waiting threads when done                                   */
void shared_queue_push(struct shared_queue *queue, int val)
{
	int e = sem_wait(&queue->lock);
	if(e!=0)errx(e,"sem_wait():lock");
	Push(queue->store,val);

  int f= sem_post(&queue->size);
	if(f!=0)errx(f,"sem_post():size");
	int r = sem_post(&queue->lock);
	if(r!=0)errx(r,"sem_post():lock");

}
/* shared_queue_pop(queue) pop a new value from the queue             *
 * blocks while the queue is empty                                    */
int shared_queue_pop(struct shared_queue *queue)
{
	int e= sem_wait(&queue->size);
	if(e!=0)errx(e,"sem_wait():size");
	int f=sem_wait(&queue->lock);
	if(f!=0)errx(f,"sem_wait():lock");
	int val= Pop(queue->store);

	int r= sem_post(&queue->lock);
	if(r!=0)errx(r,"sem_post():lock");
	return val;
}
/* shared_queue_destroy(queue) destroy the queue                      *
 * free any remaining memory                                          */
void shared_queue_destroy(struct shared_queue *queue)
{ 
	sem_destroy(&queue->lock);
	sem_destroy(&queue->size);
	free(queue->store);
	free(queue);
}
