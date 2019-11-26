#ifndef __V4L2_WEBCAM___
#define __V4L2_WEBCAM___


enum io_method {
	IO_METHOD_READ,
	IO_METHOD_MMAP,
	IO_METHOD_USERPTR,
};


struct buffer {
	void *start;
	size_t length;
};


class V4L2_webcam {

public:
	V4L2_webcam(char *, enum io_method);

	int read_frame(void);
	void mainloop(void);
	void stop_capturing(void);
	void start_capturing(void);
	void uninit_device(void);
	void init_read(unsigned int);
	void init_mmap(void);
	void init_userp(unsigned int);
	void init_device(void);
	void close_device(void);
	void open_device(void);

private:
	enum io_method _io;
	struct buffer *_buffers;
	unsigned int _n_buffers;

};


#endif // __V4L2_WEBCAM___
