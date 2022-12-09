enum __IOCTL_CMD__ {
__ZERO__,
__PROTO_CLEAR__,
__PROTO_SORT_ASCENDING__,
__PROTO_SORT_DESCENDING__,
__PROTO_SIZE_CALL__,
};


typedef struct __buf_info_t__ {
} __buf_info_t__;

typedef __buf_info_t__ __BUF__;

#define IOCTL_MAGIC 'G'
#define __CLEAR__ _IOWR(IOCTL_MAGIC,__PROTO_CLEAR__, __buf_info_t__) 

#define __SORT_ASCENDING__ _IOWR(IOCTL_MAGIC,__PROTO_SORT_ASCENDING__, __buf_info_t__)
#define __SORT_DESCENDING__ _IOWR(IOCTL_MAGIC,__PROTO_SORT_DESCENDING__, __buf_info_t__)
#define __SIZE_CALL__ _IOWR(IOCTL_MAGIC,__PROTO_SIZE_CALL__, __buf_info_t__)
#define LST_ERR "-100000000000"
