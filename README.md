
##Sortable FIFO Device Driver for Linux
# headers
----------------
```c
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
```

# IOCTL commands as table
|Name|Code|Task|Tested|
|---|---|---|---|
|`__CLEAR__`|1|Clear buffer|**O**| 
|`__SORT_ASCENDING__`|**2**|Sort buffer(ascending)|**O**|    
|`__SORT_DESCENDING__`|**3**|Sort buffer(descending)|**O**|
|`__SIZE_CALL__`|4|return buffer size|**O**|
-----------------------------------------
    
**Use with caution**

Sort is performed, with its item size in bytes.

Device Driver's name format is /dev/${RANDOM_UUID}.

I/O is performed as FIFO.

Adapt for any usage.

You can change its allocation space.

Thanks.


