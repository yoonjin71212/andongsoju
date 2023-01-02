enum __IOCTL_CMD__ {
__ZERO__,   /* literally 0. */
__PROTO_CLEAR__,   /* Clear function call */
/* SORT */
__PROTO_SORT_ASCENDING__,
__PROTO_SORT_DESCENDING__,
/*-----*/
__PROTO_SIZE_CALL__, /*Size request*/
};


typedef struct __buf_info_t__ {
} __buf_info_t__; /*Empty Structure*/

typedef __buf_info_t__ __BUF__; /*Easy name */

#define IOCTL_MAGIC 'G' /*Magic letter */
/*Actual IOCTL Commands, are here. */
#define __CLEAR__ _IOWR(IOCTL_MAGIC,__PROTO_CLEAR__, __buf_info_t__) 
#define __SORT_ASCENDING__ _IOWR(IOCTL_MAGIC,__PROTO_SORT_ASCENDING__, __buf_info_t__)
#define __SORT_DESCENDING__ _IOWR(IOCTL_MAGIC,__PROTO_SORT_DESCENDING__, __buf_info_t__)
#define __SIZE_CALL__ _IOWR(IOCTL_MAGIC,__PROTO_SIZE_CALL__, __buf_info_t__)
/*-------------------------------*/
/* This is error code for internal error detection */
#define LST_ERR "-100000000000"
