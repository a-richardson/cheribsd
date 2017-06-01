/*-
 * Copyright (c) 2009 Stanislav Sedov <stas@FreeBSD.org>
 * All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD$
 */

#ifndef	_COMMON_KVM_H_
#define	_COMMON_KVM_H_

#include <stdbool.h>

dev_t	dev2udev(kvm_t *kd, struct cdev *dev);
int	kdevtoname(kvm_t *kd, struct cdev *dev, char *);
/*bool	kvm_read_all(kvm_t *kd, kvaddr_t addr, void *buf, size_t nbytes);*/

#if __has_feature(capabilities)
bool	kvm_read_cap(kvm_t *kd, const void* __capability addr,
		     void * __capability buf, size_t nbytes);
#endif
#ifndef __CHERI_PURE_CAPABILITY__
bool	kvm_read_ptr(kvm_t *kd, const void* addr, void *buf, size_t nbytes);
#else
#define kvm_read_ptr kvm_read_cap
#endif

/*
 * Filesystems specific access routines.
 */
int	devfs_filestat(kvm_t *kd, struct vnode *vp, struct vnstat *vn);
int	isofs_filestat(kvm_t *kd, struct vnode *vp, struct vnstat *vn);
int	msdosfs_filestat(kvm_t *kd, struct vnode *vp, struct vnstat *vn);
int	nfs_filestat(kvm_t *kd, struct vnode *vp, struct vnstat *vn);
int	smbfs_filestat(kvm_t *kd, struct vnode *vp, struct vnstat *vn);
int	udf_filestat(kvm_t *kd, struct vnode *vp, struct vnstat *vn);
int	ufs_filestat(kvm_t *kd, struct vnode *vp, struct vnstat *vn);
int	zfs_filestat(kvm_t *kd, struct vnode *vp, struct vnstat *vn);
void	*getvnodedata(struct vnode *vp);
struct mount	*getvnodemount(struct vnode *vp);

#endif	/* _COMMON_KVM_H_ */
