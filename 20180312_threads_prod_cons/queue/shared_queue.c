#include "shared_queue.h"
#include <stdio.h>

#include <err.h>
#include <errno.h>
#include <assert.h>



/* new_shared_queue() allocate and initialize a new queue             */
struct shared_queue* new_shared_queue(void)
{
	struct shared_queue *queue =malloc(sizeof(struct shared_queue));
	queue->store = malloc(sizeof(struct queue));
  int e = sem_init(&queue->lock,0,0);
	if(e!=0)errx(3,"Fail");
	int f= sem_init(&queue->size,0,0);
	if(f!=0)errx(3,"FAIL");
	return queue;
}

static void Push(struct queue *queue,int val)
{
  struct queue *node = malloc(sizeof(struct queue));
	node->value = val;
  if(queue)
		node->suiv=queue;
  else {
		node->suiv=queue->suiv;
    queue->suiv = node;}
	queue = node;

}
static int Pop(struct queue *queue)
{
  //assert(queue != NULL);
  if(!queue)
		errx(3,"FAIL");
	struct queue *node = malloc(sizeof(*node));
  node = queue->suiv;
  int x = node->value;
  if(node->suiv == node)
		queue =NULL;
	else
		queue->suiv = node->suiv;
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
	queue->size +=1;
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
	queue->size -=1;
	int r= sem_post(&queue->lock);
	if(r!=0)errx(r,"sem_post():lock");
	return val;
}
/* shared_queue_destroy(queue) destroy the queue                      *
 * free any remaining memory                                          */
void shared_queue_destroy(struct shared_queue *queue)
{	while(queue->store){
		queue->store->value=0;
		queue->store->suiv =NULL;}
}
