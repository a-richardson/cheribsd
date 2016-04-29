/*-
 * Copyright (c) 2016 Alex Richardson
 * All rights reserved.
 *
 * This software was developed by SRI International and the University of
 * Cambridge Computer Laboratory under DARPA/AFRL contract (FA8750-10-C-0237)
 * ("CTSRD"), as part of the DARPA CRASH research programme.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/types.h>

#if !__has_feature(capabilities)
#error "This code requires a CHERI-aware compiler"
#endif

#include <pthread.h>
#include <stdio.h>
#include <err.h>


struct thread_args {
	int num;
};

//static pthread_mutex_t global_mutex;

static void *thread_func(void *_arg)
{
	int result;
	struct thread_args *arg = _arg;

	fprintf(stderr, "---Thread %d thread_func() started!\n", arg->num);

	//pthread_t self = pthread_self();
	//fprintf(stderr, "Thread %p num: %d\n", self, arg->num);
// 	if ((result = pthread_mutex_lock(&global_mutex)) != 0) {
// 		errc(1, result, "pthread_mutex_lock");
// 	}
	fprintf(stderr, "---Thread num: %d got mutex\n", arg->num);
// 	if ((result = pthread_mutex_unlock(&global_mutex)) != 0) {
// 		errc(1, result, "pthread_mutex_unlock");
// 	}
	fprintf(stderr, "---Thread num: %d finished\n", arg->num);
	return NULL;
}


int
main(void)
{
	pthread_t thread1;
	pthread_t thread2;
	pthread_t self;
	struct thread_args t1args;
	struct thread_args t2args;
	int result;

	t1args.num = 1;
	t2args.num = 2;
	fprintf(stderr, "---About to start cheri_pthreads\n");
	self = pthread_self();
	fprintf(stderr, "---Main thread is %p\n", self);
// 	if ((result = pthread_mutex_init(&global_mutex, NULL)) != 0) {
// 		errc(1, result, "pthread_create");
// 	}
//	fprintf(stderr, "---Global mutex initialized\n");
// 	if ((result = pthread_mutex_lock(&global_mutex)) != 0) {
// 		errc(1, result, "pthread_mutex_lock");
// 	}
//	fprintf(stderr, "---Main thread locked global mutex\n");
// 	if ((result = pthread_mutex_unlock(&global_mutex)) != 0) {
// 		errc(1, result, "pthread_mutex_lock");
// 	}
//	fprintf(stderr, "---Main thread unlocked global mutex\n");
	fprintf(stderr, "---About to spawn threads\n");
	if ((result = pthread_create(&thread1, NULL, thread_func, &t1args)) != 0) {
		errc(1, result, "pthread_create 1");
	}
	fprintf(stderr, "---Thread 1 created: %p\n", thread1);
// 	if ((result = pthread_create(&thread2, NULL, thread_func, &t2args)) != 0) {
// 		errc(1, result, "pthread_create 2");
// 	}
// 	fprintf(stderr, "---Thread 2 created: %p\n", thread2);
	/* TODO: pthread_cond_wait, etc... */
	/* wait for the second thread to finish */
	fprintf(stderr, "---Main thread %p waiting for thread %p to join\n", self, thread1);
	if ((result = pthread_join(thread1, NULL)) != 0) {
		errc(1, result, "pthread_join 1");
	}
	fprintf(stderr, "---Thread 1 joined!\n");
// 	fprintf(stderr, "---Main thread %p waiting for thread %p to join\n", self, thread2);
// 	if ((result = pthread_join(thread2, NULL)) != 0) {
// 		errc(1, result, "pthread_join 2");
// 	}
// 	fprintf(stderr, "---Thread 2 joined!\n");
	fprintf(stderr, "---Finished: %p\n", pthread_self());
	return (0);
}
