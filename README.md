
## AndongSoju, Sortable FIFO Device Driver for Linux
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/31857db2f4aa40968e75023a1e951966)](https://www.codacy.com/gh/yoonjin2/andongsoju/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=yoonjin2/andongsoju&amp;utm_campaign=Badge_Grade)
![alt text](https://img.danawa.com/prod_img/500000/740/291/img/5291740_1.jpg?shrink=330:330&_v=20180830142133)

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

# IOCTL comments as table
|Name|Code|Task|Tested|
|---|---|---|---|
|`__CLEAR__`|1|Clear buffer|**O**| 
|`__SORT_ASCENDING__`|**2**|Sort buffer(ascending)|**O**|    
|`__SORT_DESCENDING__`|**3**|Sort buffer(descending)|**O**|
|`__SIZE_CALL__`|4|return buffer size|**O**|
-----------------------------------------
    
**Use with caution**

This is device driver that do all tasks in GFP_KERNEL.

You can change its allocation space.

Thanks.


