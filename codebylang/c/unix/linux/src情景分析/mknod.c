//inode.c
int inode_init_always(struct super_block *sb, struct inode *inode)
{
	static const struct address_space_operations empty_aops;
	static const struct inode_operations empty_iops;
	static const struct file_operations empty_fops;
	struct address_space *const mapping = &inode->i_data;

	inode->i_sb = sb;
	inode->i_blkbits = sb->s_blocksize_bits;
	inode->i_flags = 0;
	atomic_set(&inode->i_count, 1);
	inode->i_op = &empty_iops;
	inode->i_fop = &empty_fops;
	inode->i_nlink = 1;
	inode->i_uid = 0;
	inode->i_gid = 0;
	atomic_set(&inode->i_writecount, 0);
	inode->i_size = 0;
	inode->i_blocks = 0;
	inode->i_bytes = 0;
	inode->i_generation = 0;
#ifdef CONFIG_QUOTA
	memset(&inode->i_dquot, 0, sizeof(inode->i_dquot));
#endif
	inode->i_pipe = NULL;
	inode->i_bdev = NULL;
	inode->i_cdev = NULL;
	inode->i_rdev = 0;
	inode->dirtied_when = 0;

	if (security_inode_alloc(inode))
		goto out;

	/* allocate and initialize an i_integrity */
	if (ima_inode_alloc(inode))
		goto out_free_security;

	spin_lock_init(&inode->i_lock);
	lockdep_set_class(&inode->i_lock, &sb->s_type->i_lock_key);

	mutex_init(&inode->i_mutex);
	lockdep_set_class(&inode->i_mutex, &sb->s_type->i_mutex_key);

	init_rwsem(&inode->i_alloc_sem);
	lockdep_set_class(&inode->i_alloc_sem, &sb->s_type->i_alloc_sem_key);

	mapping->a_ops = &empty_aops;
	mapping->host = inode;
	mapping->flags = 0;
	mapping_set_gfp_mask(mapping, GFP_HIGHUSER_MOVABLE);
	mapping->assoc_mapping = NULL;
	mapping->backing_dev_info = &default_backing_dev_info;
	mapping->writeback_index = 0;

	/*
	 * If the block_device provides a backing_dev_info for client
	 * inodes then use that.  Otherwise the inode share the bdev's
	 * backing_dev_info.
	 */
	if (sb->s_bdev) {
		struct backing_dev_info *bdi;

		bdi = sb->s_bdev->bd_inode->i_mapping->backing_dev_info;
		mapping->backing_dev_info = bdi;
	}
	inode->i_private = NULL;
	inode->i_mapping = mapping;
#ifdef CONFIG_FS_POSIX_ACL
	inode->i_acl = inode->i_default_acl = ACL_NOT_CACHED;
#endif

#ifdef CONFIG_FSNOTIFY
	inode->i_fsnotify_mask = 0;
#endif

	return 0;

out_free_security:
	security_inode_free(inode);
out:
	return -ENOMEM;
}


//mknod->...init_special_inode
//申请indoe数据结构，并填写内容
void init_special_inode(struct inode *inode, umode_t mode, dev_t rdev)
{
	inode->i_mode = mode;
	if (S_ISCHR(mode)) { //字符设备
		inode->i_fop = &def_chr_fops;                //关联操作
		inode->i_rdev = rdev;                     //设备号
	} else if (S_ISBLK(mode)) {//块设备
		inode->i_fop = &def_blk_fops;            //关联操作
		inode->i_rdev = rdev;					//设备号
	} else if (S_ISFIFO(mode))
		inode->i_fop = &def_fifo_fops;
	else if (S_ISSOCK(mode))
		inode->i_fop = &bad_sock_fops;
	else
		printk(KERN_DEBUG "init_special_inode: bogus i_mode (%o) for"
				  " inode %s:%lu\n", mode, inode->i_sb->s_id,
				  inode->i_ino);
}

//这里的操作是vfs层面的操作，是虚拟的连接
//vfs层面的操作根据设备类型设备号寻找注册的实际操作，调用实际的操作

//块设备操作
const struct file_operations def_blk_fops = {
	.open		= blkdev_open,
	.release	= blkdev_close,
	.llseek		= block_llseek,
	.read		= do_sync_read,
	.write		= do_sync_write,
  	.aio_read	= generic_file_aio_read,
	.aio_write	= blkdev_aio_write,
	.mmap		= generic_file_mmap,
	.fsync		= block_fsync,
	.unlocked_ioctl	= block_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl	= compat_blkdev_ioctl,
#endif
	.splice_read	= generic_file_splice_read,
	.splice_write	= generic_file_splice_write,
};

//字符设备
const struct file_operations def_chr_fops = {
	.open = chrdev_open,
};








