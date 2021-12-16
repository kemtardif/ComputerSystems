/* 
A. The sizeof operator return a size_t type, which is unsigned, 
thus max-bytes-sizeof(val) will return an unsigned number, which is
greater than zero. one way to modifiy the result is to write
the condition as maxBytes >= sizeof(val). 

 */
void copy_int(int val, void *buf, int maxbytes) {
if (maxbytes-sizeof(val) >= 0)
memcpy(buf, (void *) &val, sizeof(val));
}